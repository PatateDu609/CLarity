#include <CLarity/clarity.h>


void test1(clarity_test_t *t, void *data) {
	(void) t;
	(void) data;
}


void test2(clarity_test_t *t, void *data) {
	(void) t;
	(void) data;
}


void test3(clarity_test_t *t, void *data) {
	(void) data;

	cl_fail_test(t, "this is the test 3, and it should fail");
}


void test4(clarity_test_t *t, void *data) {
	(void) data;

	cl_fail_test(t, "this is the test 4, and it should fail");
}


void test5(clarity_test_t *t, void *data) {
	(void) data;

	cl_fail_test(t, "this is the test 5, and it should fail");
}


void test6(clarity_test_t *t, void *data) {
	(void) data;

	cl_skip_test(t, "this is the test 6, and it should be skipped");
}


void test7(clarity_test_t *t, void *data) {
	(void) data;

	cl_skip_test(t, "this is the test 7, and it should be skipped");
}


void test8(clarity_test_t *t, void *data) {
	(void) data;

	cl_skip_test(t, "this is the test 8, and it should be skipped");
}


void test9(clarity_test_t *t, void *data) {
	(void) data;

	cl_skip_test(t, "this is the test 9, and it should be skipped");
}


void test10(clarity_test_t *t, void *data) {
	(void) data;

	cl_fail_test(t, "this is the test 10, and it should fail");
}


void test11(clarity_test_t *t, void *data) {
	(void)t;
	(void) data;
}

void test12(clarity_test_t *t, void *data) {
	(void)data;

	cl_fail_test(t, "this is the test 12, and it should fail");
}

int main() {
	clarity_suite_t *s1 = cl_create_suite("Suite 1");
	clarity_suite_t *s2 = cl_create_suite("Suite 2");
	clarity_suite_t *s3 = cl_create_suite("Suite 3");

	clarity_test_t  *t01    = cl_create_test("test 01 - should pass", test1, NULL);
	clarity_test_t  *t02    = cl_create_test("test 02 - should pass", test2, NULL);
	clarity_test_t  *t03    = cl_create_test("test 03 - should fail", test3, NULL);
	clarity_test_t  *t04    = cl_create_test("test 04 - should fail", test4, NULL);
	clarity_test_t  *t05    = cl_create_test("test 05 - should fail", test5, NULL);
	clarity_test_t  *t06    = cl_create_test("test 06 - should skip", test6, NULL);
	clarity_test_t  *t07    = cl_create_test("test 07 - should skip", test7, NULL);
	clarity_test_t  *t08    = cl_create_test("test 08 - should skip", test8, NULL);
	clarity_test_t  *t09    = cl_create_test("test 09 - should skip", test9, NULL);
	clarity_test_t  *t10    = cl_create_test("test 10 - should fail", test10, NULL);
	clarity_test_t  *t11    = cl_create_test("test 11 - should pass", test11, NULL);
	clarity_test_t  *t12    = cl_create_test("test 12 - should fail", test12, NULL);

	cl_add_test(s1, t01);
	cl_add_test(s1, t02);
	cl_add_test(s2, t03);
	cl_add_test(s3, t04);
	cl_add_test(s1, t05);
	cl_add_test(s3, t06);
	cl_add_test(s2, t07);
	cl_add_test(s2, t08);
	cl_add_test(s1, t09);
	cl_add_test(s2, t10);
	cl_add_test(s3, t11);
	cl_add_test(s1, t12);

	bool            result = cl_run_suite(s1);
	result &= cl_run_suite(s2);
	result &= cl_run_suite(s3);

	cl_free_suite(s1);
	cl_free_suite(s2);
	cl_free_suite(s3);

	return !result;
}