cmake_minimum_required(VERSION 3.24)

project(chess CXX ASM)

add_library(chess STATIC)
target_compile_features(chess PUBLIC cxx_std_23)
target_compile_options(chess PUBLIC -Wall -Wextra -flto -save-temps $<$<COMPILE_LANGUAGE:CXX>:-fconstexpr-depth=100000 -fconstexpr-steps=99999999>)
target_link_libraries(chess PUBLIC nespp -flto)
target_include_directories(chess PUBLIC include)

add_subdirectory(test)
