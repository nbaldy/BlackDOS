bcc -ansi -c -o fib.o fib.c
as86 blackdos.asm -o basm.o
ld86 -o fib -d fib.o basm.o
dd if=fib of=floppya.img bs=512 count=1 seek=30 conv=notrunc
