bcc -ansi -c -o madlibs.o madlibs.c
as86 blackdos.asm -o basm.o
ld86 -o madlibs -d madlibs.o basm.o
dd if=madlibs of=floppya.img bs=512 count=4 seek=30 conv=notrunc
