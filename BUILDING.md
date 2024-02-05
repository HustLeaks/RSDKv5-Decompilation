# How to Build for PlayStation 3

* have [ps3toolchain](https://github.com/ps3dev/PS3Toolchain) and [SDL2](https://github.com/StrawFox64/SDL2PSL1GHT) configured
* After installing SDL2 run ```export PKG_CONFIG_PATH=$PS3DEV/portlibs/ppu/lib/pkgconfig/```
* clone this repository ```git clone --recursive https://github.com/StrawFox64/RSDKv5-Decompilation.git```
* clone the Sonic Mania repository ```git clone https://github.com/StrawFox64/Sonic-Mania-Decompilation.git```
* Inside the Sonic-Mania-Decompilation repository folder copy the SonicMania folder to ```RSDKv5-Decompilation/RSDKv5```
* look for the makefile in RSDKv5.ps3 and run make.
* After finishing, we will have generated 3 files, being ```RSDKv5.elf```, ```RSDKv5.fake.self``` and ```RSDKv5.self```.

# Building an ISO

### Important Notice
Here you will learn how to assemble an image (disc) of sonic mania. Thus, not having the need to run it internally in multiman, but as a normal playstation 3 game. The processes can be a bit complex for beginners as it was for me. But I left all the boring parts ready in the ```BuildingISO``` folder. Make a calm reading and with enough attention, to finish the procedures and so you can assemble a functional image. Please do not skip steps. For they are all important. 

* All procedures are performed through windows, if you are using another operating system, research how to use the necessary tools in your operating system.

# Pre-requisites

* Need a legitimate copy of Sonic Mania.
* Need SCETool.
* Need [RSDKv5 Extract](https://github.com/MainMemory/RSDKv5Extract/releases).
* Need GenPS3ISO.

## Step one

* Download all prerequisites and put in the folder ```BuildingISO```

### Step two (Building Eboot.bin)

* After the compilation (Previously described) copy ```RSDKv5.self``` to ```BuildingISO``` folder
* Open the terminal in the BuildingISO folder and run ```scetool.exe --decrypt RSDKv5.self EBOOT.ELF``` and wait
* after decrypting run ```scetool.exe --template RSDKv5.self --sce-type=SELF --skip-sections=FALSE --compress-data=false --encrypt EBOOT.ELF EBOOT.BIN```
* When you finish encrypting. Copy ```EBOOT.BIN``` for ```SonicMania/PS3_GAME/USRDIR/```

### Step three (Data.rsdk extraction)

* With your original copy of sonic mania copy the ```data.rsdk``` file for ```BuildingISO``` folder
* Then drag ```data.rsdk``` to RSDKv5Extract.exe and release
* After you finish extracting, enter the ```Data``` folder and copy the folder from inside to ```SonicMania/PS3_GAME/USRDIR/```

### Step Four (Building ISO) (Optional, Read **Notes)

* After the previous procedures performed go back to the ```BuildingISO``` folder, select the ```SonicMania``` folder and drag to the GenPS3ISO and release
* This will generate a file .iso that can be run on your console through webman or your preferred iso loader
* Just copy to your external media or internal hd

#### **Notes

There are two ways to run this game. The first run in folder format is the second run in iso format. I strongly recommend running it in folder format, because this way you have available the saves and updates of eboot.bin itself.

### Running in folder mode
#### copy the ```SonicMania``` folder found in ```BuildingISO```, to your internal hdd to ```GAMES``` folder, or to your external media to the same folder
