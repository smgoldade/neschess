cmake_minimum_required(VERSION 3.22)

set(LLVM_MOS_PLATFORM nes-nrom)
find_package(llvm-mos-sdk REQUIRED)

project(neschess)
add_subdirectory(src)