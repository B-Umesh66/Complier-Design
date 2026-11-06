#ifndef PASS_SELECTOR_H
#define PASS_SELECTOR_H

#include "node.h"

typedef enum optimization_pass
{
	PASS_CONSTANT_FOLDING = 0,
	PASS_CONSTANT_PROPAGATION,
	PASS_DEAD_CODE_ELIMINATION,
	PASS_COMMON_SUBEXPRESSION_ELIMINATION,
	PASS_COUNT
} optimization_pass;

void pass_selector_set_auto(int enabled);
int pass_selector_auto_is_enabled();
void pass_selector_note_manual_option(optimization_pass pass, int enabled);
void pass_selector_analyze_expression(node *expression);
void pass_selector_analyze_folding(node *expression);
void pass_selector_analyze_assignment(const char *variable, node *expression);
void pass_selector_enter_control();
void pass_selector_exit_control();
void pass_selector_record_transformation(optimization_pass pass);
void pass_selector_report();

#endif
