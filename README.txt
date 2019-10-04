Lab 04 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

	In this lab, we used the readSectors and writeSectors functions from lab 3 to
	create a runProgram function so that we can now run a program from the disk.
	We do this by reading the sectors containing the program to the buffer,
	deriving the base location of the segment to run it in main memory and
	transferring the program one byte at a time, and then we then call launchProgram
	to run the program. We found that this caused our program to execute
	in a loop - thus, we needed to create a terminate function which "hangs up"
	the program by using interrupt 33 with ax = 5 which stalls the program with an
	infinite loop.

	We have provided the test program fib (already loaded onto the disk) as well
	as a custom program we wrote for testing called madlibs.c. This program
	contains a message for our grader, and so we would appreciate it if they would
	indulge our extra effort. To make this program work, we edited blackdos.h to
	create a new library function, CLRSCRN, which calls interrupt 33 with ax=12 to
	clear the screen.

The very first time our program is run, bootload must be compiled by executing
the command
   "nasm bootload.asm"
To compile the operating system, use
	 "./compileOS.sh" (will need exe privileges)
To compile fib.c or madlibs.c and add the program to the disk at sector 30, use
	"./addFib.sh" or "./addMadlibs.sh", respectively (will need exe privileges)
To add a different executable to the program, use
 	"dd if=[my_exe] of=floppya.img bs=512 count=[number_of_sectors] seek=30 conv=notrunc"
and then run the operating system using
   "echo "c" | bochs -f bdos.txt"

