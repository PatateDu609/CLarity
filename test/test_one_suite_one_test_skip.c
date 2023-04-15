#include <CLarity/clarity.h>

void test_skip(clarity_test_t *t, void *data) {
	(void)data;
	cl_skip_test(t, "skipped");
}

int main() {
	clarity_suite_t *suite = cl_create_suite("Basic suite with one test");
	clarity_test_t *test = cl_create_test("basic test skip", test_skip, NULL);

	cl_add_test(suite, test);

	bool result = cl_run_suite(suite);

	cl_free_suite(suite);

	return !result;
}