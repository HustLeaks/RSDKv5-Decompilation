# How to Build for PlayStation 3

* have [ps3toolchain](https://github.com/ps3dev/PS3Toolchain) and [SDL2](https://github.com/StrawFox64/SDL2PSL1GHT) configured
* After installing SDL2 run ```export PKG_CONFIG_PATH=$PS3DEV/portlibs/ppu/lib/pkgconfig/```
* clone this repository ```git clone https://github.com/StrawFox64/RSDKv5-Decompilation.git --recursive```
* clone the Sonic Mania repository ```git clone https://github.com/StrawFox64/Sonic-Mania-Decompilation.git```
* Inside the Sonic-Mania-Decompilation repository folder copy the SonicMania folder to ```RSDKv5-Decompilation/RSDKv5```
* look for the makefile in RSDKv5.ps3 and run make.
* After finishing, we will have generated 3 files, being ```RSDKv5.elf```, ```RSDKv5.fake.self``` and ```RSDKv5.self```.
* We will use only the latter.

# Building an ISO

### Important Notice
Here you will learn how to assemble an image (disc) of sonic mania. Thus, not having the need to run it internally in multiman, but as a normal playstation 3 game. The processes can be a bit complex for beginners as it was for me. But I left all the boring parts ready in the ```BuildingISO``` folder. Make a calm reading and with enough attention, to finish the procedures and so you can assemble a functional image. Please do not skip steps. For they are all important. 

* All procedures are performed through windows, if you are using another operating system, research how to use the necessary tools in your operating system.

# You will need

* Need a legitimate copy of Sonic Mania.
* Need SCETool.
* Need [RSDKv5 Extract](https://github.com/MainMemory/RSDKv5Extract/releases).
* Need ISO Builder (```MakePS3ISO``` or ```GenPS3ISO``` (Choice of your preference)).

# Finishing

### Building Eboot.bin

* Download everything you need. put them all in the ```BuildingISO``` folder
* After the compilation of the project (Previously described) copy ```RSDKv5.self``` to ```BuildingISO``` folder
* Open the terminal in the BuildingISO folder and run ```scetool.exe --decrypt RSDKv5.self EBOOT.ELF``` and wait
* after decrypting run ```scetool.exe --template RSDKv5.self --sce-type=SELF --skip-sections=FALSE --compress-data=false --encrypt EBOOT.ELF EBOOT.BIN```
* When you finish encrypting. Copy ```EBOOT.BIN``` for ```SonicMania/PS3_GAME/USRDIR/```

### Data.rsdk file

* With your original copy of sonic mania copy the ```data.rsdk``` file for ```BuildingISO``` folder
* With RSDK Extract and ```data.rsdk```
* Then drag ```data.rsdk``` to RSDKv5Extract.exe
* After you finish extracting, enter the ```Data``` folder and copy the folder from inside to ```SonicMania/PS3_GAME/USRDIR/```

~~### Building ISO~~

~~* After the previous procedures performed go back to the ```BuildingISO``` folder, select the ```SonicMania``` folder and drag to the ISO Builder Chosen~~
~~* This will generate a file .iso that can be run on your console through webman or your preferred iso loader~~
~~* Just copy to your external media or internal hd~~

#### copy the ```SonicMania``` folder to your internal hdd to ```GAMES``` folder, or to your external media to the same folder
