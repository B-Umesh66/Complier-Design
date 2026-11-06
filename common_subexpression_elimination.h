#ifndef COMMON_SUBEXPRESSION_ELIMINATION_H
#define COMMON_SUBEXPRESSION_ELIMINATION_H

#include "node.h"

void set_common_subexpression_elimination(int enabled);
int common_subexpression_elimination_is_enabled();
void optimize_common_subexpressions(node *expression);
void cse_invalidate_variable(const char *variable);
void cse_enter_control();
void cse_exit_control();

#endif
