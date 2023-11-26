cmake_minimum_required(VERSION 3.25)

add_executable(chess_test)
target_compile_features(chess_test PRIVATE cxx_std_23)
target_link_libraries(chess_test PUBLIC chess)
target_sources(chess_test PUBLIC
        main.cpp
)

enable_testing()
add_test(NAME libchess_test COMMAND chess_test)