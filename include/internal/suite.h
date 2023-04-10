#ifndef CLARITY_INCLUDE_INTERNAL_SUITE_H
#define CLARITY_INCLUDE_INTERNAL_SUITE_H

#include <CLarity/clarity.h>
#include <CLarity/suite.h>
#include <CLarity/clarity_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A suite containing a collection of related tests.
 *
 * The `cl_suite_s` struct is used to group related tests together. Each suite
 * can have an optional setup function that runs before any tests in the suite
 * are executed, and an optional teardown function that runs after all the tests
 * have completed.
 */
struct clarity_suite_s {
	/**
	 * @brief The name of the suite.
	 */
	const char *name;

	/**
	 * @brief A pointer to a setup function for the suite.
	 *
	 * This function is run once before any tests in the suite are executed. If
	 * `setup` is `NULL`, no setup function is run.
	 *
	 * @param[in] data A pointer to user-defined data to be passed to the setup
	 *                 function. If there is no user-defined data, this should
	 *                 be `NULL`.
	 *
	 * @return `CL_SUCCESS` if the setup function completes successfully,
	 *         otherwise an error code indicating the reason for the failure.
	 */
	clarity_setup_fn_t setup;

	/**
	 * @brief The data to pass to the setup function.
	 */
	void *setup_data;

	/**
	 * @brief A pointer to a teardown function for the suite.
	 *
	 * This function is run once after all the tests in the suite are executed.
	 * If `teardown` is `NULL`, no teardown function is run.
	 *
	 * @param[in] data A pointer to user-defined data to be passed to the
	 *                 teardown function. If there is no user-defined data,
	 *                 this should be `NULL`.
	 *
	 * @return `CL_SUCCESS` if the teardown function completes successfully,
	 *         otherwise an error code indicating the reason for the failure.
	 */
	clarity_teardown_fn_t teardown;

	/**
	 * @brief The data to pass to the teardown function.
	 */
	void *teardown_data;

	/**
	 * @brief The number of tests in the suite.
	 */
	size_t test_count;

	/**
	 * @brief The number of tests the suite can accept at the moment without doing any reallocation.
	 */
	size_t test_capacity;

	/**
	 * @brief An array of pointers to the tests in the suite.
	 */
	clarity_test_t **tests;
};

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_INTERNAL_SUITE_H
