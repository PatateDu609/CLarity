#ifndef CLARITY_INCLUDE_INTERNAL_TEST_H
#define CLARITY_INCLUDE_INTERNAL_TEST_H

#include <CLarity/clarity_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure representing a test.
 *
 * The `clarity_test_t` structure represents a test in the Clarity testing framework.
 * A test is defined by its name, function pointer to the test function, and a pointer to
 * user data associated with the test.
 *
 * @remark All fields in this structure should be considered read-only and should not be modified
 *         by the user.
 */
struct clarity_test_s {
	/**
	 * @brief The name of the test.
	 *
	 * This field represents the name of the test, as specified by the user when creating the test.
	 * The name should be unique within a test suite.
	 *
	 * @note This field should be considered read-only and should not be modified by the user.
	 */
	const char *name;

	/**
	 * @brief The function pointer to the test function.
	 *
	 * This field represents a function pointer to the test function.
	 * The function should have the signature `clarity_test_fn_t`.
	 *
	 * @note This field should be considered read-only and should not be modified by the user.
	 */
	clarity_test_fn_t test_fn;

	/**
	 * @brief User data associated with the test.
	 *
	 * This field represents a pointer to user data associated with the test, as specified by the user
	 * when creating the test. This pointer can be used to pass arbitrary data to the test function.
	 *
	 * @note This field should be considered read-only and should not be modified by the user.
	 */
	void *user_data;
};


#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_INTERNAL_TEST_H
