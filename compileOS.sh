dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kasm.o
bcc -ansi -c -o Shell.o Shell.c
as86 blackdos.asm -o basm.o
ld86 -o Shell -d Shell.o basm.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259
bcc -ansi -c -o ddir.o ddir.c
ld86 -o ddir -d ddir.o basm.o
./loadFile Shell
./loadFile ddir
bcc -ansi -c -o cal.o cal.c
ld86 -o cal -d cal.o basm.o
./loadFile cal
bcc -ansi -c -o t3.o t3.c
ld86 -o t3 -d t3.o basm.o
./loadFile t3
./loadFile Stenv
