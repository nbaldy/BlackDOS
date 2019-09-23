Lab 02 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

	In this lab, we created a "readString" function which can read a user-entered
	line from the console - it continues reading character until "Enter" is
	pressed, and supports backspace. We get the keyboard input using interrupt 22
	and print each character after it is pressed using interrupt 16. We then
	implemented this functionality into interrupt 33, where readString could be
	called by setting AX = 1 and BX to the address of the character array where
	input is stored. (CX and DX unused).

	We then created the "writeInt" function which could write an integer to the
	screen or printer by converting the int to a string using the intToStr
	function and then calling printStr. We again integrated this method into
	interrupt 33 with AX = 13, BX = the int to print, and CX = the destination (0
	= screen or 1 = printer).

	Finally, we created a "readInt" method which can read a user-entered integer
	from the console using readString and then converting this intput to an
	integer. We integrated this functionality into interrupt 33 where AX = 14, and
	BX is the address of the integer to be stored. With these interrupts complete,
	we use them in main to create a MadLibs game. The user needs only to run our
	program and follow the directions, then they should see a note created
	printer.out based on their input.

	The very first time our program is run, bootload must be compiled using "nasm
	bootload.asm". To run our program, use compileOS.sh to compile the operating
	system, and then run it using 'echo "c" | bochs -f bdos.txt'.
