Lab 03 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

	In this lab, we wrote a readSectors function which reads a sector from the
	floppy disk - it is provided an initial address, the number of sectors to read
	and an initial absolute sector to start at. It converts the absolute sector
	given to a relative sector by using modulus and division on the absolute
	number. This allows calculations for a trackhead, head number, relative sector
	number. These values are used to calculate AX, CX, and DX for our call to
	interrupt 19, with BX being the address passed into our ReadSectors function.

	We then created the writeSectors function, which uses a similar process as
	ReadSectors, calling interrupt 19 with AX = 768 + sectorCount, with the rest
	of the parameters remaining the same as readSectors. This allows us to write
	the contents of buffer to the disk.

	Finally we created the clearScreen function, which has two integer parameters
	which indicate the background and foreground color. Then, it uses interrupt 16
	to clear the screen by printing 24 newlines, place the cursor in the left-hand
	corner, and change the background and foreground if applicable.

	When we call inturrupt 33, we call readSectors, writeSectors, and clearScreen
	if AX is 2, 6, or 12, respectively. In main, we specify a background and
	foreground color, save this as a configuration file, clear the screen, print
	the logo, and then print the contents of Sector 30, which should be msg



The very first time our program is run, bootload must be compiled by executing
the command
   "nasm bootload.asm".
Before running our program, use "compileOS.sh" to compile the operating system
and then run the operating system using
   "echo "c" | bochs -f bdos.txt"

