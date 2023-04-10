cmake_minimum_required(VERSION 3.22)

project(CLarity VERSION 0.1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

set(CMAKE_C_STANDARD 23)

set(SOURCE_FILES src/test.c src/suite.c src/printer.c)

set(INCLUDE_FILES include/internal/suite.h include/CLarity/suite.h include/CLarity/test.h include/CLarity/clarity_types.h include/internal/test.h include/internal/printer.h)

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(PRIVATE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/internal)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "clarity")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} PRIVATE ${PRIVATE_INCLUDE_DIRS})

# Add testing targets
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

add_custom_target(copy_shared_library ALL
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:CLarity> ${CMAKE_BINARY_DIR}/test
		COMMENT "Copying the shared library to test directory"
		DEPENDS ${PROJECT_NAME})

get_directory_property(TEST_TARGETS DIRECTORY "${PROJECT_SOURCE_DIR}/test" DEFINITION TEST_TARGETS)

foreach (TEST_TARGET ${TEST_TARGETS})
	add_dependencies(${TEST_TARGET} copy_shared_library)
endforeach ()