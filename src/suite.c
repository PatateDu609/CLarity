#include <CLarity/suite.h>
#include <string.h>
#include "suite.h"
#include "test.h"

#define CL_DEFAULT_SUITE_CAPACITY 16


clarity_suite_t *
cl_create_suite(const char *name, clarity_setup_fn_t setup_fn, void *setup_data, clarity_teardown_fn_t teardown_fn,
                void *teardown_data) {
	clarity_suite_t *suite = calloc(1, sizeof(*suite));
	if (!suite)
		return NULL;

	suite->name          = name;
	suite->setup         = setup_fn;
	suite->setup_data    = setup_data;
	suite->teardown      = teardown_fn;
	suite->teardown_data = teardown_data;
	suite->test_capacity = 0;
	suite->test_count    = 0;
	suite->tests         = NULL;

	return suite;
}


void cl_free_suite(clarity_suite_t *suite) {
	if (!suite)
		return;
	if (suite->test_count) {
		for (size_t i = 0; i < suite->test_count; i++) {
			cl_free_test(suite->tests[i]);
		}
	}
	free(suite->tests);

	free(suite);
}


clarity_status_t cl_add_test(clarity_suite_t *suite, clarity_test_t *test) {
	if (!test)
		return CL_SUCCESS;

	if (!suite)
		return CL_ERROR_SUITE_NULL;

	if (suite->test_capacity == 0) {
		clarity_test_t **tests = calloc(CL_DEFAULT_SUITE_CAPACITY, sizeof(clarity_test_t *));
		if (!tests)
			return CL_ERROR_MEMORY;
		suite->test_capacity = CL_DEFAULT_SUITE_CAPACITY;
		suite->tests         = tests;
	} else if (suite->test_count >= suite->test_capacity) {
		size_t max = suite->test_capacity * 2;
		if (max > 512)
			max = 512;
		size_t new_capacity = max + suite->test_capacity;

		clarity_test_t **tests = realloc(suite->tests, new_capacity * sizeof(clarity_test_t *));
		if (!tests)
			return CL_ERROR_MEMORY;
		suite->tests         = tests;
		suite->test_capacity = new_capacity;
	}
	suite->tests[suite->test_count++] = test;

	return CL_SUCCESS;
}


bool cl_run_suite(clarity_suite_t *suite) {
	if (!suite || !suite->test_count) {
		return true;
	}

	cl_print_suite_name(suite->name);
	clarity_suite_report_t report;
	memset(&report, 0, sizeof report);
	report.name = suite->name;

	if (suite->setup) {
		clarity_status_t status = suite->setup(suite->setup_data);
		if (status != CL_SUCCESS)
			return false;
	}

	for (size_t i = 0; i < suite->test_count; i++) {
		clarity_test_result_t result = cl_run_test(suite->tests[i]);
		cl_print_test_result(&result);

		report.total_tests++;
		if (result.skipped)
			report.skipped_tests++;
		else if (result.passed)
			report.succeeded_tests++;
		else
			report.failed_tests++;
	}

	if (suite->teardown) {
		clarity_status_t status = suite->teardown(suite->teardown_data);
		if (status != CL_SUCCESS)
			return false;
	}

	cl_print_suite_report(&report);

	return report.failed_tests == 0;
}