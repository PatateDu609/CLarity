#include <CLarity/clarity.h>

void test_add_s(clarity_test_t *, void *) {

}

int main() {
	clarity_suite_t *suite = cl_create_suite("Basic suite with one test", NULL, NULL, NULL, NULL);
	clarity_test_t *test = cl_create_test("basic test", test_add_s, NULL);

	cl_add_test(suite, test);

	bool result = cl_run_suite(suite);

	cl_free_suite(suite);

	return !result;
}