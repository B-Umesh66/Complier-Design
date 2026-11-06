#include "pass_selector.h"

#include "constant_folding.h"
#include "constant_propagation.h"
#include "dead_code_elimination.h"
#include "common_subexpression_elimination.h"
#include "optimization_safety.h"
#include "optimization_report.h"

static const char *pass_names[PASS_COUNT] = {
	"Constant Folding",
	"Constant Propagation",
	"Dead Code Elimination",
	"Common Subexpression Elimination"
};

static int auto_enabled = 0;
static int manual_state[PASS_COUNT] = { -1, -1, -1, -1 };
static int auto_selected[PASS_COUNT] = { 0, 0, 0, 0 };
static int candidates[PASS_COUNT] = { 0, 0, 0, 0 };
static int transformations[PASS_COUNT] = { 0, 0, 0, 0 };
static int control_depth = 0;

static void enable_pass(optimization_pass pass)
{
	if (manual_state[pass] == 0 || auto_selected[pass])
		return;
	auto_selected[pass] = 1;
	switch (pass)
	{
		case PASS_CONSTANT_FOLDING: set_constant_folding(1); break;
		case PASS_CONSTANT_PROPAGATION: set_constant_propagation(1); break;
		case PASS_DEAD_CODE_ELIMINATION: set_dead_code_elimination(1); break;
		case PASS_COMMON_SUBEXPRESSION_ELIMINATION:
			set_common_subexpression_elimination(1); break;
		default: break;
	}
}

static int has_safe_folding_candidate(node *expression)
{
	int32_t ignored;
	optimization_safety_result safety_result;

	if (expression == NULL || expression->left == NULL || expression->right == NULL)
		return 0;
	if (has_safe_folding_candidate(expression->left) ||
		has_safe_folding_candidate(expression->right))
		return 1;
	if (!optimization_safety_is_valid_integer_constant(expression->left,
			&safety_result) ||
		!optimization_safety_is_valid_integer_constant(expression->right,
			&safety_result))
		return 0;
	return optimization_safety_evaluate_int32(expression->Operator,
		expression->left->integer_value, expression->right->integer_value,
		&ignored, &safety_result);
}

static int has_variable(node *expression)
{
	if (expression == NULL)
		return 0;
	if (expression->left != NULL || expression->right != NULL)
		return has_variable(expression->left) || has_variable(expression->right);
	return !expression->is_integer_constant &&
		optimization_safety_is_supported_variable(expression->place);
}

void pass_selector_set_auto(int enabled)
{
	int index;
	auto_enabled = enabled ? 1 : 0;
	control_depth = 0;
	for (index = 0; index < PASS_COUNT; ++index)
	{
		auto_selected[index] = 0;
		candidates[index] = 0;
		transformations[index] = 0;
	}
}

int pass_selector_auto_is_enabled()
{
	return auto_enabled;
}

void pass_selector_note_manual_option(optimization_pass pass, int enabled)
{
	if (pass >= 0 && pass < PASS_COUNT)
		manual_state[pass] = enabled ? 1 : 0;
}

void pass_selector_analyze_expression(node *expression)
{
	optimization_safety_result safety_result;

	if (!auto_enabled || expression == NULL)
		return;
	if (has_safe_folding_candidate(expression))
	{
		candidates[PASS_CONSTANT_FOLDING]++;
		enable_pass(PASS_CONSTANT_FOLDING);
	}
	if (control_depth == 0 && expression->left != NULL &&
		expression->right != NULL && has_variable(expression) &&
		optimization_safety_is_cse_expression_eligible(expression, &safety_result))
	{
		candidates[PASS_COMMON_SUBEXPRESSION_ELIMINATION]++;
		enable_pass(PASS_COMMON_SUBEXPRESSION_ELIMINATION);
	}
}

void pass_selector_analyze_folding(node *expression)
{
	if (!auto_enabled || expression == NULL)
		return;
	if (!constant_folding_is_enabled() &&
		has_safe_folding_candidate(expression))
	{
		candidates[PASS_CONSTANT_FOLDING]++;
		enable_pass(PASS_CONSTANT_FOLDING);
	}
}

void pass_selector_analyze_assignment(const char *variable, node *expression)
{
	optimization_safety_result safety_result;

	pass_selector_analyze_expression(expression);
	if (!auto_enabled || control_depth != 0 ||
		!optimization_safety_is_supported_variable(variable))
		return;
	if (optimization_safety_is_valid_integer_constant(expression, &safety_result))
	{
		candidates[PASS_CONSTANT_PROPAGATION]++;
		candidates[PASS_DEAD_CODE_ELIMINATION]++;
		enable_pass(PASS_CONSTANT_PROPAGATION);
		enable_pass(PASS_DEAD_CODE_ELIMINATION);
	}
}

void pass_selector_enter_control()
{
	if (auto_enabled)
		control_depth++;
}

void pass_selector_exit_control()
{
	if (auto_enabled && control_depth > 0)
		control_depth--;
}

void pass_selector_record_transformation(optimization_pass pass)
{
	if (auto_enabled && pass >= 0 && pass < PASS_COUNT)
		transformations[pass]++;
}

void pass_selector_report()
{
	int index;

	for (index = 0; index < PASS_COUNT; ++index)
	{
		if (manual_state[index] == 0)
			optimization_report_record_pass(pass_names[index], "skipped",
				"explicitly disabled", candidates[index]);
		else if (manual_state[index] == 1)
			optimization_report_record_pass(pass_names[index], "manual mode",
				"explicitly enabled", candidates[index]);
		else if (auto_selected[index])
			optimization_report_record_pass(pass_names[index], "selected",
				"supported safe candidate detected", candidates[index]);
		else if (auto_enabled)
			optimization_report_record_pass(pass_names[index], "skipped",
				"no supported safe candidate", candidates[index]);
		else
			optimization_report_record_pass(pass_names[index], "not selected",
				"automatic selection was not requested", candidates[index]);
	}

	if (!auto_enabled)
		return;
	printf("Adaptive optimization report:\n");
	for (index = 0; index < PASS_COUNT; ++index)
	{
		if (manual_state[index] == 0)
			printf("- %s: skipped (explicitly disabled)\n", pass_names[index]);
		else if (manual_state[index] == 1)
			printf("- %s: manual mode (%d safe candidate%s, %d transformation%s performed)\n",
				pass_names[index], candidates[index], candidates[index] == 1 ? "" : "s",
				transformations[index], transformations[index] == 1 ? "" : "s");
		else if (auto_selected[index])
			printf("- %s: selected (%d safe candidate%s, %d transformation%s performed)\n",
				pass_names[index], candidates[index], candidates[index] == 1 ? "" : "s",
				transformations[index], transformations[index] == 1 ? "" : "s");
		else
			printf("- %s: skipped (no supported safe candidate)\n", pass_names[index]);
	}
}
