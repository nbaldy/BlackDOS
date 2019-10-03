#include "blackdos.h"

void main()
{
    int i = 0, a = 0, b = 0, c = 0;
    char adj1[80], adj2[80], adj3[80], name[80];

    /* MADLIBS */
    PRINTS("Enter an adjective: \0");
    SCANS(adj1);
    PRINTS("Enter another adjective: \0");
    SCANS(adj2);
    PRINTS("Enter yet another adjective: \0");
    SCANS(adj3);

    PRINTS("Enter a low number: \0");
    SCANN(a);
    PRINTS("Enter a high number: \0");
    SCANN(b);

    while( c < 1 || c > 7)
    {
      PRINTS("Enter a number between 1 and 7: \0");
      SCANN(c);
    }

    PRINTS("Enter your name: \0");
    SCANS(name);

    /*Clear screen, keeping old colors*/
    CLRSCRN(-1, -1);

    /* Print Madlibs*/
    PRINTS("   Dear \0");
    PRINTS(name);
    PRINTS(", \r\n I would like to inform you that you do not need to grade \r\n Nicole, Elena, and Tim's Project. I have already determined \r\n that this \0");
    PRINTS(adj1);
    PRINTS(" project deserves an A\0");
    for(i=0; i<c; i++)
    {
      PRINTS("+\0");
    }
    PRINTS(", which you can put down in the \r\n gradebook as \0");
    PRINTN(b);
    PRINTS(" out of \0");
    PRINTN(a);

    PRINTS(". Nicole, Elena, and Tim \r\n are my very favorite students because they are so \0");
    PRINTS(adj2);

    PRINTS(". \r\n Thank you for understanding. \r\n\r\n    - The great and \0");
    PRINTS(adj3);
    PRINTS(" Dr. O'Niel\0");
    END;

  }
