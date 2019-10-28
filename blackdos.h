#define PRINTS(x)  interrupt(33,0,x,0,0)
#define PRINTN(x)  interrupt(33,13,x,0,0)
#define PRINTFILE(x, y, z) interrupt(33, 11, x, y, z)
#define LPRINTS(x) interrupt(33,0,x,1,0)
#define LPRINTN(x) interrupt(33,13,x,1,0)
#define SCANS(x)   interrupt(33,1,x,0,0)
#define SCANN(x)   interrupt(33,14,&x,0,0)
#define CLRSCRN(x,y) interrupt(33,12,x,y,0) /*(int bg, int fg)*/
#define READSCTR(x,y,z) interrupt(33, 2, x,y,z) /*(char *buffer, int sector, int sectorCount)*/
#define WRTESCTR(x,y,z) interrupt(33,6,x,y,z) /*(char *buffer, int sector, int sectorCount)*/
#define READFILE(x,y,z) interrupt(33,3,x,y,z) /*(char* fname, char* buffer, int* size)*/
#define REBOOT() interrupt(25,0,0,0,0)
#define RUNPROGRAM(x, y) interrupt(33, 4, x, y, 0) /*(char* name, int segment)*/
#define END interrupt(33,5,0,0,0)
