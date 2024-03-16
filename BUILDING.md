# How to Build for PlayStation 3

# Pre-requisites

* Need [ps3toolchain](https://github.com/ps3dev/PS3Toolchain) and [SDL2](https://github.com/StrawFox64/SDL2PSL1GHT) configured
* Need a legitimate copy of Sonic Mania.
* Need [RSDKv5 Extract](https://github.com/Axanery/RSDKv5UExtract/releases).

# Steps
* clone this repository ```git clone --recursive https://github.com/StrawFox64/RSDKv5-Decompilation.git```
* clone the Sonic Mania repository ```git clone https://github.com/StrawFox64/Sonic-Mania-Decompilation.git```
* Inside the Sonic-Mania-Decompilation repository folder copy the SonicMania folder to ```RSDKv5-Decompilation/RSDKv5```
* extract the data.rsdk
* After you finish extracting, enter the ```Data``` folder and copy the folder from inside to ```pkgfiles/USRDIR```
* look for the makefile in RSDKv5.ps3 and run ```make pkg```.
* After finishing the build will be generated two pkg, install ```RSDKv5.pkg```