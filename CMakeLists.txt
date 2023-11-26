cmake_minimum_required(VERSION 3.25)

if(NOT CMAKE_CROSSCOMPILING)
    message(FATAL_ERROR "Build is for 6502, cross compilation required.")
endif()

set(LLVM_MOS_PLATFORM nes-nrom)
find_package(llvm-mos-sdk REQUIRED)

include(cmake/Policy.cmake)
project(neschess)

# LLVM-MOS-SDK doesnt appear to remove unneeded options that dont do anything and thus
# cause warnings when using the compiler for assembly
set(CMAKE_ASM_FLAGS_MINSIZEREL -Oz CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS_DEBUG CACHE STRING "" FORCE)

add_subdirectory(src)