
default:
	rm -rf forth.gb
	rgbasm -o forth.o forth.asm
	rgblink -o forth.gb --sym forth.sym forth.o
	rgbfix -v -p 0xFF forth.gb

dev:
	watchexec --clear clear make
