#ifndef DEAD_CODE_ELIMINATION_H
#define DEAD_CODE_ELIMINATION_H

#include "node.h"

void set_dead_code_elimination(int enabled);
int dead_code_elimination_is_enabled();
void dce_mark_expression_used(node *expression);
void dce_record_assignment(const char *variable, node *expression,
	int first_quad, int last_quad);
void dce_enter_control();
void dce_exit_control();
void dce_finalize();
void dce_emit_surviving_register_code();

#endif
