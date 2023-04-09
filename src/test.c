#include <CLarity/test.h>
#include "test.h"

clarity_test_t *cl_create_test(const char *name, clarity_test_fn_t fn, void *data) {
	clarity_test_t *test = calloc(1, sizeof(*test));
	if (!test)
		return NULL;

	test->name = name;
	test->test_fn = fn;
	test->user_data = data;

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