#ifndef CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H
#define CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* Opaque type representing a test case in the Clarity testing framework.
*
* Test cases are created using `clarity_test_create()` and must be passed to
* the `clarity_suite_add_test()` function to be executed as part of a test suite.
*
* The `clarity_test_t` type should not be accessed directly by the user of the
* Clarity framework, and should be treated as an opaque type. Any interaction
* with the `clarity_test_t` object should be done through the provided functions
* in the Clarity API.
*/
typedef struct clarity_test_s clarity_test_t;

/**
 * @brief Type definition for a clarity test function.
 *
 * @details
 * A clarity test function is a function that takes a pointer to a clarity_test_t struct
 * and a pointer to arbitrary data and returns void. This typedef is used to define the
 * signature of test functions that are registered with CLarity using the
 * `clarity_register_tests` function.
 *
 * @param t A pointer to the clarity_test_t struct for the test being executed.
 * @param data A pointer to arbitrary data that can be used by the test function.
 *
 * Example:
 * ```
 * void my_test_function(clarity_test_t *t, void *data) {
 *     // perform test logic
 * }
 *
 * int main(int argc, char **argv) {
 *     clarity_register_tests(my_test_function);
 *     cl_run_tests(argc, argv);
 * }
 * ```
 */
typedef void (*clarity_test_fn_t)(clarity_test_t *t, void *data);

/**
 * @brief The possible status codes returned by Clarity functions.
 */
typedef enum clarity_status_e {
	CL_SUCCESS, /**< The operation succeeded. */
	CL_ERROR_MEMORY, /**< There was an error allocating memory. */
	CL_ERROR_SUITE_NULL, /**< The suite was NULL, no operation was performed. */
}            clarity_status_t;

/**
 * @brief Opaque structure representing a test suite.
 *
 * A test suite is a collection of related test cases.
 *
 * Instances of this structure should be created with clarity_create_suite()
 * and freed with clarity_free_suite().
 */
typedef struct clarity_suite_s clarity_suite_t;

/**
 * @brief A fixtures is a group of setup and teardown functions that are associated with a suite.
 *        Fixtures are executed once per test, before and after the test function.
 */
typedef struct clarity_fixture_s clarity_fixture_t;

/**
 * @brief Function signature for test setup function.
 *
 * @param data Custom user data.
 * @return int 0 on success, non-zero on failure.
 */
typedef int (*clarity_setup_fn_t)(void *data);

/**
 * @brief Function signature for test teardown function.
 *
 * @param data Custom user data.
 *
 * @return int 0 on success, non-zero on failure.
 */
typedef int (*clarity_teardown_fn_t)(void *data);

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_CLARITY_TYPES_H
