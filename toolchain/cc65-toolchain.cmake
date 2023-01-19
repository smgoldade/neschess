# A toolchain file to use cc65 to crosscompile for the 6502
# Based on the one available at https://github.com/jviskari/cc65_cmake

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER cl65 CACHE PATH "C Compiler")
set(CMAKE_C_COMPILER_ID cc65)
set(CMAKE_C_VERBOSE_FLAG "-v")
set(CMAKE_C_FLAGS_INIT " ")
set(CMAKE_DEPFILE_FLAGS_C "--create-dep <DEPFILE>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ASM_COMPILER cl65 CACHE PATH "ASM Compiler")
set(CMAKE_ASM_COMPILER_ID ca65)

find_program( CMAKE_AR ar65 )

set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_COMMAND> -E remove <TARGET> " "<CMAKE_AR> a <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_ASM_CREATE_STATIC_LIBRARY ${CMAKE_C_CREATE_STATIC_LIBRARY} )
