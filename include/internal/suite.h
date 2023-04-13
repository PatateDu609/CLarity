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
	 * @brief The fixtures to be used for each test in the suite.
	 *
	 * The fixtures should contain a setup and teardown function that will be called before and after each test in the suite.
	 * This fixtures will be applied to all tests in the suite.
	 */
	clarity_fixture_t *suite_fixture;

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

	/**
     * @brief The number of fixtures groups currently in the suite.
     */
	size_t fixture_count;

	/**
	 * @brief The capacity of the fixtures group array.
	 *
	 * This is the maximum number of fixtures groups that can be added to the suite before the fixtures group array needs to be resized.
	 */
	size_t fixture_capacity;

	/**
	 * @brief Array of pointers to the fixtures groups in the suite.
	 *
	 * The array contains `fixture_count` number of pointers to `clarity_fixture_t` structures.
	 *
	 * Each fixtures group contains a setup and teardown function, which will be called before and after all tests in the suite.
	 * Multiple fixtures groups can be added to a suite, but each fixtures group can only have one setup and one teardown function.
	 */
	clarity_fixture_t **fixtures;
};

/**
 * @struct clarity_fixture_s
 * @brief Represents a fixtures associated with a suite.
 *
 * A fixtures is a group of setup and teardown functions that are executed once per test, before and after the test function.
 *
 * @see clarity_suite_t
 */
struct clarity_fixture_s {
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
};

/**
 * @brief Runs the setup function for the given fixture.
 *
 * This function executes the setup function for the given fixture, passing in
 * the data provided when the fixture was created. If the setup function returns
 * an error, this function will return a non-zero value.
 *
 * @note This is an internal function and should not be called directly by user
 * code.
 *
 * @param fixture The fixture to run the setup function for.
 * @param status_code The actual return code got after running the function. It should be used only if true is returned.
 *
 * @return true if the setup function has run successfully, or false otherwise.
 *
 */
bool cl_fixture_run_setup(clarity_fixture_t *fixture, int *status_code);

/**
 * @brief Runs the teardown function for the given fixture.
 *
 * This function executes the teardown function for the given fixture, passing
 * in the data provided when the fixture was created. If the teardown function
 * returns an error, this function will return a non-zero value.
 *
 * @note This is an internal function and should not be called directly by user
 * code.
 *
 * @param fixture The fixture to run the teardown function for.
 * @param status_code The actual return code got after running the function. It should be used only if true is returned.
 *
 * @return true if the teardown function has run successfully, or false otherwise.
 */
bool cl_fixture_run_teardown(clarity_fixture_t *fixture, int *status_code);


#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_INTERNAL_SUITE_H
