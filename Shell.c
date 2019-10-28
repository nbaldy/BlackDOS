#include "blackdos.h"

void parseCmnd(char* buffer, int* cmd, char* arg1, char* arg2);

void main()
{

  /* Holds information for parsing commands and config values - note max 512 chars*/
  char buffer[512], arg1[80], arg2[80];
  int bgnd, fgnd, cmd;

  /* Read config in sector 258 into buffer then save the config variables */
  READSCTR(buffer, 258, 1);

  bgnd = buffer[0]-'0'+1;
  fgnd = buffer[1]-'0'+1;

  /* Clear screen and print welcome */
  CLRSCRN(bgnd,fgnd);
  PRINTS("Welcome to the Shell!\r\n\0");

  /* Start Shell UI*/
  while(1)
  {
    PRINTS("\r\n^(~(oo)~)^ \0");
    SCANS(buffer);
    parseCmnd(buffer);
  }

}


/* Compare 2 strings, return 1 (true) if identical, else 0 */
int compare(char *c1, char *c2, int size)
{
  int i;

  for(i = 0; i < size; i++)
  {

    if(c1[i] != c2[i])
    {
      return 0;
    }

  }
  return 1;
}


/* Read a buffer up to a delimitor or the nullterminator and place this in result*/
/* Skip leading deliminators*/
int readToChar(char* buffer, char delim, char* result)
{
  /* index of delimitor */
  int len = 0;
  int skip = 0;

  /* skip leading deliminators*/
  while(buffer[skip] == delim)
    skip++;

  while(!(buffer[len+skip] == delim || buffer[len+skip] == '\0'))
  {
    result[len] = buffer[len+skip];
    len++;
  }
  result[len] = '\0';

  /* the index at which the substring ends */
  return len+skip;
}

/* Reboot terminal - all code after should not execute */
void boot(char* buffer)
{
  /* Arguments, print warning*/
  if(buffer[0] != '\0')
  {
    if(buffer[0] == ' ')
      PRINTS("Warning: Argument provided are ignored. Rebooting... \r\n\0");
    else
    { /*attempted 5 char command or mistype*/
      PRINTS("ERROR: Badly formatted command\r\n\0");
      return;
    }
  }

  REBOOT();
  PRINTS("ERROR: Reboot failed!\r\n\0");
  return;
}


/* Print buffer if present, else simply return */
void echo(char* buffer)
{
  /* No comment */
  if(buffer[0] == '\0')
  {
    return;
  }

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command\r\n\0");
    return;
  }

  /* Print comment, skipping space */
  PRINTS(&buffer[1]);
  PRINTS("\r\n\0");
}


/* Clears screen, not changing screen colors */
void clrs()
{
  CLRSCRN(-1,-1);
  return;
}


/***** Stub Commands follow *****/

void copy(char* buffer)
{
  char file1[80], file2[80];
  int start = 1; /* skip space */

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For copy command: copy file1 file2\r\n\0");
    return;
  }

  /* Get file1 */
  start +=readToChar(&buffer[start], ' ', file1);
  /* Get file2 */
  start +=readToChar(&buffer[start], ' ', file2);

  /* Empty Parameter */
  if(file1[0] == '\0' || file2[0] == '\0')
  {
    PRINTS("ERROR: Copy requires two parameters: copy file1 file2\r\n\0");
    return;
  }


  /* Third argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Copy requires only two parameters: copy file1 file2\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: copy\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(file1);
  PRINTS("\r\n\0");
  PRINTS("Arg 2: \0");
  PRINTS(file2);
  PRINTS("\r\n\0");

}

void ddir(char* buffer)
{
  //* Arguments, print warning*/
  if(buffer[0] != '\0')
  {
    if(buffer[0] != ' ')
    {
      PRINTS("ERROR: Badly formatted command\r\n\0");
      return;
    }
  }

  PRINTS("Command: ddir\r\n\0");
  RUNPROGRAM("ddir\0", 4);
}

void exec(char* buffer)
{
  char filename[80];
  int start = 1; /* skip space */

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For Exec command: exec filename\r\n\0");
    return;
  }

  /* Get filename */
  start += readToChar(&buffer[start], ' ', filename);

  /*empty parameter*/
  if(filename[0] == '\0')
  {
    PRINTS("ERROR: Exec takes one parameter: exec filename\r\n\0");
    return;
  }


  /* Second argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Exec requires only one arg: exec filename\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: exec\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(filename);
  PRINTS("\r\n\0");

  RUNPROGRAM(filename, 4);
}

void help(char* buffer)
{
  /* Arguments, print warning*/
  if(buffer[0] != '\0')
  {
    if(buffer[0] == ' ')
      PRINTS("Warning: Argument provided are ignored.\r\n\0");
    else
    { /*attempted 5 char command or mistype*/
      PRINTS("ERROR: Badly formatted command\r\n\0");
      return;
    }
  }

  /*PRINTS("Command: help\r\n\0");*/

  PRINTS("\r\nNAME: Shell - a case-sensitive command interpreter that is capable of file and \r\nkeyboard I/O which allows the user to manipulate files, the console display, andthe printer.\r\n\0");
  PRINTS("\r\nCMD	\t PARAMETERS      DESCRIPTION\r\n\0");
  PRINTS("boot                  reboot the system\r\n\0");
  PRINTS("clrs                  clear the screen\r\n\0");
  PRINTS("echo  comment         display comment on screen followed by a new line\r\n\0");
  PRINTS("copy	 file1, file2    create file2 and copy all bytes of file1 to file1 without                       deleting file1\r\n\0");
  PRINTS("ddir                  list directory contents\r\n\0");
  PRINTS("exec  filename        execute filename\r\n\0");
  PRINTS("help                  print this user manual\r\n\0");
  PRINTS("prnt  filename        print contents of filename to printer\r\n\0");
  PRINTS("remv  filename        delete filename\r\n\0");
  PRINTS("senv                  set environment variables\r\n\0");
  PRINTS("show  filename        display contents of filename on console\r\n\0");
  PRINTS("twet  filename        create a text file called filename\r\n\0");
}

