#include "optimization_report.h"

#include <stdio.h>
#include <string.h>

#define MAX_REPORT_RECORDS 200
#define MAX_REPORT_PASSES 8

typedef struct report_transformation
{
	char optimization[64];
	char original[256];
	char optimized[128];
	char reason[160];
} report_transformation;

typedef struct report_rejection
{
	char optimization[64];
	char expression[256];
	char reason[160];
} report_rejection;

typedef struct report_pass
{
	char pass[64];
	char status[32];
	char reason[160];
	int safe_candidates;
} report_pass;

static int report_enabled = 0;
static int report_json = 0;
static report_transformation transformations[MAX_REPORT_RECORDS];
static report_rejection rejections[MAX_REPORT_RECORDS];
static report_pass passes[MAX_REPORT_PASSES];
static int transformation_count = 0;
static int rejection_count = 0;
static int pass_count = 0;
static int tac_statistics_available = 0;
static int original_tac_instructions = 0;
static int optimized_tac_instructions = 0;

static void copy_text(char *destination, size_t capacity, const char *source)
{
	if (capacity == 0)
		return;
	snprintf(destination, capacity, "%s", source == NULL ? "" : source);
}

static void reset_report(void)
{
	transformation_count = 0;
	rejection_count = 0;
	pass_count = 0;
	tac_statistics_available = 0;
	original_tac_instructions = 0;
	optimized_tac_instructions = 0;
}

void optimization_report_set_enabled(int enabled)
{
	report_enabled = enabled ? 1 : 0;
	report_json = 0;
	reset_report();
}

void optimization_report_set_json(int enabled)
{
	report_enabled = enabled ? 1 : 0;
	report_json = enabled ? 1 : 0;
	reset_report();
}

int optimization_report_is_enabled(void)
{
	return report_enabled;
}

void optimization_report_record_transformation(const char *optimization,
	const char *original, const char *optimized, const char *reason)
{
	report_transformation *record;

	if (!report_enabled || transformation_count >= MAX_REPORT_RECORDS)
		return;
	record = &transformations[transformation_count++];
	copy_text(record->optimization, sizeof(record->optimization), optimization);
	copy_text(record->original, sizeof(record->original), original);
	copy_text(record->optimized, sizeof(record->optimized), optimized);
	copy_text(record->reason, sizeof(record->reason), reason);
}

void optimization_report_record_rejection(const char *optimization,
	const char *expression, const char *reason)
{
	report_rejection *record;

	if (!report_enabled || rejection_count >= MAX_REPORT_RECORDS)
		return;
	record = &rejections[rejection_count++];
	copy_text(record->optimization, sizeof(record->optimization), optimization);
	copy_text(record->expression, sizeof(record->expression), expression);
	copy_text(record->reason, sizeof(record->reason), reason);
}

void optimization_report_record_pass(const char *pass, const char *status,
	const char *reason, int safe_candidates)
{
	report_pass *record;

	if (!report_enabled || pass_count >= MAX_REPORT_PASSES)
		return;
	record = &passes[pass_count++];
	copy_text(record->pass, sizeof(record->pass), pass);
	copy_text(record->status, sizeof(record->status), status);
	copy_text(record->reason, sizeof(record->reason), reason);
	record->safe_candidates = safe_candidates;
}

void optimization_report_set_tac_statistics(int original_instructions,
	int optimized_instructions)
{
	if (!report_enabled)
		return;
	tac_statistics_available = 1;
	original_tac_instructions = original_instructions;
	optimized_tac_instructions = optimized_instructions;
}

static int transformations_for(const char *optimization)
{
	int index;
	int total = 0;
	for (index = 0; index < transformation_count; ++index)
		if (strcmp(transformations[index].optimization, optimization) == 0)
			total++;
	return total;
}

static void print_json_string(const char *text)
{
	const unsigned char *current = (const unsigned char *)text;
	putchar('"');
	while (*current != '\0')
	{
		switch (*current)
		{
			case '\\': fputs("\\\\", stdout); break;
			case '"': fputs("\\\"", stdout); break;
			case '\n': fputs("\\n", stdout); break;
			case '\r': fputs("\\r", stdout); break;
			case '\t': fputs("\\t", stdout); break;
			default:
				if (*current < 0x20)
					printf("\\u%04x", *current);
				else
					putchar(*current);
		}
		current++;
	}
	putchar('"');
}

