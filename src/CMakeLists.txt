cmake_minimum_required(VERSION 3.25)
add_subdirectory(nespp)
add_subdirectory(chess)

project(neschess CXX ASM)

neschess_policy()
add_executable(neschess)
target_compile_features(neschess PRIVATE cxx_std_23)
target_compile_options(neschess PRIVATE -Wall -Wextra -flto -g)
target_sources(neschess PRIVATE
        chrrom.s
        game_screen.cpp
        main.cpp
        neschess.cpp
        title_screen.cpp
)
target_link_libraries(neschess PRIVATE nespp chess -flto)
target_include_directories(neschess PRIVATE .)

set_target_properties(neschess PROPERTIES OUTPUT_NAME "../neschess.nes")
target_link_options(neschess PRIVATE "LINKER:-Map,neschess.map")
add_custom_command(TARGET neschess POST_BUILD COMMAND ${CMAKE_OBJDUMP} -dgS $<TARGET_FILE:neschess>.elf > $<TARGET_FILE:neschess>.lst)