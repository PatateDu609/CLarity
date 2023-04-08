cmake_minimum_required(VERSION 3.22)

project(CLarity VERSION 0.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_FILES src/clarity.c)
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "clarity")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

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
