#include "constant_propagation.h"
#include "optimization_safety.h"
#include "pass_selector.h"
#include "optimization_report.h"

#define MAX_CONSTANT_BINDINGS 52

typedef struct constant_binding
{
	char variable[32];
	int known;
	int32_t value;
} constant_binding;

static constant_binding bindings[MAX_CONSTANT_BINDINGS];
static int propagation_enabled = 0;

void set_constant_propagation(int enabled)
{
	propagation_enabled = enabled ? 1 : 0;
}

int constant_propagation_is_enabled()
{
	return propagation_enabled;
}

void clear_constant_bindings()
{
	int index;

	for (index = 0; index < MAX_CONSTANT_BINDINGS; ++index)
		bindings[index].known = 0;
}

static constant_binding *find_binding(const char *variable, int create)
{
	int index;
	constant_binding *empty = NULL;

	for (index = 0; index < MAX_CONSTANT_BINDINGS; ++index)
	{
		if (bindings[index].variable[0] == '\0')
		{
			if (empty == NULL)
				empty = &bindings[index];
		}
		else if (strcmp(bindings[index].variable, variable) == 0)
			return &bindings[index];
	}

	if (create && empty != NULL)
	{
		snprintf(empty->variable, sizeof(empty->variable), "%s", variable);
		return empty;
	}

	return NULL;
}

void propagate_constants(node *expression)
{
	constant_binding *binding;

	if (!propagation_enabled || expression == NULL)
		return;

	if (expression->left != NULL || expression->right != NULL)
	{
		propagate_constants(expression->left);
		propagate_constants(expression->right);
		return;
	}

	if (expression->is_integer_constant ||
		!optimization_safety_is_supported_variable(expression->place))
		return;

	binding = find_binding(expression->place, 0);
	if (binding == NULL || !binding->known)
		return;

	printf("Constant propagation: %s -> %d (known constant assignment)\n",
		expression->place, (int)binding->value);
	{
		char original[32];
		char optimized[32];
		snprintf(original, sizeof(original), "%s", expression->place);
		snprintf(optimized, sizeof(optimized), "%d", (int)binding->value);
		optimization_report_record_transformation("Constant Propagation", original,
			optimized, "known constant assignment");
	}
	snprintf(expression->place, sizeof(expression->place), "%d", (int)binding->value);
	expression->is_integer_constant = 1;
	expression->integer_value = binding->value;
	pass_selector_record_transformation(PASS_CONSTANT_PROPAGATION);
}

void record_constant_assignment(const char *variable, node *expression)
{
	constant_binding *binding;
	optimization_safety_result safety_result;

	if (!propagation_enabled ||
		!optimization_safety_is_supported_variable(variable))
		return;

	binding = find_binding(variable, 1);
	if (binding == NULL)
		return;

	if (optimization_safety_is_valid_integer_constant(expression, &safety_result))
	{
		binding->known = 1;
		binding->value = expression->integer_value;
	}
	else
	{
		binding->known = 0;
		optimization_safety_log_rejection("constant propagation", variable,
			safety_result);
	}
}
