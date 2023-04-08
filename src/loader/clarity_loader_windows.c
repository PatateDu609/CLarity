#include "loader.h"
#include <windows.h>

/**
 * @brief Windows-specific data for the clarity library loader.
 */
struct clarity_loader_s {
	HMODULE handle; /**< The handle to the loaded library. */
};

clarity_loader_t *cl_new_loader() {
	clarity_loader_t *loader = calloc(1, sizeof(*loader));
	if (loader == NULL) return NULL;

	return loader;
}

clarity_status_t cl_load_library(clarity_loader_t *loader, const char *path) {
	loader->handle = LoadLibrary(path);
	if (!loader->handle) {
		DWORD error_code = GetLastError();

		switch (error_code) {
			case ERROR_MOD_NOT_FOUND:
				return CL_ERROR_FILE_NOT_FOUND;
			case ERROR_INVALID_PARAMETER:
				return CL_ERROR_INVALID_FORMAT;
			default:
				return CL_ERROR_LOAD_LIBRARY;
		}
	}

	return CL_SUCCESS;
}

clarity_status_t cl_unload_library(clarity_loader_t *loader) {
	if (!loader->handle)
		return CL_ERROR_LIBRARY_NOT_LOADED;

	if (!FreeLibrary(loader->handle))
		return CL_ERROR_UNLOAD_LIBRARY;

	return CL_SUCCESS;
}

clarity_test_fn_t cl_lookup_test(clarity_loader_t *loader, const char *name) {
	if (!loader->handle)
		return NULL;
	return (clarity_test_fn_t) GetProcAddress(loader->handle, name);
}
