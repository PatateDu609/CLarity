#include <CLarity/suite.h>
#include "suite.h"

clarity_suite_t *cl_create_suite(const char *name, clarity_setup_fn_t setup_fn, clarity_teardown_fn_t teardown_fn) {
	clarity_suite_t *suite = calloc(1, sizeof(*suite));
	if (!suite)
		return NULL;

	suite->name = name;
	suite->setup = setup_fn;
	suite->teardown = teardown_fn;
	suite->test_capacity = 0;
	suite->test_count = 0;
	suite->tests = NULL;

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

	free(suite);
}

clarity_status_t cl_add_test(clarity_suite_t *suite, clarity_test_t *test) {
	if (!test)
		return CL_SUCCESS;

	if (!suite)
		return CL_ERROR_SUITE_NULL;

	if (suite->test_count >= suite->test_capacity)
	{
		size_t max = suite->test_capacity;
		if (max > 512)
			max = 512;
		size_t new_capacity = max + suite->test_capacity;

		clarity_test_t **tests = realloc(suite->tests, new_capacity);
		if (!tests)
			return CL_ERROR_MEMORY;
		suite->tests = tests;
		suite->test_capacity = new_capacity;
	}
	suite->tests[suite->test_count++] = test;

	return CL_SUCCESS;
}

bool cl_run_suite(clarity_suite_t *suite) {
	if (!suite) {
		return true;
	}

	if (suite->setup) {
		clarity_status_t status = suite->setup(suite->setup_data);
		if (status != CL_SUCCESS)
			return false;
	}


	if (suite->teardown) {
		clarity_status_t status = suite->teardown(suite->teardown_data);
		if (status != CL_SUCCESS)
			return false;
	}

	return true;
}