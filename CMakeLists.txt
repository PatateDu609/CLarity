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
#
## Set test directory
#set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
#
## Add test executable
#add_executable(${PROJECT_NAME}_test ${TEST_DIR}/main.c)
#set_target_properties(${PROJECT_NAME}_test PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_test")
#
#target_include_directories(${PROJECT_NAME}_test PRIVATE ${INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME} ${LIB_DL})
