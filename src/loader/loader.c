#include "loader.h"
#include <stdlib.h>

clarity_status_t cl_cleanup_loader(clarity_loader_t *loader) {
	clarity_status_t status = cl_unload_library(loader);

	if (status == CL_SUCCESS || status == CL_ERROR_LIBRARY_NOT_LOADED){
		status = CL_SUCCESS;
		free(loader);
	}

	return status;
}