ROOT=`pwd`
<$ROOT/src/mkhdr

DIRS=\
	src\

<$ROOT/src/mkdirs

qemu:V: install
	qemu-system-i386 -kernel $BIN/kernel.bin
