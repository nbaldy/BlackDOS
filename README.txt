Lab 07 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

In this lab, we finished our shell functionality by completing the implementation
of remv, copy, and twet. We did this by creating writeFile and deleteFile functions
which were tied to interrupt 33. The former finds a spot in the directory and map
for a new file (throwing an error if there is not space or if a file with the same
name already exists) and then writes the contents of a buffer into memory and modifies
the map and directory. The latter searches for the file in the directory (throwing
an error if it does not exist) and then removes its entry in map and the directory.

Run our program using
  ./compileOS.sh
and then run our program using
  echo "c" | bochs -f bdos.txt
The shell opens once the operating system boots, and then the following commands
can be used.

Programs already loaded into memory are fpc02 (a calendar program) and lab7 (a program which saves fpc02 as fall19, deleting fpc02).


CMD	PARAMETERS	 DESCRIPTION
boot			       reboot the system
clrs			       clear the screen
echo			       display comment on screen followed by a new line
	- comment
copy			       create file2 and copy all bytes of file1 to file1 without deleting file1
	- filename1
	- filename2
ddir			       list directory contents
exec			       execute filename
	- filename
help			       display this user manual
prnt			       print contents of filename to printer
	- filename
remv			       delete the file called filename
	- filename
senv			       set environment variables
show			       display contents of filename in console
	- filename
twet			       create a text file called filename
	- filename
