#include <CLarity/suite.h>
#include <string.h>
#include "suite.h"
#include "test.h"

#define CL_DEFAULT_SUITE_CAPACITY 16


clarity_suite_t *cl_create_suite(const char *name) {
	clarity_suite_t *suite = calloc(1, sizeof(*suite));
	if (!suite)
		return NULL;

	suite->name             = name;
	suite->suite_fixture    = NULL;
	suite->test_capacity    = 0;
	suite->test_count       = 0;
	suite->tests            = NULL;
	suite->fixture_capacity = 0;
	suite->fixture_count    = 0;
	suite->fixtures         = NULL;

	return suite;
}


void cl_suite_register_setup(clarity_suite_t *suite, clarity_setup_fn_t fn, void *data) {
	if (!suite->suite_fixture) {
		suite->suite_fixture = cl_create_fixture(fn, data, NULL, NULL);
	} else {
		suite->suite_fixture->setup      = fn;
		suite->suite_fixture->setup_data = data;
	}
}


void cl_suite_register_teardown(clarity_suite_t *suite, clarity_teardown_fn_t fn, void *data) {
	if (!suite->suite_fixture) {
		suite->suite_fixture = cl_create_fixture(NULL, NULL, fn, data);
	} else {
		suite->suite_fixture->teardown      = fn;
		suite->suite_fixture->teardown_data = data;
	}
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

	if (suite->fixture_count) {
		for (size_t i = 0; i < suite->fixture_count; i++) {
			cl_free_fixture(suite->fixtures[i]);
		}
	}
	free(suite->fixtures);

	cl_free_fixture(suite->suite_fixture);
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

	int status = 0;
	if (cl_fixture_run_setup(suite->suite_fixture, &status)) {
		if (status)
			return false;
	}


	for (size_t i = 0; i < suite->test_count; i++) {
		for (size_t j = 0; j < suite->fixture_count; j++) {
			if (cl_fixture_run_setup(suite->fixtures[j], &status)) {
				if (status) {
					return false;
				}
			}
		}


		clarity_test_result_t result = cl_run_test(suite->tests[i]);
		cl_print_test_result(&result);

		report.total_tests++;
		if (result.skipped)
			report.skipped_tests++;
		else if (result.passed)
			report.succeeded_tests++;
		else
			report.failed_tests++;

		bool state = true;
		for (int64_t          j      = (int64_t) (suite->fixture_count - 1); j >= 0; j--) {
			if (cl_fixture_run_teardown(suite->fixtures[j], &status) && status)
				state = false;
		}
		if (!state)
			return false;
	}

	if (cl_fixture_run_teardown(suite->suite_fixture, &status)) {
		if (status)
			return false;
	}

	cl_print_suite_report(&report);

	return report.failed_tests == 0;
}


bool cl_fixture_run_setup(clarity_fixture_t *fixture, int *status_code) {
	if (!fixture || !fixture->setup)
		return false;

	int status = fixture->setup(fixture->setup_data);
	if (status_code)
		*status_code = status;

	return true;
}


bool cl_fixture_run_teardown(clarity_fixture_t *fixture, int *status_code) {
	if (!fixture || !fixture->teardown)
		return false;

	int status = fixture->teardown(fixture->teardown_data);
	if (status_code)
		*status_code = status;

	return true;
}


clarity_status_t cl_suite_add_fixture(clarity_suite_t  *suite, clarity_fixture_t *fixture) {
	if (!fixture)
		return CL_SUCCESS;

	if (!suite)
		return CL_ERROR_SUITE_NULL;

	if (suite->fixture_capacity == 0) {
		clarity_fixture_t **fixtures = calloc(CL_DEFAULT_SUITE_CAPACITY, sizeof(clarity_fixture_t *));
		if (!fixtures)
			return CL_ERROR_MEMORY;
		suite->fixture_capacity = CL_DEFAULT_SUITE_CAPACITY;
		suite->fixtures         = fixtures;
	} else if (suite->fixture_count >= suite->fixture_capacity) {
		size_t max = suite->fixture_capacity * 2;
		if (max > 512)
			max = 512;
		size_t new_capacity = max + suite->fixture_capacity;

		clarity_fixture_t **fixtures = realloc(suite->fixtures, new_capacity * sizeof(clarity_fixture_t *));
		if (!fixtures)
			return CL_ERROR_MEMORY;
		suite->fixtures         = fixtures;
		suite->fixture_capacity = new_capacity;
	}
	suite->fixtures[suite->fixture_count++] = fixture;

	return CL_SUCCESS;
}


clarity_fixture_t *cl_create_fixture(clarity_setup_fn_t setup_fn, void *setup_data, clarity_teardown_fn_t teardown_fn,
                                     void *teardown_data) {
	clarity_fixture_t *fixture = calloc(1, sizeof(*fixture));
	if (!fixture)
		return NULL;

	fixture->setup         = setup_fn;
	fixture->setup_data    = setup_data;
	fixture->teardown      = teardown_fn;
	fixture->teardown_data = teardown_data;

	return fixture;
}


void cl_free_fixture(clarity_fixture_t *fixture) {
	if (!fixture)
		return;
	free(fixture);
}
