function(create_test filename)
	# remove the extension from the name
	string(REPLACE ".c" "" filename_without_extension ${filename})

	# create the target and add the libraries and include directories.
	add_executable(${PROJECT_NAME}_${filename_without_extension} ${filename})
	target_link_libraries(${PROJECT_NAME}_${filename_without_extension} PRIVATE CLarity)
	target_include_directories(${PROJECT_NAME}_${filename_without_extension} PRIVATE ${INCLUDE_DIRS})
endfunction()


create_test(test_one_suite_one_test_pass.c)
create_test(test_one_suite_one_test_skip.c)
create_test(test_one_suite_one_test_fail.c)

create_test(test_one_suite_multiple_tests.c)
create_test(test_multiple_suites.c)

# Add all targets in a variable to expose them to the root folder.
get_property(TEST_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)