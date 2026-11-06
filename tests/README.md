# Constant-folding test inputs

These files use the compiler's current restricted C-like grammar: identifiers
are one character and declarations are not supported.

Run each source with and without `--const-fold`.  With folding enabled:

- `constant_folding_simple.c` must assign `14` to `x`.
- `constant_folding_nested.c` must assign `75` to `x`.
- `constant_folding_variable.c` may fold `5 * 2`, but must retain `a + 10`.
- `constant_folding_divide_by_zero.c` must retain `10 / 0`.
- `constant_folding_boundaries.c` must fold `0 - 5` to `-5`, and retain the
  overflowing addition and `INT32_MIN / -1` expression.

## Constant propagation test inputs

Run these with `--const-propagation --const-fold` to exercise both passes.
`constant_propagation_sequential.c` and
`constant_propagation_dependencies.c` must replace known identifiers and fold
the resulting arithmetic. `constant_propagation_reassignment.c` must stop
propagating `a` after `a = x`. `constant_propagation_unknown.c` must retain
unknown values. The `if`, `if/else`, and `while` boundary inputs must not
propagate `a` into or out of those control-flow constructs.

## Dead-code elimination test inputs

Run these with `--dead-code`. DCE removes only assignments whose final RHS is
a proven integer constant and whose value is never read. The unused and
overwritten tests exercise both removal reasons; used, chained, and
variable-expression cases must be retained when DCE runs alone. The control
boundary tests retain assignments before, within, and after `if` and `while`.
The interaction
test is intended for `--dead-code --const-propagation --const-fold`.

## Common subexpression elimination test inputs

Run these with `--cse`. The within-tree, sequential, and commutative inputs
must emit one calculation for each repeated addition. Reassignment must force
a fresh calculation. The control-boundary input must not reuse a result from
outside an `if`, and division is reused only when its denominator is a proven
non-zero integer constant. `cse_all_passes.c` runs with all optimizer flags.

## Optimization safety test inputs

`optimization_safety_normal.c` verifies safe folding. Existing folding
boundary and divide-by-zero inputs verify signed-overflow and division guards.
`optimization_safety_unsupported.c` verifies that floating expressions remain
unchanged, and `optimization_safety_rejected_division.c` verifies that CSE does
not reuse division with an unknown denominator. Rejected transformations are
reported through the shared safety log.

## Adaptive pass-selection test inputs

Run these with `--auto-opt`. The constants, constant-assignment, repeated,
dead-assignment, and multiple-opportunity programs select only relevant passes
and report transformations actually performed. `auto_opt_none.c` reports every
pass skipped. Use `--auto-opt --no-cse` with `auto_opt_repeated.c` to verify
that an explicit disable overrides automatic selection.

## Unified optimization report test inputs

Use `--report` with each pass's existing inputs to verify that only real
transformations are counted. In particular, run the divide-by-zero case with
`--const-fold --report`: it must report a safety rejection and zero folding
transformations. `--auto-opt --report` includes selector decisions.

Use `--report-json` with `report_json.c`; extract the text between
`BEGIN_OPTIMIZATION_REPORT_JSON` and `END_OPTIMIZATION_REPORT_JSON` before
passing it to a JSON parser, because normal compiler logs are preserved.

## TAC effectiveness test inputs

Run with `--stats` or `--report`. For `constant_folding_nested.c`, baseline
and unoptimized TAC are both four instructions; with `--const-fold`, final TAC
is one instruction. `dead_code_overwritten.c` is three instructions without
DCE and two after deferred DCE removes its overwritten assignment.
`effectiveness_zero.c` is a leaf expression statement and therefore has zero
baseline and zero optimized TAC instructions; it verifies safe zero handling.

## Interactive menu checks

Run `./compiler` with no arguments. Test menu entries 1 through 11 using the
default input file, entry 8 with a mixed `Y/N` configuration, invalid text
followed by entry 12, and a nonexistent input path followed by entry 12.
Command-line test commands remain unchanged because the menu is entered only
when no arguments are supplied.
