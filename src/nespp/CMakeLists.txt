cmake_minimum_required(VERSION 3.25)

project(nespp CXX ASM)

add_library(nespp STATIC)
target_compile_features(nespp PUBLIC cxx_std_23)
target_compile_options(nespp PUBLIC -Wall -Wextra -flto)
target_include_directories(nespp PRIVATE src PUBLIC include)

add_subdirectory(src)
add_subdirectory(test)