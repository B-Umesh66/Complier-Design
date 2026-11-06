#include "common_subexpression_elimination.h"
#include "optimization_safety.h"
#include "pass_selector.h"
#include "optimization_report.h"
#include <stdint.h>

#define MAX_CSE_ENTRIES 100

typedef struct cse_entry
{
	char key[256];
	char result[32];
	uint64_t dependencies;
	int active;
} cse_entry;

static cse_entry entries[MAX_CSE_ENTRIES];
static int entry_count = 0;
static int cse_enabled = 0;
static int control_depth = 0;

static int copy_text(char *destination, size_t capacity, const char *source)
{
	int written = snprintf(destination, capacity, "%s", source);
	return written >= 0 && (size_t)written < capacity;
}

static int build_key(node *expression, char *key, size_t capacity,
	uint64_t *dependencies)
{
	char left_key[256];
	char right_key[256];
	uint64_t left_dependencies;
	uint64_t right_dependencies;
	int index;
	int written;

	if (expression == NULL || capacity == 0)
		return 0;
	if (expression->cse_key[0] != '\0')
	{
		*dependencies = expression->cse_dependencies;
		return copy_text(key, capacity, expression->cse_key);
	}
	if (expression->left == NULL && expression->right == NULL)
	{
		if (expression->is_integer_constant)
		{
			written = snprintf(key, capacity, "I:%d", (int)expression->integer_value);
			*dependencies = 0;
			return written >= 0 && (size_t)written < capacity;
		}
		index = optimization_safety_variable_index(expression->place);
		if (index < 0)
			return 0;
		written = snprintf(key, capacity, "V:%c", expression->place[0]);
		*dependencies = ((uint64_t)1) << index;
		return written >= 0 && (size_t)written < capacity;
	}
	if (!optimization_safety_is_supported_operator(expression->Operator))
		return 0;
	if (!build_key(expression->left, left_key, sizeof(left_key), &left_dependencies) ||
		!build_key(expression->right, right_key, sizeof(right_key), &right_dependencies))
		return 0;
	if ((expression->Operator == '+' || expression->Operator == '*') &&
		strcmp(left_key, right_key) > 0)
	{
		char temporary[256];
		uint64_t dependency_temporary = left_dependencies;
		copy_text(temporary, sizeof(temporary), left_key);
		copy_text(left_key, sizeof(left_key), right_key);
		copy_text(right_key, sizeof(right_key), temporary);
		left_dependencies = right_dependencies;
		right_dependencies = dependency_temporary;
	}
	written = snprintf(key, capacity, "O:%c(%s,%s)", expression->Operator,
		left_key, right_key);
	if (written < 0 || (size_t)written >= capacity)
		return 0;
	*dependencies = left_dependencies | right_dependencies;
	copy_text(expression->cse_key, sizeof(expression->cse_key), key);
	expression->cse_dependencies = *dependencies;
	return 1;
}

static void expression_text(node *expression, char *buffer, size_t capacity)
{
	char left[128];
	char right[128];

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
	expression_text(expression->left, left, sizeof(left));
	expression_text(expression->right, right, sizeof(right));
	snprintf(buffer, capacity, "(%s %c %s)", left, expression->Operator, right);
}

static cse_entry *find_entry(const char *key)
{
	int index;
	for (index = 0; index < entry_count; ++index)
	{
		if (entries[index].active && strcmp(entries[index].key, key) == 0)
			return &entries[index];
	}
	return NULL;
}

static void cache_expression(const char *key, const char *result,
	uint64_t dependencies)
{
	if (find_entry(key) != NULL || entry_count >= MAX_CSE_ENTRIES)
		return;
	copy_text(entries[entry_count].key, sizeof(entries[entry_count].key), key);
	copy_text(entries[entry_count].result, sizeof(entries[entry_count].result), result);
	entries[entry_count].dependencies = dependencies;
	entries[entry_count].active = 1;
	entry_count++;
}

static void optimize_node(node *expression)
{
	char key[256];
	char original[256];
	uint64_t dependencies;
	cse_entry *entry;
	optimization_safety_result safety_result;

	if (expression == NULL || expression->left == NULL || expression->right == NULL)
		return;
	if (!optimization_safety_is_cse_expression_eligible(expression,
			&safety_result))
	{
		expression_text(expression, original, sizeof(original));
		optimization_safety_log_rejection("common subexpression elimination",
			original, safety_result);
		return;
	}
	optimize_node(expression->left);
	optimize_node(expression->right);
	if (!build_key(expression, key, sizeof(key), &dependencies))
	{
		expression_text(expression, original, sizeof(original));
		optimization_safety_log_rejection("common subexpression elimination",
			original, OPTIMIZATION_EXPRESSION_TOO_COMPLEX);
		return;
	}
	entry = find_entry(key);
	if (entry == NULL)
	{
		cache_expression(key, expression->place, dependencies);
		return;
	}
	expression_text(expression, original, sizeof(original));
	printf("Common subexpression elimination: %s -> %s (reuses earlier computation)\n",
		original, entry->result);
	optimization_report_record_transformation("Common Subexpression Elimination",
		original, entry->result, "reuses earlier computation");
	pass_selector_record_transformation(PASS_COMMON_SUBEXPRESSION_ELIMINATION);
	snprintf(expression->place, sizeof(expression->place), "%s", entry->result);
	expression->left = NULL;
	expression->right = NULL;
	expression->Operator = '\0';
	expression->is_integer_constant = 0;
}

void set_common_subexpression_elimination(int enabled)
{
	int index;
	cse_enabled = enabled ? 1 : 0;
	entry_count = 0;
	control_depth = 0;
	for (index = 0; index < MAX_CSE_ENTRIES; ++index)
		entries[index].active = 0;
}

int common_subexpression_elimination_is_enabled()
{
	return cse_enabled;
}

void optimize_common_subexpressions(node *expression)
{
	if (!cse_enabled || control_depth != 0)
		return;
	optimize_node(expression);
}

void cse_invalidate_variable(const char *variable)
{
	int index;
	uint64_t dependency;
	int entry_index;
	if (!cse_enabled)
		return;
	index = optimization_safety_variable_index(variable);
	if (index < 0)
		return;
	dependency = ((uint64_t)1) << index;
	for (entry_index = 0; entry_index < entry_count; ++entry_index)
	{
		if ((entries[entry_index].dependencies & dependency) != 0)
			entries[entry_index].active = 0;
	}
}

void cse_enter_control()
{
	int index;
	if (!cse_enabled)
		return;
	entry_count = 0;
	for (index = 0; index < MAX_CSE_ENTRIES; ++index)
		entries[index].active = 0;
	control_depth++;
}

void cse_exit_control()
{
	int index;
	if (!cse_enabled)
		return;
	entry_count = 0;
	for (index = 0; index < MAX_CSE_ENTRIES; ++index)
		entries[index].active = 0;
	if (control_depth > 0)
		control_depth--;
}
