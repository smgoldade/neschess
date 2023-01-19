cmake_minimum_required(VERSION 3.22)
include(toolchain/cc65-toolchain.cmake)

project(nesrpg C ASM)
set(C_STANDARD C99)

add_executable(nesrpg)
target_sources(nesrpg PRIVATE
        src/main.c

        src/nes/ines.s
        src/nes/6502_util.s
        src/nes/nes_interrupt.s
        src/nes/nes.s
        src/nes/startup.s
)

set_target_properties(nesrpg PROPERTIES
        OUTPUT_NAME "nesrpg.nes"
        COMPILE_FLAGS "-t nes -v -g -Oirs --asm-define NODEBUG -T "
        LINK_FLAGS "-t nes -C ${CMAKE_CURRENT_SOURCE_DIR}/toolchain/nes.cfg -Ln labels.txt -v -vm -m nesrpg.map"
)


