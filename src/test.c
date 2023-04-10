#include <CLarity/test.h>
#include "test.h"
#include <string.h>

clarity_test_t *cl_create_test(const char *name, clarity_test_fn_t fn, void *data) {
	if (!fn || !name)
		return NULL;

	clarity_test_t *test = calloc(1, sizeof(*test));
	if (!test)
		return NULL;

	test->name = name;
	test->test_fn = fn;
	test->user_data = data;
	test->result.name = test->name;
	test->result.skipped = false;
	test->result.passed = true;

	return test;
}

const char *cl_get_test_name(clarity_test_t *test) {
	if (!test)
		return NULL;
	return test->name;
}

void *cl_get_test_data(clarity_test_t *test) {
	if (!test)
		return NULL;
	return test->user_data;
}

void cl_free_test(clarity_test_t *test) {
	free(test);
}

clarity_test_result_t cl_run_test(clarity_test_t *test) {
	if (!test)
		return (clarity_test_result_t){};

	if (test->result.skipped)
		return test->result;

	test->test_fn(test, test->user_data);
	return test->result;
}