#ifndef CLARITY_INCLUDE_CLARITY_CLARITY_H
#define CLARITY_INCLUDE_CLARITY_CLARITY_H

#include <stdint.h>
#include "clarity_types.h"
#include "suite.h"
#include "test.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Runs all tests discovered by CLarity.
 *
 * @details
 * This function runs all tests discovered by CLarity. It uses the internal test runner to
 * execute each test and reports the results to the console. If any test fails, it will call
 * the `exit()` function with a non-zero status code to signal that the tests have failed.
 *
 * This function should be called once and only once in a program, typically from the `main()`
 * function, to run all the tests defined in the program.
 *
 * @warning This function is marked as `noreturn`. It will not return and will terminate the
 * program with `exit()` function when all tests have been executed. The exit status code will
 * be zero if all tests passed, or non-zero if any test failed.
 *
 * @note This function will automatically discover and load all tests defined in shared
 * libraries and object files that have been registered with CLarity. See `cl_load_tests()`
 * function for more details on how to register tests.
 *
 * @see cl_load_tests()
 *
 * @param ac The number of arguments passed to the program from the command line.
 * @param av An array of strings containing the command line arguments.
 */
void cl_run_tests(int ac, char **av) __attribute__((noreturn));

/**
 * @brief Load tests from a dynamic library or object file.
 *
 * @details
 * This function loads all tests defined in a dynamic library or object file at the specified
 * path. The file is opened using the platform-specific dynamic library loading function,
 * which is either `LoadLibrary()` on Windows or `dlopen()` on Unix-based systems.
 *
 * The library file must contain a function named `clarity_register_tests()` that takes no
 * arguments and returns a pointer to a `cl_test_list_t` structure. This function is called
 * by CLarity after the library is loaded to register all the tests defined in the library.
 *
 * If the library file is already loaded, this function returns immediately without doing
 * anything.
 *
 * @warning
 * This function should only be called from the main thread before any tests are executed.
 * Calling this function from multiple threads simultaneously may lead to undefined behavior.
 *
 * @param path The path to the dynamic library or object file to load.
 *
 * @return
 * - `CL_SUCCESS` if the library was loaded successfully.
 * - `CL_ERROR_INVALID_ARGUMENT` if `path` is `NULL` or an empty string.
 * - `CL_ERROR_FILE_NOT_FOUND` if the file at `path` could not be found or opened.
 * - `CL_ERROR_LOAD_LIBRARY` if the library file could not be loaded.
 * - `CL_ERROR_INVALID_FORMAT` if the library file has an invalid format or does not contain
 *   the required `clarity_register_tests()` function.
 */
clarity_status_t cl_load_tests(const char* library_path);

/**
 * @brief Unload tests from a dynamic library or object file.
 *
 * @details
 * This function unloads all tests defined in a dynamic library or object file at the specified
 * path. The file is closed using the platform-specific dynamic library unloading function,
 * which is either `FreeLibrary()` on Windows or `dlclose()` on Unix-based systems.
 *
 * If the library file was not previously loaded or has already been unloaded, this function
 * returns immediately without doing anything.
 *
 * @warning
 * This function should only be called from the main thread after all tests have been executed
 * and all the registered tests have been executed. Calling this function from multiple threads
 * simultaneously may lead to undefined behavior.
 *
 * @return
 * - `CL_SUCCESS` if the library was unloaded successfully.
 * - `CL_ERROR_LIBRARY_NOT_LOADED` if the library file was not previously loaded.
 * - `CL_ERROR_UNLOAD_LIBRARY` if the library file could not be unloaded.
 */
clarity_status_t cl_unload_tests();

#ifdef __cplusplus
}
#endif

#endif //CLARITY_INCLUDE_CLARITY_CLARITY_H
