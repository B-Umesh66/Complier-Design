#ifndef CONSTANT_PROPAGATION_H
#define CONSTANT_PROPAGATION_H

#include "node.h"

/* Propagation is opt-in and has no effect on the legacy compiler mode. */
void set_constant_propagation(int enabled);
int constant_propagation_is_enabled();

/* Replaces known variable leaves in an expression with integer constants. */
void propagate_constants(node *expression);

/* Updates the straight-line assignment facts after an assignment is emitted. */
void record_constant_assignment(const char *variable, node *expression);

/* Discards facts at control-flow boundaries. */
void clear_constant_bindings();

#endif
