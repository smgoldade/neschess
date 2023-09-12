cmake_minimum_required(VERSION 3.22)
add_subdirectory(nes++)

project(nesrpg CXX ASM)
set(CXX_STANDARD 17)

add_executable(nesrpg)
target_sources(nesrpg PRIVATE
        chrrom.s
        main.cpp
)
target_link_libraries(nesrpg PRIVATE nes++)

set_target_properties(nesrpg PROPERTIES OUTPUT_NAME "../nesrpg.nes")
add_link_options(-Wl,-Map,nesrpg.map)

