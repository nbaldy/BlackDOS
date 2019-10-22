/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_______ Nicole Baldy, Elaine Falcione, Tim Inzitari_______ Date:______9/19/19_______        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.04, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void runProgram(int start, int size, int segment);
void printLogo();

void main()
{
   char buffer[512];
   int size;
   makeInterrupt21();

   /* Read sector 258 - config file - into memory */
   interrupt(33,2,buffer,258,1);
   /* Clear screen */
   interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
   printLogo();

   /* Load msg file */
   interrupt(33,3,"msg\0",buffer,&size);
   /* Print msg file */
   interrupt(33,0,buffer,0,0);

   while (1) ;
}

void printLogo()
{
  interrupt(33,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
  interrupt(33,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
  interrupt(33,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
  interrupt(33,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
  interrupt(33,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
  interrupt(33,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
  interrupt(33,0," BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0);
  interrupt(33,0," Author(s):Nicole Baldy, Elena Falcione, Tim Inzitari.\r\n\r\n\0",0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */



/* Prints a string to either the console (if d=0) or printer (d=1) */
void printString(char* c, int d)
{
	int out;
	int secondParam;
	char r;
	int i;

  out = 16;
	secondParam = 14 * 256;
	if (d == 1){
		out = 23;
		secondParam = 0;
	}

  /*print until null terminator is pressed*/
	i = 0;
	r = c[0];
	while (r != '\0')
	{
	   interrupt(out, secondParam + r, 0,0,0);
	   r= c[++i];
	 }
}

/* Gets a line of input from the user, updating stringarray */
void readString(char* stringarray)
{
  int count;
  int i;
  char* c;

  /*initial keystroke*/
  c = interrupt(22,0,0,0,0);
  count = 0;

  while (c != 13)
  { /*until enter is pressed - print keystroke unless backspace*/
      if (c == 8)
      {
        /*backspace - decrement count if not empty*/
        if (count > 0)
        {
          interrupt(16,14 * 256 + c,0,0,0);
          count--;
        }
      }
      else
      {
        /*store keystroke in array*/
        interrupt(16,14 * 256 + c,0,0,0);
        stringarray[count] = c;
        count++;
      }
      /*get next keystroke*/
      c = interrupt(22,0,0,0,0);
  }

  /*mark end of input with null character and print the newline*/
  stringarray[count] = '\0';
  interrupt(16,14 * 256 + '\r',0,0,0);
  interrupt(16,14 * 256 + '\n',0,0,0);

}


/*  Reads an integer from the console */
void readInt(int* num)
{
  char b[6];
  int i;

  /*Read in string*/
  readString(b);
  *num=0;
  i=0;
  /* convert from char array to int */
  while((b[i] != '\0') && (i < 6))
  {
    *num = *num * 10;
    *num = *num + (b[i++] - '0');
  }
}


int mod(int a, int b) {
  int x = a;
  while (x >= b)
    x = x - b;
  return x;
}

int div(int a, int b) {
 int q = 0;
 while (q * b <= a) q++;
 return (q - 1);
}

/* convert an integer to a sequence of printable characters*/
void intToStr (int num, char* str) {
    int i;
    char tmp[6];
    int digits;
    int x;
    x = 0;
    digits = 0;
    i=0;

    /*special case - number is 0*/
    if(num == 0)
    {
      str[0] = '0';
      str[1] = '\0';
      return;
    }

    /* do the conversion with a temporary string*/
    while (num != 0) {
      x = mod(num,10);
      tmp[i++] =  (x + '0');
      num = div(num,10);
      ++digits;
    }

    /*reverse the digits*/
    i = 0;
    str[digits] = '\0';
    while (digits > 0)
    {
        str[--digits] = tmp[i++];
    }
}

/* use intToStr and printString to write an integer to the console or printer*/
void writeInt(int num, int out)
{
  char* str[6];
  intToStr(num,str);
  interrupt(33,0, str, out,0);
}

/* Takes absolute sector, calculates and reads relative sector into buffer */
readSectors(char *buffer, int sector, int sectorCount)
{
  int trackNo;
  int relSecNo;
  int headNo;
  int ax;
  int cx;
  int dx;


  trackNo =0;
  relSecNo = 0;
  headNo = 0;
  ax = 0;
  cx = 0;
  dx = 0;

  /* compute relative sector */
  relSecNo = mod(sector,18) + 1;
  headNo = div(sector,18);
  headNo = mod(headNo,2);
  trackNo = div(sector,36);

  /* instructs inturrupt to read from sector */
  ax = 512 + sectorCount;
  cx = trackNo * 256 + relSecNo;
  dx = headNo * 256;

  /* read sector into buffer */
  interrupt(19,ax,buffer,cx,dx);

}

writeSectors(char *buffer, int sector, int sectorCount)
{
  int trackNo;
  int relSecNo;
  int headNo;
  int ax;
  int cx;
  int dx;


  trackNo =0;
  relSecNo = 0;
  headNo = 0;
  ax = 0;
  cx = 0;
  dx = 0;

  /* compute relative sector */
  relSecNo = mod(sector,18) + 1;
  headNo = div(sector,18);
  headNo = mod(headNo,2);
  trackNo = div(sector,36);

  /* instructs inturrupt to write to sector */
  ax = 768 + sectorCount;
  cx = trackNo * 256 + relSecNo;
  dx = headNo * 256;

  /* write sector from buffer */
  interrupt(19,ax,buffer,cx,dx);

}

/* bx = background color, cx = character color, and clear screen */
void clearScreen(int bx, int cx)
{
  int i = 0;

  /* clear screen */
  for (i; i < 24; ++i)
  {
    interrupt(16,14*256 + '\r',0,0,0);
    interrupt(16,14*256 + '\n',0,0,0);
  }

  /* reposition cursor in left corner */
  interrupt(16,512,0,0,0);

  /* set screen and character color */
  if (bx > 0 && bx < 9 && cx > 0 && cx < 17)
   interrupt(16,1536,4096 * (bx-1) + 256 * (cx-1),0,6223);

}

/* Reads a program from start sector, runs in given segment */
void runProgram(int start, int size, int segment)
{
  /*max size - 26 sectors*/
  char buffer[0x34000];
  int baseSegment;
  int offset;

   if (size > 26)
   {
     interrupt(33, 0, "Error: size invalid. Can be no bigger than 26 sectors \0", 0,0);
     return;
   }

  /* call readSectors to load file into local buffer */
  interrupt(33, 2, buffer, start, size);

  /* get base location of segment or error if invalid */
  if (segment < 2 || segment > 9) {
    interrupt(33, 0, "Error: segment invalid. Must be 2-9 inclusive \0", 0,0);
    return;
  }
  baseSegment = 4096 * segment;

  /* transfer loaded file from buffer into memory at computed segment */
  for (offset=0; offset < 0x3400; offset++)
  {
    putInMemory(baseSegment, offset, buffer[offset]);
  }

  /* Launch program */
  launchProgram(baseSegment);

  interrupt(33,5,0,0);

}

void stop()
{
  while(1);
}

void readFile(char* fname, char* buffer, int* size)
{
  char directory[512];
  int i,j, found;
  /* Load disk directory into memory */
  interrupt(33, 2, directory, 257, 1);

  /*Loop through 32 possible files */
  for (i=0; i<32 && directory[16*i] != '\0'; i++)
  {
    found = 1; /*use as flag - clear when chars don'tmatch*/
    for (j=0; j<8 && fname[j]!='\0' ; j++)
    {
      if(fname[j] != directory[16*i + j])
      {
        found = 0;
        break;
      }
    }

    if(found)
      break;
  }

  if (found)
  {
    int startPos;
    startPos = directory[16*i + 8];
    *size = directory[16*i +9];

    /* read file into buffer */
    interrupt(33, 2, buffer, startPos, *size);
    return;
  }

  /* Not found - throw file not founderror */
  interrupt(33,15,0,0,0);
}





/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */
void error(int bx)
{
   switch (bx) {
	   case 0:
	   /* error 0 = "File not found." */
	   interrupt(16, 3654, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3695, 0, 0, 0); interrupt(16, 3700, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3686, 0, 0, 0); interrupt(16, 3695, 0, 0, 0); interrupt(16, 3701, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   break;
	   case 1:
	   /* error 1 = "Bad file name." */
	   interrupt(16, 3650, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0); interrupt(16, 3689, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3693, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0);
	   break;
	   case 2:
	   /* error 2 = "Disk full." */
	   interrupt(16, 3652, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3699, 0, 0, 0);
	   interrupt(16, 3691, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0);
	   interrupt(16, 3701, 0, 0, 0); interrupt(16, 3692, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   break;
	   default:
	   /* default = "General error." */
	   interrupt(16, 3655, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3681, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3685, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3695, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0);
   }
   interrupt(16, 3630, 0, 0, 0); interrupt(16, 3597, 0, 0, 0); interrupt(16, 3594, 0, 0, 0);
   interrupt(33, 5, 0, 0, 0);
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   /*return;*/
  switch(ax) {
   case 0:  printString(bx, cx); break;
    case 1: readString(bx); break;
    case 2: readSectors(bx,cx,dx); break;
    case 3: readFile(bx,cx, dx); break;
    case 4: runProgram(bx, cx); break;
    case 5: stop();
    case 6: writeSectors(bx,cx,dx); break;
     /*case 7: case 8: case 9: case 10: */
    /*  case 11:*/
    case 12: clearScreen(bx,cx); break;
    case 13: writeInt(bx,cx); break;
    case 14: readInt(bx); break;
    case 15: error(bx); break;
    default: error(3);
  }
}
