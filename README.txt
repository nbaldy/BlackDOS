Lab 05 - Operating Systems Nicole Baldy, Elena Falcione, Tim Inzitari

In this lab, we created a basic shell with three working functions: boot, clrs,
and echo. Boot is called with no arguments and reboots the operating system,
clrs also takes no arguments and clears the screen, and echo prints its argument
(comment) to the screen. We also created the 9 stub functions specified in the
lab, which print the command and the arguments provided. All commands issue
warnings if extra arguments are provided and show helpful tips if you do not
provide enough arguments

Our shell program is 11 segments so compileOS.sh and kernel.c have been modified
to accommodate this.

The very first time our program is run, bootload must be compiled by executing
the command
   "nasm bootload.asm"
To compile the operating system, use
	 "./compileOS.sh" (will need exe privileges)
Run the operating system using
   "echo "c" | bochs -f bdos.txt"
The shell should automatically pop up, and the user can begin entering any of
the 12 commands we implemented or created stub functions for in this lab.
[boot, clrs, echo, copy, ddir, exec, help, prnt, remv, senv, show, twet]