void prnt(char* buffer)
{
  char filename[80];
  int start =1;

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For Prnt command: prnt filename\r\n\0");
    return;
  }

  /* Get file1 */
  start +=readToChar(&buffer[start], ' ', filename);

  /*empty parameter*/
  if(filename[0] == '\0')
  {
    PRINTS("ERROR: Prnt takes one parameter: prnt filename\r\n\0");
    return;
  }

  /* Second argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Prnt requires only one arg: prnt filename\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: prnt\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(filename);
  PRINTS("\r\n\0");
}

void remv(char* buffer)
{
  char filename[80];
  int start = 1; /* skip space */

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For Remv command: remv filename\r\n\0");
    return;
  }

  /* Get file1 */
  start +=readToChar(&buffer[start], ' ', filename);

  /*empty parameter*/
  if(filename[0] == '\0')
  {
    PRINTS("ERROR: Remv takes one parameter: remv filename\r\n\0");
    return;
  }

  /* Second argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Remv requires only one arg: remv filename\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: remv\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(filename);
  PRINTS("\r\n\0");
}

void senv(char* buffer)
{
  /* Arguments, print warning*/
  if(buffer[0] != '\0')
  {
    if(buffer[0] != ' ')
    {
      PRINTS("ERROR: Badly formatted command\r\n\0");
      return;
    }
  }

  RUNPROGRAM("Stenv\0", 4);
  PRINTS("Command: senv\r\n\0");
}

void show(char* buffer)
{
  char filename[80];
  int start = 1; /* skip space */

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For Show command: show filename\r\n\0");
    return;
  }

  /* Get file1 */
  start +=readToChar(&buffer[start], ' ', filename);

  /*empty parameter*/
  if(filename[0] == '\0')
  {
    PRINTS("ERROR: Show takes one parameter: show filename\r\n\0");
    return;
  }

  /* Second argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Show requires only one arg: show filename\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: show\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(filename);
  PRINTS("\r\n\0");
  PRINTS("\r\n\0");
}

void twet(char* buffer)
{
  char filename[80];
  int start = 1; /* skip space */

  /* No space - command badly formatted */
  if(buffer[0] != ' ')
  {
    PRINTS("ERROR: Badly formatted command. For Twet command: twet filename\r\n\0");
    return;
  }

  /* Get file1 */
  start +=readToChar(&buffer[start], ' ', filename);

  /*empty parameter*/
  if(filename[0] == '\0')
  {
    PRINTS("ERROR: Twet requires one parameter: twet filename\r\n\0");
    return;
  }

  /* Second argument provided - badly formatted command */
  if(buffer[start] == ' ')
  {
    PRINTS("Warning: Twet requires only one arg: twet filename\r\n\0");
    PRINTS("Extra arguments ignored\r\n\0");
  }

  /* Command valid */
  PRINTS("Command: twet\r\n\0");
  PRINTS("Arg 1: \0");
  PRINTS(filename);
  PRINTS("\r\n\0");
}

/* Do the work - take buffer and parse it into commands,
 * Then call the appropriate command  */
void parseCmnd(char* buffer)
{
  if(compare(buffer, "boot", 4))
    boot(&buffer[4]);
  else if(compare(buffer, "clrs", 4))
    clrs(&buffer[4]);
  else if(compare(buffer, "echo", 4))
    echo(&buffer[4]);
  else if(compare(buffer, "copy", 4))
    copy(&buffer[4]);
  else if(compare(buffer, "ddir", 4))
    ddir(&buffer[4]);
  else if(compare(buffer, "exec", 4))
    exec(&buffer[4]);
  else if(compare(buffer, "help", 4))
    help(&buffer[4]);
  else if(compare(buffer, "prnt", 4))
    prnt(&buffer[4]);
  else if(compare(buffer, "remv", 4))
    remv(&buffer[4]);
  else if(compare(buffer, "senv", 4))
    senv(&buffer[4]);
  else if(compare(buffer, "show", 4))
    show(&buffer[4]);
  else if(compare(buffer, "twet", 4))
    twet(&buffer[4]);
  else
    PRINTS("ERROR: Badly formatted command\r\n\0");

}
