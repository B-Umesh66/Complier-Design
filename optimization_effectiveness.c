#include "optimization_effectiveness.h"
#include "optimization_report.h"

#include <stdio.h>

static int statistics_enabled = 0;
static int stats_output_enabled = 0;
static int baseline_instructions = 0;
static int optimized_instructions = 0;
static int finalized = 0;

static int expression_instruction_count(const node *expression)
{
	/* This exactly mirrors emit_expression(): leaves emit no TAC, and every
	 * non-leaf emits its children followed by one arithmetic TAC instruction. */
	if (expression == NULL ||
		(expression->left == NULL && expression->right == NULL))
		return 0;
	return expression_instruction_count(expression->left) +
		expression_instruction_count(expression->right) + 1;
}

void optimization_effectiveness_set_enabled(int enabled)
{
	int requested = enabled ? 1 : 0;

	if (statistics_enabled == requested)
		return;
	statistics_enabled = requested;
	stats_output_enabled = 0;
	baseline_instructions = 0;
	optimized_instructions = 0;
	finalized = 0;
}

void optimization_effectiveness_set_stats_output(int enabled)
{
	if (enabled)
		statistics_enabled = 1;
	stats_output_enabled = enabled ? 1 : 0;
}

int optimization_effectiveness_is_enabled(void)
{
	return statistics_enabled;
}

void optimization_effectiveness_record_expression(const node *expression)
{
	if (statistics_enabled)
		baseline_instructions += expression_instruction_count(expression);
}

void optimization_effectiveness_record_assignment(void)
{
	if (statistics_enabled)
		baseline_instructions++;
}

void optimization_effectiveness_record_condition(void)
{
	if (statistics_enabled)
		baseline_instructions += 2;
}

void optimization_effectiveness_record_jump(void)
{
	if (statistics_enabled)
		baseline_instructions++;
}

void optimization_effectiveness_finalize(int first_quad, int next_quad,
	char code[100][50])
{
	int quad;

	if (!statistics_enabled || finalized)
		return;
	for (quad = first_quad; quad < next_quad; ++quad)
		if (code[quad - first_quad][0] != '\0')
			optimized_instructions++;
	finalized = 1;
	optimization_report_set_tac_statistics(baseline_instructions,
		optimized_instructions);
}

void optimization_effectiveness_print_stats(void)
{
	int eliminated;
	double reduction;

	if (!statistics_enabled || !stats_output_enabled || !finalized)
		return;
	eliminated = baseline_instructions - optimized_instructions;
	reduction = baseline_instructions == 0 ? 0.0 :
		(100.0 * (double)eliminated) / (double)baseline_instructions;
	printf("TAC statistics: original=%d optimized=%d eliminated=%d reduction=%.2f%%\n",
		baseline_instructions, optimized_instructions, eliminated, reduction);
	printf("TAC counts do not measure execution time, executable size, or machine-code performance.\n");
}
