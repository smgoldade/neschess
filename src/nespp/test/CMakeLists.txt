cmake_minimum_required(VERSION 3.25)

add_executable(nespp_test)
target_compile_features(nespp_test PRIVATE cxx_std_23)
target_link_libraries(nespp_test PUBLIC nespp)
target_sources(nespp_test PUBLIC
        main.cpp
)

enable_testing()
add_test(NAME libnespp_test COMMAND nespp_test)
