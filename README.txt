Lab 03 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

	In this lab, we created a "readSectors" which cna be used to read sectors from a floppy disk - it is provided an initial address, sector count to read and an initial absolute sector to start at. It converts the absolute sector given to a relative sector by using modulus and division on the absolute number. This allows calculations for a trackhead, head number, relative sector number. Using these values we obtain AX, CX, DX and call in interrupt 19, with BX being the address passed in.

	We then created the write sectors, which is the same process as ReadSectors, but we change a value for AH to 3 (it is 2 in readSectors).

	Finally we created the Clear screen function, which is given 2 integers representing a background and a foreground color. It starts by issuing 24 new line calls using interrupt 16. it then issues an interrupt command 16 to place the cursor in the upper left hand corner after the text has been cleared by the newlines. Then it calls an interrupt 16 to scan the window  and set the foreground and background to that which is specified.



The very first time our program is run, bootload must be compiled by executing
the command
   "nasm bootload.asm".
To run our program, use "compileOS.sh" to compile the operating system, then
execute the command to place msg into sector 30
   "dd if=msg of=floppya.img bs=512 count=1 seek=30 conv=notrunc"
And the following command to save the configuration file as a separate file
	 "dd if=floppy.img of=config bs=512 skip=258 count=1 conv=notrunc"
 and then run the operating system using
   "echo "c" | bochs -f bdos.txt"

