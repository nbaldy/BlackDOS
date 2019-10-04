
void parseCmnd(char *buffer, int &cmd, char *arg1, char *arg2)
{
  /* From first 4 characters figure out the command
   *  make an int to make later processing easier */

  /* formatting - 5th char should be a space */

  /* Read to next space or null terminator - this gets put in arg1 */

  /* Read to next space or null terminator - this gets put in arg2 */

  /* Echo, however, puts everything (spaces or no) in arg1 to write back to the screen */

  /* args 1 and 2 can be empty */


}

void main()
{

  /* Read in Configuration Values*/
  char buffer[512], arg1[80], arg2[80];
  int bgnd, fgnd, cmd;


  /* Read config in sector 268 into buffer then save the config variables */
  READSCTR(buffer, 258,1);
  bgnd = buffer[0];
  fgnd = buffer[1];

  CLRSCRN(bgnd,fgnd);
  LPRINTS(" Welcome to the Shell!\0");

  while(1)
  {
    LPRINTS("^(~(oo)~)^ ");
    SCANS(buffer);
    ParseCmnd(buffer, cmd, arg1, arg2);
    

  }


}
