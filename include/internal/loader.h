#ifndef CLARITY_INCLUDE_INTERNAL_LOADER_H
#define CLARITY_INCLUDE_INTERNAL_LOADER_H

#include <CLarity/clarity.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A struct that abstracts the actual process of loading functions from libraries.
 *
 * The loader keeps track of the library and the functions that have been loaded from it.
 * The user should create a new loader using `cl_new_loader()`, load a library using
 * `cl_load_library()`, and unload the library using `cl_unload_library()`. The loader
 * should be freed using `cl_cleanup_loader()` when it is no longer needed.
 */
typedef struct clarity_loader_s clarity_loader_t;

/**
 * @brief Creates a new loader.
 *
 * The user should create a new loader for each library that needs to be loaded. The loader
 * keeps track of the library and the functions that have been loaded from it. When the
 * loader is no longer needed, it should be freed using `cl_cleanup_loader()`.
 *
 * @return A pointer to the new loader, or NULL if the memory allocation failed.
 *
 * @see cl_load_library(), cl_unload_library(), cl_cleanup_loader()
 */
clarity_loader_t *cl_new_loader();

/**
 * @brief Loads a library.
 *
 * This function loads a library and makes its functions available for use. The path to the
 * library should be provided as a string. If the library cannot be loaded, this function
 * returns an error status.
 *
 * @param loader A pointer to the loader.
 * @param path The path to the library.
 *
 * @return CLARITY_SUCCESS if the library was loaded successfully, or an error status
 * otherwise.
 *
 * @see cl_new_loader(), cl_unload_library()
 */
clarity_status_t cl_load_library(clarity_loader_t *loader, const char *path);

/**
 * @brief Unloads a library.
 *
 * This function unloads the library and frees any memory that was allocated by the loader.
 * If the library cannot be unloaded, this function returns an error status.
 *
 * @param loader A pointer to the loader.
 *
 * @return CLARITY_SUCCESS if the library was unloaded successfully, or an error status
 * otherwise.
 *
 * @see cl_new_loader(), cl_load_library()
 */
clarity_status_t cl_unload_library(clarity_loader_t *loader);

/**
 * @brief Deletes a loader.
 *
 * This function frees the memory that was allocated for the loader. If the loader is not
 * NULL, it also unloads the library associated with the loader. If the library cannot be
 * unloaded, this function returns an error status.
 *
 * @param loader A pointer to the loader.
 *
 * @return CLARITY_SUCCESS if the loader was deleted successfully, or an error status
 * otherwise.
 *
 * @see cl_new_loader(), cl_load_library(), cl_unload_library()
 */
clarity_status_t cl_cleanup_loader(clarity_loader_t *loader);

/**
 * @brief Looks up a test function in the loaded library.
 *
 * @details
 * This function looks up a test function with the given name in the currently loaded library
 * using the specified clarity loader. If the test function is found, a pointer to it is returned.
 * Otherwise, NULL is returned.
 *
 * @warning The returned function pointer should not be called directly. Instead, it should be
 * passed to the `cl_run_test()` function to execute the test.
 *
 * @param loader The clarity loader to use for the lookup.
 * @param name The name of the test function to look up.
 * @return A pointer to the test function, or NULL if not found.
 */
clarity_test_fn_t cl_lookup_test(clarity_loader_t *loader, const char *name);

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_INTERNAL_LOADER_H
