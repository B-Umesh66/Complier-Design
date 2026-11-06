#ifndef OPTIMIZATION_SAFETY_H
#define OPTIMIZATION_SAFETY_H

#include "node.h"

typedef enum optimization_safety_result
{
	OPTIMIZATION_SAFE = 0,
	OPTIMIZATION_UNSUPPORTED_OPERATOR,
	OPTIMIZATION_DIVISION_BY_ZERO,
	OPTIMIZATION_DIVISION_OVERFLOW,
	OPTIMIZATION_UNPROVEN_DIVISION_DENOMINATOR,
	OPTIMIZATION_SIGNED_OVERFLOW,
	OPTIMIZATION_NOT_CONSTANT,
	OPTIMIZATION_UNSUPPORTED_EXPRESSION,
	OPTIMIZATION_EXPRESSION_TOO_COMPLEX
} optimization_safety_result;

const char *optimization_safety_reason(optimization_safety_result result);
void optimization_safety_log_rejection(const char *optimization,
	const char *expression, optimization_safety_result result);

int optimization_safety_is_supported_operator(char operation);
int optimization_safety_parse_int32_literal(const char *text, int32_t *result,
	optimization_safety_result *safety_result);
int optimization_safety_evaluate_int32(char operation, int32_t left, int32_t right,
	int32_t *result, optimization_safety_result *safety_result);
int optimization_safety_is_supported_variable(const char *name);
int optimization_safety_variable_index(const char *name);
int optimization_safety_is_valid_integer_constant(const node *expression,
	optimization_safety_result *safety_result);
int optimization_safety_is_dce_eligible(const node *expression,
	optimization_safety_result *safety_result);
int optimization_safety_is_cse_expression_eligible(const node *expression,
	optimization_safety_result *safety_result);

#endif