static void print_json_report(void)
{
	int index;
	int eliminated = original_tac_instructions - optimized_tac_instructions;
	double reduction = original_tac_instructions == 0 ? 0.0 :
		(100.0 * (double)eliminated) / (double)original_tac_instructions;

	printf("BEGIN_OPTIMIZATION_REPORT_JSON\n{");
	printf("\n  \"total_transformations\": %d,", transformation_count);
	if (tac_statistics_available)
		printf("\n  \"tac_statistics\": {\"original_instructions\": %d, \"optimized_instructions\": %d, \"instructions_eliminated\": %d, \"percentage_reduction\": %.2f},",
			original_tac_instructions, optimized_tac_instructions, eliminated, reduction);
	printf("\n  \"passes\": [");
	for (index = 0; index < pass_count; ++index)
	{
		if (index != 0)
			printf(",");
		printf("\n    {\"pass\": "); print_json_string(passes[index].pass);
		printf(", \"status\": "); print_json_string(passes[index].status);
		printf(", \"reason\": "); print_json_string(passes[index].reason);
		printf(", \"safe_candidates\": %d}", passes[index].safe_candidates);
	}
	printf("\n  ],\n  \"transformations\": [");
	for (index = 0; index < transformation_count; ++index)
	{
		if (index != 0)
			printf(",");
		printf("\n    {\"type\": "); print_json_string(transformations[index].optimization);
		printf(", \"original\": "); print_json_string(transformations[index].original);
		printf(", \"optimized\": "); print_json_string(transformations[index].optimized);
		printf(", \"reason\": "); print_json_string(transformations[index].reason);
		printf("}");
	}
	printf("\n  ],\n  \"rejections\": [");
	for (index = 0; index < rejection_count; ++index)
	{
		if (index != 0)
			printf(",");
		printf("\n    {\"type\": "); print_json_string(rejections[index].optimization);
		printf(", \"expression\": "); print_json_string(rejections[index].expression);
		printf(", \"reason\": "); print_json_string(rejections[index].reason);
		printf("}");
	}
	printf("\n  ]\n}\nEND_OPTIMIZATION_REPORT_JSON\n");
}

void optimization_report_print(void)
{
	int index;
	int eliminated;
	double reduction;

	if (!report_enabled)
		return;
	if (report_json)
	{
		print_json_report();
		return;
	}

	printf("Unified optimization report:\n");
	printf("Pass selection:\n");
	if (pass_count == 0)
		printf("- Automatic selection was not requested.\n");
	for (index = 0; index < pass_count; ++index)
		printf("- %s: %s (%s; %d safe candidate%s)\n", passes[index].pass,
			passes[index].status, passes[index].reason, passes[index].safe_candidates,
			passes[index].safe_candidates == 1 ? "" : "s");

	printf("Transformations: %d total\n", transformation_count);
	for (index = 0; index < transformation_count; ++index)
		printf("- [%s] %s -> %s (%s)\n", transformations[index].optimization,
			transformations[index].original, transformations[index].optimized,
			transformations[index].reason);
	printf("Totals by pass:\n");
	for (index = 0; index < pass_count; ++index)
		printf("- %s: %d\n", passes[index].pass,
			transformations_for(passes[index].pass));
	if (tac_statistics_available)
	{
		eliminated = original_tac_instructions - optimized_tac_instructions;
		reduction = original_tac_instructions == 0 ? 0.0 :
			(100.0 * (double)eliminated) / (double)original_tac_instructions;
		printf("TAC effectiveness: original=%d optimized=%d eliminated=%d reduction=%.2f%%\n",
			original_tac_instructions, optimized_tac_instructions, eliminated, reduction);
		printf("TAC reduction is not an execution-time, executable-size, or machine-code performance measurement.\n");
	}

	printf("Safety rejections: %d\n", rejection_count);
	for (index = 0; index < rejection_count; ++index)
		printf("- [%s] %s (%s)\n", rejections[index].optimization,
			rejections[index].expression, rejections[index].reason);
}
