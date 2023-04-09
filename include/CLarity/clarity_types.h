#ifndef CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H
#define CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type definition for a clarity test function.
 *
 * @details
 * A clarity test function is a function that takes no arguments and returns void.
 * This typedef is used to define the signature of test functions that are registered
 * with CLarity using the `clarity_register_tests` function.
 *
 * Example:
 * ```
 * void my_test_function(void) {
 *     // perform test logic
 * }
 *
 * int main(int argc, char **argv) {
 *     clarity_register_tests(my_test_function);
 *     cl_run_tests(argc, argv);
 * }
 * ```
 */
typedef void (*clarity_test_fn_t)(void);

/**
 * @brief The possible status codes returned by Clarity functions.
 */
typedef enum clarity_status_e {
	CL_SUCCESS, /**< The operation succeeded. */
	CL_ERROR_MEMORY, /**< There was an error allocating memory. */
	CL_ERROR_INVALID_ARGUMENT, /**< An argument provided to the function was invalid. */
	CL_ERROR_FILE_NOT_FOUND, /**< A required file was not found. */
	CL_ERROR_LOAD_LIBRARY, /**< There was an error loading a dynamic library. */
	CL_ERROR_INVALID_FORMAT, /**< A dynamic library had an invalid format. */
	CL_ERROR_LIBRARY_NOT_LOADED, /**< A required dynamic library was not loaded. */
	CL_ERROR_UNLOAD_LIBRARY, /**< There was an error unloading a dynamic library. */
	CL_ERROR_SUITE_NULL, /**< The suite was NULL, no operation was performed. */
}            clarity_status_t;

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H
