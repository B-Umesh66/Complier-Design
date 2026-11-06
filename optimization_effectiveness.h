#ifndef OPTIMIZATION_EFFECTIVENESS_H
#define OPTIMIZATION_EFFECTIVENESS_H

#include "node.h"

/* Counts TAC only; it does not estimate execution time or machine-code size. */
void optimization_effectiveness_set_enabled(int enabled);
void optimization_effectiveness_set_stats_output(int enabled);
int optimization_effectiveness_is_enabled(void);
void optimization_effectiveness_record_expression(const node *expression);
void optimization_effectiveness_record_assignment(void);
void optimization_effectiveness_record_condition(void);
void optimization_effectiveness_record_jump(void);
void optimization_effectiveness_finalize(int first_quad, int next_quad,
	char code[100][50]);
void optimization_effectiveness_print_stats(void);

#endif
