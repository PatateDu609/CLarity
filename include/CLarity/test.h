#ifndef CLARITY_INCLUDE_CLARITY_TEST_H
#define CLARITY_INCLUDE_CLARITY_TEST_H

#include <stdbool.h>
#include "suite.h"
#include "clarity_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new test case.
 *
 * @param name the name of the test case
 * @param fn the function to execute for the test case
 * @param data the data to associate with the test case
 *
 * @return a pointer to the new test case, or NULL if the allocation failed
 */
clarity_test_t *cl_create_test(const char *name, clarity_test_fn_t fn, void *data);

/**
 * @brief Get the name of a test case.
 *
 * @param test the test case to get the name from
 *
 * @return a pointer to the name of the test case
 */
const char *cl_get_test_name(clarity_test_t *test);

/**
 * @brief Get the data associated with a test case.
 *
 * @param test the test case to get the data from
 *
 * @return a pointer to the data associated with the test case
 */
void *cl_get_test_data(clarity_test_t *test);

/**
 * @brief Free a test case.
 *
 * @param test the test case to free
 */
void cl_free_test(clarity_test_t *test);

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_TEST_H
