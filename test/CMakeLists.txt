add_executable(${PROJECT_NAME}_test_one_suite_one_test test_one_suite_one_test.c)
target_link_libraries(${PROJECT_NAME}_test_one_suite_one_test PRIVATE CLarity)
target_include_directories(${PROJECT_NAME}_test_one_suite_one_test PRIVATE ${INCLUDE_DIRS})


# Add all targets in a variable to expose them to the root folder.
get_property(TARGETS_IN_DIR DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
set(TEST_TARGETS ${TEST_TARGETS} ${TARGETS_IN_DIR} CACHE INTERNAL "")