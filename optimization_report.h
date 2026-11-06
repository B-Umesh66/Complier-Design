#ifndef OPTIMIZATION_REPORT_H
#define OPTIMIZATION_REPORT_H

/* Reporting is observational: it never enables or changes an optimization. */
void optimization_report_set_enabled(int enabled);
void optimization_report_set_json(int enabled);
int optimization_report_is_enabled(void);

void optimization_report_record_transformation(const char *optimization,
	const char *original, const char *optimized, const char *reason);
void optimization_report_record_rejection(const char *optimization,
	const char *expression, const char *reason);
void optimization_report_record_pass(const char *pass, const char *status,
	const char *reason, int safe_candidates);
void optimization_report_set_tac_statistics(int original_instructions,
	int optimized_instructions);
void optimization_report_print(void);

#endif
