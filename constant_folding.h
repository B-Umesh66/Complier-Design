#ifndef CONSTANT_FOLDING_H
#define CONSTANT_FOLDING_H

#include "node.h"

/* Folding is deliberately opt-in so the legacy compiler path remains available. */
void set_constant_folding(int enabled);
int constant_folding_is_enabled();

/* Folds safe, signed 32-bit integer subexpressions in place. */
void optimize_constant_expression(node *expression);

#endif
