
default:
	rgbasm -o forth.o forth.asm
	rgblink -o forth.gb forth.o
	rgbfix -v -p 0xFF forth.gb

dev:
	watchexec --clear clear make
