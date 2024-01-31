#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include $(PSL1GHT)/ppu_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	RSDKv5
BUILD		:=	build
SOURCES		:=	\
	../RSDKv5/ 						\
	../RSDKv5/RSDK/Core/  			\
	../RSDKv5/RSDK/Dev/        		\
	../RSDKv5/RSDK/Storage/			\
	../RSDKv5/RSDK/Graphics/ 		\
	../RSDKv5/RSDK/Audio/        	\
	../RSDKv5/RSDK/Input/        	\
	../RSDKv5/RSDK/Scene/      		\
	../RSDKv5/RSDK/Scene/Objects/ 	\
	../RSDKv5/RSDK/User/Core/  		\
	../dependencies/all/tinyxml2 	\
	../dependencies/all/iniparser 	\
	../dependencies/all/miniz   	\
	../dependencies/all/stb			\
	../RSDKv5/SonicMania/ 			\
	../RSDKv5/SonicMania/Objects
DATA		:=	data
INCLUDES	:=	\
	../RSDKv5/ 						\
	../dependencies/all/ 			\
	../dependencies/all/tinyxml2/ 	\
	../dependencies/all/iniparser/	\
	../dependencies/all/stb			\
	../RSDKv5/SonicMania/   		\
	../RSDKv5/SonicMania/Objects/

TITLE		:=	SonicMania
APPID		:=	CUSA07023
CONTENTID	:=	UP0001-$(APPID)_00-0000000000000000

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
# you may be asking why on did i put the -O2 optimization flags manually?
# this happens because the optimizations -O2 table does not work here, because of some unknown bug
# This bug occurs with flag -fcode-hoisting, for some reason if you use separator in it the execution does not work
# and if you remove the separator, the compiler does not let you compile because it does not have a separator
# but if you take out the separator and move it up the flag -freorder-blocks-algorithm=stc, it works mysteriously
# below and the complete table with a small change.

EXTRA_OFLAGS = -falign-functions  -falign-jumps \
-falign-labels  -falign-loops \
-fcaller-saves \
-fcrossjumping \
-fcse-follow-jumps  -fcse-skip-blocks \
-fdelete-null-pointer-checks \
-fdevirtualize  -fdevirtualize-speculatively \
-fexpensive-optimizations \
-fsplit-loops \
-fgcse  -fgcse-lm \
-fhoist-adjacent-loads \
-finline-functions \
-finline-small-functions \
-findirect-inlining \
-fipa-bit-cp  -fipa-cp  -fipa-icf \
-fipa-ra  -fipa-sra  -fipa-vrp \
-fisolate-erroneous-paths-dereference \
-flra-remat \
-foptimize-sibling-calls \
-foptimize-strlen \
-fpartial-inlining \
-fpeephole2 \
-fcode-hoisting
-freorder-blocks-algorithm=stc \
-freorder-blocks-and-partition  -freorder-functions \
-frerun-cse-after-loop \
-fschedule-insns -fschedule-insns2 \
-fsched-interblock  -fsched-spec \
-fstore-merging \
-fstrict-aliasing \
-fthread-jumps \
-ftree-builtin-call-dce \
-ftree-loop-vectorize \
-ftree-pre \
-ftree-slp-vectorize \
-ftree-switch-conversion  -ftree-tail-merge \
-ftree-vrp \
-fvect-cost-model=cheap

RSDK_flags	=	-D__PS3__ -DRETRO_STANDALONE=0 -DRSDK_AUTOBUILD -DRETRO_USE_MOD_LOADER=0 -DRETRO_DISABLE_LOG
CFLAGS		=	-g3 -O1 $(EXTRA_OFLAGS) -Wall -mcpu=cell $(MACHDEP) $(INCLUDE) $(RSDK_flags) -I$(PORTLIBS)/include
CXXFLAGS	=	$(CFLAGS)

LDFLAGS		=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	$(shell pkg-config --libs sdl2 theora) -lnet -lsysutil -lsysmodule

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
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(subst PublicFunctions.c,,${wildcard $(dir)/*.c})))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(subst xmltest.cpp,,${wildcard $(dir)/*.cpp})))
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
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).fake.self $(OUTPUT).self

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