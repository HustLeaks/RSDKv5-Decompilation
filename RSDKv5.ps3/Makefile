#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include $(PSL1GHT)/ppu_rules

PKG_CONFIG_PATH=/usr/local/ps3dev/portlibs/ppu/lib/pkgconfig/

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	\
	../RSDKv5/ 							\
	../RSDKv5/RSDK/Core/  			\
	../RSDKv5/RSDK/Dev/        			\
	../RSDKv5/RSDK/Storage/ \
	../RSDKv5/RSDK/Graphics/ \
	../RSDKv5/RSDK/Audio/        			\
	../RSDKv5/RSDK/Input/        			\
	../RSDKv5/RSDK/Scene/        			\
	../RSDKv5/RSDK/Scene/Objects/ \
	../RSDKv5/RSDK/User/Core/  \
	../dependencies/all/tinyxml2 		\
	../dependencies/all/iniparser 	\
	../dependencies/all/miniz   \
	../../../SonicManiaPS3/ \
	../../../SonicMania/Objects
DATA		:=	data
INCLUDES	:=	\
	../RSDKv5/ 					\
	../dependencies/all/ 			\
	../dependencies/all/tinyxml2/ 	\
	../dependencies/all/iniparser/ \
	../dependencies/all/iniparser/ \
	../../../SonicMania/   		\
	../../../SonicMania/Objects/

TITLE		:=	RSDKv5
APPID		:=	SONCMANIA
CONTENTID	:=	UP0001-$(APPID)_00-0000000000000000
#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

# you may be asking why on earth did i put the -O2 optimization flags
# manually. it turns out this port wouldn't work on real hardware so i
# started checking what was the one that was causing this.
# it's -fschedule-insns2, so it's been removed from here.

EXTRA_OFLAGS = -fthread-jumps \
-falign-functions  -falign-jumps \
-falign-loops  -falign-labels \
-fcaller-saves \
-fcrossjumping \
-fcse-follow-jumps  -fcse-skip-blocks \
-fdelete-null-pointer-checks \
-fdevirtualize -fdevirtualize-speculatively \
-fexpensive-optimizations \
-fgcse  -fgcse-lm  \
-fhoist-adjacent-loads \
-finline-small-functions \
-findirect-inlining \
-fipa-cp \
-fipa-bit-cp \
-fipa-vrp \
-fipa-sra \
-fipa-icf \
-fisolate-erroneous-paths-dereference \
-flra-remat \
-foptimize-sibling-calls \
-foptimize-strlen \
-fpartial-inlining \
-fpeephole2 \
-fstore-merging \
-fstrict-aliasing -fstrict-overflow \
-ftree-builtin-call-dce \
-ftree-switch-conversion -ftree-tail-merge \
-fcode-hoisting 
-freorder-blocks-algorithm=stc \
-freorder-blocks-and-partition -freorder-functions \
-frerun-cse-after-loop \
-fsched-interblock  -fsched-spec \
-fschedule-insns  

CFLAGS		=	-O1 $(EXTRA_OFLAGS) -Wall -mcpu=cell $(MACHDEP) $(INCLUDE) -D__PS3__ -DRSDK_AUTOBUILD -I/usr/local/ps3dev/portlibs/ppu/include -I/usr/local/ps3dev/portlibs/ppu/include/SDL2
CXXFLAGS	=	$(CFLAGS)

LDFLAGS		=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
# $(shell /usr/local/ps3dev/portlibs/ppu/bin/sdl2-config --libs)
#LIBS	:=	 -L/usr/local/ps3dev/portlibs/ppu/lib -lSDL2_mixer -lSDL2 -lrsx -lgcm_sys -lio -lsysutil -laudio -lrt -llv2 -ldbglogger -lnet -lsysmodule -lFLAC -logg -lvorbis -lvorbisfile -lmikmod -lmad -ltheora -lm
LIBS	:=	$(shell /usr/local/ps3dev/portlibs/ppu/bin/sdl2-config --libs) $(shell pkg-config --libs theora) -ldbglogger -lnet -lsysutil -lsysmodule

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

export BUILDDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(LIBPSL1GHT_INC) \
					-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					$(LIBPSL1GHT_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).self

#---------------------------------------------------------------------------------
run:
	ps3load $(OUTPUT).self


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).self: $(OUTPUT).elf
$(OUTPUT).elf:	$(OFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
