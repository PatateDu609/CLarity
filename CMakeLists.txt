cmake_minimum_required(VERSION 3.22)

project(CLarity VERSION 0.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_FILES src/loader/loader.c src/test.c src/suite.c src/printer.c)
if (WIN32)
	set(SOURCE_FILES ${SOURCE_FILES} src/loader/clarity_loader_windows.c)
endif ()

set(INCLUDE_FILES include/internal/loader.h include/internal/suite.h include/CLarity/suite.h include/CLarity/test.h include/CLarity/clarity_types.h include/internal/test.h include/internal/printer.h)

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(PRIVATE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/internal)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "clarity")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} PRIVATE ${PRIVATE_INCLUDE_DIRS})

## Find dl library for Unix-like systems
#if (UNIX AND NOT APPLE)
#	find_library(LIBDL dl)
#	if (NOT LIBDL)
#		message(FATAL_ERROR "Couldn't find LIBDL")
#	endif ()
#endif ()

# Add testing targets
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

if (WIN32)
	add_custom_target(copy_dll ALL
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:CLarity> ${CMAKE_BINARY_DIR}/test
			COMMENT "Copying DLL to test directory"
			DEPENDS ${PROJECT_NAME})
endif ()

get_directory_property(TEST_TARGETS DIRECTORY "${PROJECT_SOURCE_DIR}/test" DEFINITION TEST_TARGETS)
message(NOTICE "Targets from root ${TEST_TARGETS}")

add_dependencies(${TEST_TARGETS} copy_dll)