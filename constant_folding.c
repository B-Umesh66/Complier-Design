#include "constant_folding.h"
#include "optimization_safety.h"
#include "pass_selector.h"
#include "optimization_report.h"

static int folding_enabled = 0;

void set_constant_folding(int enabled)
{
	folding_enabled = enabled ? 1 : 0;
}

int constant_folding_is_enabled()
{
	return folding_enabled;
}

static void expression_text(node *expression, char *buffer, size_t capacity)
{
	if (capacity == 0)
		return;

	if (expression == NULL)
	{
		snprintf(buffer, capacity, "?");
		return;
	}

	if (expression->left == NULL && expression->right == NULL)
	{
		snprintf(buffer, capacity, "%s", expression->place);
		return;
	}

	{
		char left[128];
		char right[128];
		expression_text(expression->left, left, sizeof(left));
		expression_text(expression->right, right, sizeof(right));
		snprintf(buffer, capacity, "(%s %c %s)", left, expression->Operator, right);
	}
}

void optimize_constant_expression(node *expression)
{
	int32_t result;
	char original[256];
	optimization_safety_result safety_result;

	if (!folding_enabled || expression == NULL ||
		expression->left == NULL || expression->right == NULL)
		return;

	optimize_constant_expression(expression->left);
	optimize_constant_expression(expression->right);

	if (!expression->left->is_integer_constant ||
		!expression->right->is_integer_constant)
		return;

	expression_text(expression, original, sizeof(original));
	if (!optimization_safety_evaluate_int32(expression->Operator,
			expression->left->integer_value, expression->right->integer_value,
			&result, &safety_result))
	{
		optimization_safety_log_rejection("constant folding", original,
			safety_result);
		return;
	}

	snprintf(expression->place, sizeof(expression->place), "%d", (int)result);
	expression->integer_value = result;
	expression->is_integer_constant = 1;
	expression->Operator = '\0';
	expression->left = NULL;
	expression->right = NULL;

	printf("Constant folding: %s -> %d (compile-time integer arithmetic)\n",
		original, (int)result);
	{
		char optimized[32];
		snprintf(optimized, sizeof(optimized), "%d", (int)result);
		optimization_report_record_transformation("Constant Folding", original,
			optimized, "compile-time integer arithmetic");
	}
	pass_selector_record_transformation(PASS_CONSTANT_FOLDING);
}
