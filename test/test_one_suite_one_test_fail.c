#include <CLarity/clarity.h>

void test_fail(clarity_test_t *t, void *data) {
	(void)data;
	cl_fail_test(t, "failed");
}

int main() {
	clarity_suite_t *suite = cl_create_suite("Basic suite with one test");
	clarity_test_t *test = cl_create_test("basic test fail", test_fail, NULL);

	cl_add_test(suite, test);

	bool result = cl_run_suite(suite);

	cl_free_suite(suite);

	return !result;
}