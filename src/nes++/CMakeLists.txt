cmake_minimum_required(VERSION 3.22)

project(nes++ CXX ASM)
set(CXX_STANDARD 17)

add_library(nes++ INTERFACE)
target_include_directories(nes++ INTERFACE .)
target_sources(nes++ INTERFACE
        nes_interrupt.cpp
        nes_ppu.cpp
        nes_ppu.s
        types.cpp
)