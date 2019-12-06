Lab X - the shell

This program can be compiled using our makefile (make) and run
using the command ./shell

The makefile was created by the following tutorial:
http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
Adding the ulimit command was based on the following stackoverflow:
https://stackoverflow.com/questions/2271447/set-stack-size-in-a-makefile
Figuring out execvp and some of the Linux commands was based on the Linux manual:
https://linux.die.net/man/3/execvp

This shell can be used as an extension to the Linux shell in that all
Linux commands can be run in this shell, while the following commands
are simplified Linux commands which are also supported

Command   Args       Explanation

C         F1, F2      Copy File1 to File2 without deleting File1
D         File        Delete File1
E         Comment     Echo Comment onto screen
H                     Help - display this manual
G         cFile, Exe  GCC compile C file
L                     List contents of current directory
M         File        Make (or edit) a text file
P         File        Print contents of File
Q                     Quit Shell
W                     Wipe (Clear) screen
X         Program     Execute program


Note that, if calling an executable file, it must be called with
./Program, where Program is the executable name
