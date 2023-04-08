cmake_minimum_required(VERSION 3.22)
project(CLarity C)

set(CMAKE_C_STANDARD 23)

add_library(CLarity src/clarity.c)
target_include_directories(CLarity PUBLIC include/CLarity)