# PlayStation 3 Toolchain
  export PS3DEV=/usr/local/ps3dev
	export PSL1GHT=$PS3DEV
# Toolchain PATH
	export PATH=$PATH:$PS3DEV/bin
	export PATH=$PATH:$PS3DEV/ppu/bin
	export PATH=$PATH:$PS3DEV/spu/bin
	export PKG_CONFIG_PATH=$PS3DEV/portlibs/ppu/lib/pkgconfig/
