Lab 05 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

In this lab, we added functionality to our shell - ddir, exec, help, prnt, senv,
and show were implemented. In compileOS.sh, we compile kernel and shell, and add
the shell to floppya using loadFile. The shell opens once the operating system
boots, and then the following commands can be used


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
remv			       [Not implemented, print args]
	- filename
senv			       set environment variables
show			       display contents of filename in console
	- filename
twet			       [Not implemented, print args]
	- filename
