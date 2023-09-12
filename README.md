# nesrpg
An RPG. Made for the NES!  
At least that's the goal.

## Recognition
This project derives pretty much all necessary information needed for programming the NES from
the NES Wiki over at [nesdev](https://www.nesdev.org/).  
Additional inspiration and ideas taken from [nesdoug](https://nesdoug.com).

## Build
Compiled with [llvm-mos](https://github.com/llvm-mos/llvm-mos).  
Build is via [CMake](https://cmake.org/).

### Developer Setup
The IDE I've personally used is [CLion](https://www.jetbrains.com/clion/).  
The setup process is to use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) w/Ubuntu.  
Install the [llvm-mos-sdk](https://github.com/llvm-mos/llvm-mos-sdk), and set it up so that it can be found with CMake's find_package.
I've included the .idea directory to help with CLion setup with a custom compiler setup and shared CMake profile that should then correctly build for you.

### Direct Build
    cmake -S. -B ./bin
    cmake --build ./bin --target nesrpg -j 9

### Output
The output file is nesrpg.nes in the /bin directory.  
This can be run in an emulator like [mesen](https://www.mesen.ca/).  