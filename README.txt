Lab 05 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

In this lab, we added functionality to our shell - ddir, exec, help, prnt, senv,
and show were implemented. Run our program using
  ./compileOS.sh
and then run our program using
  echo "c" | bochs -f bdos.txt
The shell opens once the operating system boots, and then the following commands
can be used.

Programs already loaded into memory are t3 (a tic tac toe game) and cal (a calender).


CMD	PARAMETERS	 DESCRIPTION
boot			       reboot the system
clrs			       clear the screen
echo			       display comment on screen followed by a new line
	- comment
copy			       [Not implemented, print args]
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
