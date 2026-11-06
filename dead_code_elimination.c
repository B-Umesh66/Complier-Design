#include "dead_code_elimination.h"
#include "optimization_safety.h"
#include "pass_selector.h"
#include "optimization_report.h"

#define MAX_DCE_ASSIGNMENTS 100
#define MAX_DCE_VARIABLES 52
#define DCE_START_ADDRESS 100

typedef struct dce_assignment
{
	char variable[32];
	node *expression;
	int first_quad;
	int last_quad;
	int used;
	int removed;
	int eligible;
	optimization_safety_result rejection_reason;
} dce_assignment;

extern char code[100][50];

static dce_assignment assignments[MAX_DCE_ASSIGNMENTS];
static int assignment_count = 0;
static int last_assignment[MAX_DCE_VARIABLES];
static int control_depth = 0;
static int control_seen = 0;
static int dce_enabled = 0;

static void remove_assignment(int index, const char *reason)
{
	int quad;
	dce_assignment *assignment = &assignments[index];

	if (!assignment->eligible || assignment->removed || assignment->used)
		return;

	for (quad = assignment->first_quad; quad < assignment->last_quad; ++quad)
		code[quad - DCE_START_ADDRESS][0] = '\0';

	assignment->removed = 1;
	printf("Dead code elimination: removed %s = %s (%s)\n",
		assignment->variable, assignment->expression->place, reason);
	{
		char original[128];
		snprintf(original, sizeof(original), "%s = %s", assignment->variable,
			assignment->expression->place);
		optimization_report_record_transformation("Dead Code Elimination", original,
			"removed", reason);
	}
	pass_selector_record_transformation(PASS_DEAD_CODE_ELIMINATION);
}

void set_dead_code_elimination(int enabled)
{
	int index;

	dce_enabled = enabled ? 1 : 0;
	assignment_count = 0;
	control_depth = 0;
	control_seen = 0;
	for (index = 0; index < MAX_DCE_VARIABLES; ++index)
		last_assignment[index] = -1;
}

int dead_code_elimination_is_enabled()
{
	return dce_enabled;
}

void dce_mark_expression_used(node *expression)
{
	int index;

	if (!dce_enabled || expression == NULL || control_depth != 0)
		return;

	if (expression->left != NULL || expression->right != NULL)
	{
		dce_mark_expression_used(expression->left);
		dce_mark_expression_used(expression->right);
		return;
	}

	if (!optimization_safety_is_supported_variable(expression->place))
		return;

	index = optimization_safety_variable_index(expression->place);
	if (index >= 0 && last_assignment[index] >= 0)
		assignments[last_assignment[index]].used = 1;
}

void dce_record_assignment(const char *variable, node *expression,
	int first_quad, int last_quad)
{
	int variable_slot;
	int previous;
	dce_assignment *assignment;

	if (!dce_enabled || !optimization_safety_is_supported_variable(variable) ||
		assignment_count >= MAX_DCE_ASSIGNMENTS)
		return;

	variable_slot = optimization_safety_variable_index(variable);
	if (control_depth == 0 && variable_slot >= 0)
	{
		previous = last_assignment[variable_slot];
		if (previous >= 0)
			remove_assignment(previous, "overwritten before its value was read");
		last_assignment[variable_slot] = -1;
	}

	assignment = &assignments[assignment_count];
	snprintf(assignment->variable, sizeof(assignment->variable), "%s", variable);
	assignment->expression = expression;
	assignment->first_quad = first_quad;
	assignment->last_quad = last_quad;
	assignment->used = 0;
	assignment->removed = 0;
	assignment->eligible = control_depth == 0 && !control_seen &&
		optimization_safety_is_dce_eligible(expression,
			&assignment->rejection_reason);
	if (!assignment->eligible && control_depth == 0 && !control_seen)
		optimization_safety_log_rejection("dead code elimination", variable,
			assignment->rejection_reason);
	if (assignment->eligible && variable_slot >= 0)
		last_assignment[variable_slot] = assignment_count;
	assignment_count++;
}

static void preserve_pending_assignments()
{
	int index;

	for (index = 0; index < assignment_count; ++index)
		assignments[index].used = 1;
}

void dce_enter_control()
{
	if (!dce_enabled)
		return;
	preserve_pending_assignments();
	control_seen = 1;
	control_depth++;
}

void dce_exit_control()
{
	if (!dce_enabled)
		return;
	preserve_pending_assignments();
	if (control_depth > 0)
		control_depth--;
}

void dce_finalize()
{
	int index;

	if (!dce_enabled)
		return;

	for (index = 0; index < assignment_count; ++index)
		remove_assignment(index, "value is never subsequently read");
}

void dce_emit_surviving_register_code()
{
	int index;

	if (!dce_enabled)
		return;

	for (index = 0; index < assignment_count; ++index)
	{
		if (!assignments[index].removed)
		{
			printf("Labeling Algorithm (No. of registers required)\n");
			calc_registers(assignments[index].expression);
			printf("Gencode : \n");
			gencode(assignments[index].expression);
			printf("\n");
		}
	}
}
