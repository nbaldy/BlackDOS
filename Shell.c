#include "blackdos.h"

/*int compare(char *c1, char *c2, int size);*/
void parseCmnd(char* buffer, int* cmd, char* arg1, char* arg2);

void main()
{

  /* Holds information for parsing commands and config values*/
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
    parseCmnd(buffer, &cmd, arg1, arg2);
  }

}


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

int readToChar(int start, char delim, char* buffer, char* result)
{
  int end = start + 1;
  while(buffer[end] != delim && buffer[end] != '\0')
  {
    result[end - (start + 1)] = buffer[end];
    ++end;
  }
  result[end] = '\0';
  return end; /*new start value (for next time i call this function)*/
}

void parseCmnd(char* buffer, int* cmd, char* arg1, char* arg2)
{
  *cmd = -1;

  if(compare(buffer, "boot", 4))
  {
    REBOOT();
    PRINTS("Reboot failed  \r\n\0");
    return;
  }

  if(compare(buffer, "echo", 4))
  {
    if(buffer[4] != '\0')
    {
      return;
    }
    if(buffer[4] != ' ')
    {
      PRINTS("Badly formatted command\r\n\0");
      return;
    }
    PRINTS(&buffer[5]);
    PRINTS("\r\n\0");

    return;
  }

  if(compare(buffer, "clrs", 4))
  {
    CLRSCRN(-1,-1);
    return;
  }

  if(compare(buffer, "exec",4))
  {
    if(buffer[4] != ' ')
    {
      PRINTS("Badly formatted command\r\n\0");
      return;
    }

    readToChar(4, ' ', buffer, arg1);

    PRINTS("Command: exec\r\n\0");
    PRINTS("Arg 1: \0");
    PRINTS(arg1);
    PRINTS("\r\n\0");
  }

  if(compare(buffer, "copy",4))
  {
    if(buffer[4] != ' ')
    {
      PRINTS("Badly formatted command\r\n\0");
      return;
    }

    readToChar(4, ' ', buffer, arg1);

    PRINTS("Command: exec\r\n\0");
    PRINTS("Arg 1: \0");
    PRINTS(arg1);
    PRINTS("\r\n\0");
  }


}
