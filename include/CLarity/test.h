#ifndef CLARITY_INCLUDE_CLARITY_TEST_H
#define CLARITY_INCLUDE_CLARITY_TEST_H

#include <stdbool.h>
#include <stdint.h>
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

/**
 * @brief Internal function to mark a point in the test.
 *
 * This function should not be called directly by the user. It is used internally
 * by the `cl_fail_test` and `cl_skip_test` macros to add information about the
 * test function and the line number where the macro was called.
 *
 * @param test The test object to mark.
 * @param file The file where the macro was called.
 * @param line The line number in the file where the macro was called.
 *
 * @warning This function must not be used directly.
 */
void __cl_test_mark_point(clarity_test_t *test, const char *file, size_t line);

/**
 * @brief Marks the given test as failed and records the failure message.
 *
 * This function is used internally by the `cl_fail_test` macro to mark a test as failed.
 * It should not be called directly by user code.
 *
 * @param test A pointer to the `clarity_test_t` struct representing the failed test.
 * @param message A string representing the failure message.
 *
 * @warning This function must not be used directly.
 */
void __cl_fail_test(clarity_test_t *test, const char *message);

/**
 * @brief Marks the given test as skipped and records the skip message.
 *
 * This function is used internally by the `cl_skip_test` macro to mark a test as skipped.
 * It should not be called directly by user code.
 *
 * @param test A pointer to the `clarity_test_t` struct representing the skipped test.
 * @param message A string representing the skip message.
 *
 * @warning This function must not be used directly.
 */
void __cl_skip_test(clarity_test_t *test, const char *message);

/**
 * @brief Macro to mark the current test as failed and exit it.
 *
 * This macro should be used in the test function to indicate that the test has failed.
 * It will call the internal function `__cl_test_mark_point` to add information about the
 * test function and the line number where this macro was called.
 *
 * @param test The test object to mark as failed.
 * @param message The message to display for the failure.
 */
#define cl_fail_test(test, message)                         \
    {                                                       \
        __cl_test_mark_point(test, __FILE__, __LINE__);     \
        __cl_fail_test(test, message);                      \
    }


/**
 * @brief Macro to mark the current test as skipped and exit it.
 *
 * This macro should be used in the test function to indicate that the test has been skipped.
 * It will call the internal function `__cl_test_mark_point` to add information about the
 * test function and the line number where this macro was called.
 *
 * @param test The test object to mark as skipped.
 * @param message The message to display for the skipped test.
 */
#define cl_skip_test(test, message)                         \
    {                                                       \
        __cl_test_mark_point(test, __FILE__, __LINE__);     \
        __cl_skip_test(test, message);                      \
    }


#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_TEST_H
