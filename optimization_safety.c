#include "optimization_safety.h"
#include "optimization_report.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>

static void set_result(optimization_safety_result *destination,
	optimization_safety_result value)
{
	if (destination != NULL)
		*destination = value;
}

const char *optimization_safety_reason(optimization_safety_result result)
{
	switch (result)
	{
		case OPTIMIZATION_SAFE:
			return "safe transformation";
		case OPTIMIZATION_UNSUPPORTED_OPERATOR:
			return "unsupported arithmetic operator";
		case OPTIMIZATION_DIVISION_BY_ZERO:
			return "division by zero";
		case OPTIMIZATION_DIVISION_OVERFLOW:
			return "INT32_MIN divided by -1 overflows";
		case OPTIMIZATION_UNPROVEN_DIVISION_DENOMINATOR:
			return "division denominator is not a proven non-zero integer constant";
		case OPTIMIZATION_SIGNED_OVERFLOW:
			return "signed 32-bit integer overflow";
		case OPTIMIZATION_NOT_CONSTANT:
			return "expression is not a proven integer constant";
		case OPTIMIZATION_UNSUPPORTED_EXPRESSION:
			return "unsupported or potentially side-effecting expression";
		case OPTIMIZATION_EXPRESSION_TOO_COMPLEX:
			return "expression is too complex for the fixed safety representation";
	}
	return "unknown safety failure";
}

void optimization_safety_log_rejection(const char *optimization,
	const char *expression, optimization_safety_result result)
{
	printf("Optimization safety: %s rejected %s (%s)\n", optimization,
		expression == NULL ? "expression" : expression,
		optimization_safety_reason(result));
	optimization_report_record_rejection(optimization,
		expression == NULL ? "expression" : expression,
		optimization_safety_reason(result));
}

int optimization_safety_is_supported_operator(char operation)
{
	return operation == '+' || operation == '-' || operation == '*' ||
		operation == '/';
}

int optimization_safety_parse_int32_literal(const char *text, int32_t *result,
	optimization_safety_result *safety_result)
{
	char *end;
	long long value;

	if (text == NULL)
	{
		set_result(safety_result, OPTIMIZATION_UNSUPPORTED_EXPRESSION);
		return 0;
	}
	errno = 0;
	value = strtoll(text, &end, 10);
	if (errno != 0 || *end != '\0' || value < INT32_MIN || value > INT32_MAX)
	{
		set_result(safety_result, OPTIMIZATION_SIGNED_OVERFLOW);
		return 0;
	}
	if (result != NULL)
		*result = (int32_t)value;
	set_result(safety_result, OPTIMIZATION_SAFE);
	return 1;
}

int optimization_safety_evaluate_int32(char operation, int32_t left, int32_t right,
	int32_t *result, optimization_safety_result *safety_result)
{
	int64_t value;

	if (!optimization_safety_is_supported_operator(operation))
	{
		set_result(safety_result, OPTIMIZATION_UNSUPPORTED_OPERATOR);
		return 0;
	}
	if (operation == '/' && right == 0)
	{
		set_result(safety_result, OPTIMIZATION_DIVISION_BY_ZERO);
		return 0;
	}
	if (operation == '/' && left == INT32_MIN && right == -1)
	{
		set_result(safety_result, OPTIMIZATION_DIVISION_OVERFLOW);
		return 0;
	}

	switch (operation)
	{
		case '+': value = (int64_t)left + right; break;
		case '-': value = (int64_t)left - right; break;
		case '*': value = (int64_t)left * right; break;
		case '/': value = (int64_t)left / right; break;
		default: return 0;
	}

	if (value < INT32_MIN || value > INT32_MAX)
	{
		set_result(safety_result, OPTIMIZATION_SIGNED_OVERFLOW);
		return 0;
	}
	if (result != NULL)
		*result = (int32_t)value;
	set_result(safety_result, OPTIMIZATION_SAFE);
	return 1;
}

int optimization_safety_is_supported_variable(const char *name)
{
	return name != NULL && name[0] != '\0' && name[1] == '\0' &&
		isalpha((unsigned char)name[0]);
}

int optimization_safety_variable_index(const char *name)
{
	if (name != NULL && name[0] >= 'A' && name[0] <= 'Z' && name[1] == '\0')
		return name[0] - 'A';
	if (name != NULL && name[0] >= 'a' && name[0] <= 'z' && name[1] == '\0')
		return 26 + name[0] - 'a';
	return -1;
}

int optimization_safety_is_valid_integer_constant(const node *expression,
	optimization_safety_result *safety_result)
{
	if (expression != NULL && expression->is_integer_constant &&
		expression->left == NULL && expression->right == NULL)
	{
		set_result(safety_result, OPTIMIZATION_SAFE);
		return 1;
	}
	set_result(safety_result, OPTIMIZATION_NOT_CONSTANT);
	return 0;
}

int optimization_safety_is_dce_eligible(const node *expression,
	optimization_safety_result *safety_result)
{
	if (optimization_safety_is_valid_integer_constant(expression, safety_result))
		return 1;
	set_result(safety_result, OPTIMIZATION_UNSUPPORTED_EXPRESSION);
	return 0;
}

int optimization_safety_is_cse_expression_eligible(const node *expression,
	optimization_safety_result *safety_result)
{
	optimization_safety_result child_result;

	if (expression == NULL)
	{
		set_result(safety_result, OPTIMIZATION_UNSUPPORTED_EXPRESSION);
		return 0;
	}
	if (expression->cse_key[0] != '\0')
	{
		set_result(safety_result, OPTIMIZATION_SAFE);
		return 1;
	}
	if (expression->left == NULL && expression->right == NULL)
	{
		if (expression->is_integer_constant ||
			optimization_safety_is_supported_variable(expression->place))
		{
			set_result(safety_result, OPTIMIZATION_SAFE);
			return 1;
		}
		set_result(safety_result, OPTIMIZATION_UNSUPPORTED_EXPRESSION);
		return 0;
	}
	if (!optimization_safety_is_supported_operator(expression->Operator))
	{
		set_result(safety_result, OPTIMIZATION_UNSUPPORTED_OPERATOR);
		return 0;
	}
	if (!optimization_safety_is_cse_expression_eligible(expression->left,
			&child_result) ||
		!optimization_safety_is_cse_expression_eligible(expression->right,
			&child_result))
	{
		set_result(safety_result, child_result);
		return 0;
	}
	if (expression->Operator == '/')
	{
		if (!optimization_safety_is_valid_integer_constant(expression->right,
				&child_result))
		{
			set_result(safety_result, OPTIMIZATION_UNPROVEN_DIVISION_DENOMINATOR);
			return 0;
		}
		if (expression->right->integer_value == 0)
		{
			set_result(safety_result, OPTIMIZATION_DIVISION_BY_ZERO);
			return 0;
		}
	}
	set_result(safety_result, OPTIMIZATION_SAFE);
	return 1;
}
