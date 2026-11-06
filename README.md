# C Compiler — Code Optimizer and Evaluator

This is an educational, restricted C-like compiler implemented with Lex/Flex,
Yacc/Bison, and a C++ compilation driver. It supports one-character
identifiers, numeric literals, arithmetic expressions, assignments, `if`,
`else`, and `while`; it is not a full ISO C compiler.

## Constant folding

The first optimization pass is optional and folds safe signed 32-bit integer
subexpressions using `+`, `-`, `*`, and `/`. It logs each transformation and
does not fold division by zero or an operation whose result is outside the
signed 32-bit range.

Legacy behavior is the default:

```text
compiler <registers> < input.txt
```

## Interactive terminal menu

Run the compiler with no arguments to open the terminal menu:

```text
./compiler
```

The menu offers unoptimized, individual, adaptive, all-pass, custom, TAC
statistics, explainable-report, and complete-analysis modes. It asks for an
input file (default `input.txt`) and register count (default `3`), shows the
selected configuration, then passes the selected file to the existing Flex
lexer. Custom mode asks `Y/N` for each of the four optimization passes.

All command-line behavior remains available when arguments are supplied:

```text
./compiler 3 --const-fold --report < tests/constant_folding_nested.c
```

Enable folding explicitly:

```text
compiler <registers> --const-fold < tests/constant_folding_nested.c
```

Enable propagation and folding together:

```text
compiler <registers> --const-propagation --const-fold < tests/constant_propagation_dependencies.c
```

Use `--no-const-fold` or `--no-const-propagation` to state the defaults
explicitly. Propagation tracks only straight-line assignments and deliberately
discards known values at `if`, `else`, and `while` boundaries.

Enable dead-code elimination with either optimization pass:

```text
compiler <registers> --dead-code --const-propagation --const-fold < tests/dead_code_interaction.c
```

DCE removes only proven-safe, unused integer-constant assignments. It retains
all assignments at and after control-flow boundaries, plus expressions not
proven safe.

Enable common subexpression elimination:

```text
compiler <registers> --cse < tests/cse_sequential.c
```

CSE reuses structurally identical arithmetic expressions only in straight-line
code. It clears its cache at each control-flow boundary and invalidates entries
when a dependent variable is reassigned.

## Optimization safety

`optimization_safety.c` centralizes integer overflow, division, expression,
and optimizer-eligibility checks. Unsafe transformations are rejected with a
reason and leave the existing AST/TAC representation unchanged. This remains a
restricted educational compiler rather than a complete C implementation.

## Adaptive pass selection

Use `--auto-opt` to enable a deterministic streaming selector. It observes
supported AST candidates as the parser processes each expression, selects only
the relevant existing passes, and reports detected candidates plus the number
of transformations actually performed. Explicit `--no-const-fold`,
`--no-const-propagation`, `--no-dead-code`, and `--no-cse` options always take
precedence.

```text
compiler <registers> --auto-opt < tests/auto_opt_multiple.c
compiler <registers> --auto-opt --no-cse < tests/auto_opt_repeated.c
```

## Unified explainable optimization report

Use `--report` to collect transformations actually performed by the existing
passes, safety rejections, per-pass totals, and pass-selection decisions. It
does not enable an optimization or alter generated TAC. Existing per-pass logs
remain visible.

```text
compiler <registers> --const-fold --report < tests/constant_folding_nested.c
compiler <registers> --auto-opt --report < tests/auto_opt_multiple.c
```

`--report-json` enables the same collection and emits a JSON object between
`BEGIN_OPTIMIZATION_REPORT_JSON` and `END_OPTIMIZATION_REPORT_JSON`. Other
legacy compiler output is intentionally retained outside those delimiters.

## TAC effectiveness statistics

`--stats` prints concise TAC instruction counts. `--report` and
`--report-json` include the same metrics automatically. The baseline is a
dry-run of this compiler's unoptimized TAC emission rules on the original AST:
each arithmetic emission, assignment, conditional branch pair, and generated
unconditional jump is counted before an optimization can mutate the AST. The
optimized count is the number of non-empty final TAC slots after deferred DCE
has completed.

```text
compiler <registers> --const-fold --stats < tests/constant_folding_nested.c
compiler <registers> --dead-code --report < tests/dead_code_overwritten.c
```

These values measure TAC instruction reduction only. They do not claim or
predict execution-time, executable-size, or machine-code performance changes.

## Build

Install a Lex/Flex implementation, a Yacc/Bison implementation, and `g++`.
The lexer expects the traditional `y.tab.h` name, so use Yacc-compatible
generation options. A typical command sequence is:

```text
yacc -d yacc.y
lex lex.l
g++ y.tab.c lex.yy.c optimization_safety.c optimization_report.c optimization_effectiveness.c pass_selector.c constant_folding.c constant_propagation.c dead_code_elimination.c common_subexpression_elimination.c -lfl -o compiler
```

On Windows, use the equivalent commands supplied by the selected
Flex/Bison distribution.

The `tests/` directory contains source inputs for constant-folding cases.
