#ifndef CLARITY_INCLUDE_CLARITY_SUITE_H
#define CLARITY_INCLUDE_CLARITY_SUITE_H

#include <CLarity/clarity_types.h>
#include <stdbool.h>
#include <stdlib.h>

#include "test.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new test suite.
 *
 * @param name the name of the suite
 * @param setup_fn the setup function for the suite
 * @param setup_data the data to pass down to the setup function
 * @param teardown_fn the teardown function for the suite
 * @param teardown_data the data to pass down to the teardown function
 *
 * @return a pointer to the new suite, or NULL if the allocation failed
 *
 * @note The setup and teardown functions will be called once per suite
 *       before and after the suite.
 *
 * @note The returned suite must be freed with `cl_free_suite` when it is no longer needed.
 *
 * @see cl_free_suite
 */
clarity_suite_t *cl_create_suite(const char *name, clarity_setup_fn_t setup_fn, void *setup_data, clarity_teardown_fn_t teardown_fn, void *teardown_data);

/**
 * @brief Free a test suite and its associated resources.
 *
 * @param suite the test suite to free
 *
 * @note Any tests added to the suite will also be freed.
 *       This function should only be used to free suites
 *       created by cl_create_suite.
 *
 * @see cl_create_suite
 */
void cl_free_suite(clarity_suite_t *suite);

/**
 * @brief Adds a test to a suite.
 * @param suite Pointer to the test suite.
 * @param test Pointer to the test to add.
 *
 * @return CL_SUCCESS if the test was added successfully, or an error to explain what went wrong.
 *
 * Adds the specified test to the specified test suite.
 */
clarity_status_t cl_add_test(clarity_suite_t *suite, clarity_test_t *test);

/**
 * @brief Runs a test suite.
 * @param suite Pointer to the test suite to run.
 * @return true if all tests passed, false otherwise.
 *
 * Runs all tests in the specified test suite and returns true if all tests passed, false otherwise.
 */
bool cl_run_suite(clarity_suite_t *suite);

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_SUITE_H
