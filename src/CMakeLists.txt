cmake_minimum_required(VERSION 3.22)
add_subdirectory(nes++)

project(neschess CXX ASM)
set(CXX_STANDARD 17)

add_executable(neschess)
target_sources(neschess PRIVATE
        chrrom.s
        main.cpp
)
target_link_libraries(neschess PRIVATE nes++)

set_target_properties(neschess PROPERTIES OUTPUT_NAME "../neschess.nes")
add_link_options(-Wl,-Map,neschess.map)

