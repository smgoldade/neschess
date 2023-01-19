# nesrpg
An RPG. Made for the NES!  
At least that's the goal.

## Recognition
This project derives pretty much all necessary information needed for programming the NES from
the NES Wiki over at from [nesdev](https://www.nesdev.org/).  
Additional inspiration and ideas taken from [nesdoug](https://nesdoug.com).

## Build
Compiled with [cc65](https://cc65.github.io/).  
Build is via [CMake](https://cmake.org/), I recommend the [Ninja](https://ninja-build.org/) build generator.  

### Developer Setup
The IDE I've personally used is [CLion](https://www.jetbrains.com/clion/).  
The setup process is to use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) w/Ubuntu.  
Create a toolchain in CLion from WSL, with cc65 as the C compiler.  
I've included the .idea directory to help with CLion setup with a custom compiler setup and shared CMake profile that should then correctly build for you.

### Direct Build

    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain/cc65-toolchain.cmake -S . -B ./bin
    cmake --build --target nesrpg -j 9

### Output
The output file is nesrpg.nes in the /bin directory.  
This can be run in an emulator like [mesen](https://www.mesen.ca/).  