#ifndef CLARITY_INCLUDE_INTERNAL_PRINTER_H
#define CLARITY_INCLUDE_INTERNAL_PRINTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <stdbool.h>

/**
* @brief Represents the result of running a single test.
*/
typedef struct clarity_test_result_s {
	/**
	 * @brief The name of the test.
	 */
	const char *name;

	/**
	 * @brief The file name where the test was defined.
	 */
	const char *file_name;

	/**
	 * @brief The line number where the test was defined.
	 */
	int line_number;

	/**
	 * @brief Indicates if the test passed or failed.
	 *
	 * If `true`, the test passed. If `false`, the test failed.
	 *
	 * @note This field should not be modified by the user. It is automatically set by the testing framework
	 * based on the outcome of the test.
	 */
	bool passed;

	/**
     * @brief Indicates if the test was skipped.
     *
     * If `true`, the test was skipped. If `false`, the test was not skipped.
     */
	bool skipped;

	/**
	 * @brief If the test failed, this contains the error message.
	 *
	 * If the test passed, this should be `NULL`.
	 */
	const char *error_message;
} clarity_test_result_t;

/**
 * @brief Structure representing a report for a suite of Clarity tests.
 *
 * @details
 * This structure is used to store and output a report for a suite of Clarity tests. It contains
 * information about the suite's name, the total count of tests, the number of failed tests,
 * the number of skipped tests, and the number of succeeded tests.
 *
 * @note
 * This struct is intended for internal use and should not be exposed to end-users.
 */
typedef struct clarity_suite_report_s {
	const char *name;    /**< The name of the suite. */
	uint32_t   total_tests;     /**< The total number of tests in the suite. */
	uint32_t   failed_tests;    /**< The number of failed tests in the suite. */
	uint32_t   skipped_tests;   /**< The number of skipped tests in the suite. */
	uint32_t   succeeded_tests; /**< The number of succeeded tests in the suite. */
} clarity_suite_report_t;

/**
 * @brief Prints the result of a single test to standard output.
 *
 * @details
 * This function prints the result of a single test to standard output. If the test
 * passed, it will print "PASS". If the test failed, it will print "FAIL" along with
 * the error message.
 *
 * Example usage:
 * ```
 * clarity_test_result_t *result = cl_run_test(test);
 * cl_print_test_result(result);
 * ```
 *
 * @param result The test result to print.
 *
 * @return void
 */
void cl_print_test_result(clarity_test_result_t *result);

/**
 * @brief Prints the name of a test suite to stdout.
 *
 * @details
 * This function prints the name of a test suite to stdout in a standardized format.
 *
 * Example:
 * ```
 * cl_print_suite_name("My Test Suite");
 * ```
 *
 * @param name The name of the test suite to print.
 */
void cl_print_suite_name(const char *name);

/**
 * @brief Prints a report for a clarity test suite.
 *
 * @details
 * This function prints a report for a clarity test suite in the following format:
 *
 * ```
 * ------------------
 * Suite name
 * ------------------
 * Total: nnn, Failed: mmm, Skipped: ppp, Passed: qqq
 * ------------------
 * ```
 *
 * where:
 * - `nnn` is the total number of tests in the suite.
 * - `mmm` is the number of tests that failed in the suite.
 * - `ppp` is the number of tests that were skipped in the suite.
 * - `qqq` is the number of tests that passed in the suite.
 *
 * The report is enclosed in a box made up of dashes.
 *
 * @param report The report to print.
 *
 * @note This function is intended for internal use only.
 */
void cl_print_suite_report(clarity_suite_report_t *report);

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_INTERNAL_PRINTER_H
