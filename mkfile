ROOT=`pwd`
<$ROOT/src/mkhdr

DIRS=\
	src\

<$ROOT/src/mkdirs

nuke:V: clean
	rm -rf $BUILD

qemu:V: install
	qemu-system-i386 -kernel $BIN/kernel.bin

bear:V:
	mk nuke
	bear -- mk
