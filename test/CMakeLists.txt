add_executable(${PROJECT_NAME}_test_one_suite_one_test_pass test_one_suite_one_test_pass.c)
target_link_libraries(${PROJECT_NAME}_test_one_suite_one_test_pass PRIVATE CLarity)
target_include_directories(${PROJECT_NAME}_test_one_suite_one_test_pass PRIVATE ${INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_test_one_suite_one_test_fail test_one_suite_one_test_fail.c)
target_link_libraries(${PROJECT_NAME}_test_one_suite_one_test_fail PRIVATE CLarity)
target_include_directories(${PROJECT_NAME}_test_one_suite_one_test_fail PRIVATE ${INCLUDE_DIRS})


add_executable(${PROJECT_NAME}_test_one_suite_one_test_skip test_one_suite_one_test_skip.c)
target_link_libraries(${PROJECT_NAME}_test_one_suite_one_test_skip PRIVATE CLarity)
target_include_directories(${PROJECT_NAME}_test_one_suite_one_test_skip PRIVATE ${INCLUDE_DIRS})

# Add all targets in a variable to expose them to the root folder.
get_property(TEST_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)