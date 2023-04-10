#include <CLarity/clarity.h>
#include <stdlib.h>
#include "loader.h"


void cl_run_tests(int ac, char **av) {
	int ret = 0;

	exit(ret);
}


clarity_status_t cl_load_tests(const char *library_path) {
	if (!library_path || !*library_path)
		return CL_ERROR_INVALID_ARGUMENT;

	clarity_loader_t *loader = cl_new_loader();
	if (!loader)
		return CL_ERROR_MEMORY;

	clarity_status_t status;

	if ((status = cl_load_library(loader, library_path)) != CL_SUCCESS)
	{
		cl_cleanup_loader(loader);
		return status;
	}

	clarity_test_fn_t register_tests = cl_lookup_test(loader, "clarity_register_tests");
	if (!register_tests) {
		cl_cleanup_loader(loader);
		return CL_ERROR_INVALID_FORMAT;
	}
	register_tests();

	return cl_cleanup_loader(loader);
}
