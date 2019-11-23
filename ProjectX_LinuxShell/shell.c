// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed:Nicole Baldy, Elaine Falcione, Tim Inzitari Date: November 2019

// 3460:426 Lab 4A - Basic C shell

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for fork
#include <sys/wait.h> // for wait()


#define MAX_ARGS	64
#define MAX_ARG_LEN	16
#define MAX_LINE_LEN	80
#define WHITESPACE	" ,\t\n"

struct command_t {
   char *name;
   int argc;
   char *argv[MAX_ARGS];
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);
void printCommand_t(struct command_t x);

void checkPremade(struct command_t*);


int main(int argc, char *argv[]) {
   int pid;
   int status;
   char cmdLine[MAX_LINE_LEN];
   struct command_t command;
   while (1) {
      printPrompt();
      /* Read the command line and parse it */
      readCommand(cmdLine);

      parseCommand(cmdLine, &command);

      checkPremade(&command);

      // Commands affecting flow control - quit and empty
      if(!strcmp(command.name, "Q")) {
        kill(pid,-1);
        break;
      }
      if(!strcmp(command.name, "")) continue;

      command.argv[command.argc] = NULL;
      /* Create a child process to execute the command */
      if ((pid = fork()) == 0) {
         /* Child executing command */
        execvp(command.name, command.argv);
        printf("Bad Command, Press 'H' for help! \n");

      }
      /* Wait for the child to terminate */
      waitpid(pid, &status,0);
      kill(pid,-1);
   }

   /* Shell termination */
   printf("\n\n shell: Terminating successfully\n");
   return 0;
}

/* End basic shell */


void checkPremade(struct command_t *command)
{
  if (!strcmp(command->name, "C")) {
    command->name = "cp";
    command->argv[0] = "cp";
  }

  if (!strcmp(command->name, "D")) {
    command->name = "rm";
    command->argv[0] = "rm";
  }

  if (!strcmp(command->name, "M")) {
    command->name = "nano";
    command->argv[0] = "nano";
  }

  if (!strcmp(command->name, "P")) {
    command->name = "more";
    command->argv[0] = "more";
  }

  if (!strcmp(command->name, "S"))
  {
    command->name = "firefox";
    command->argc = 1;
    command->argv[0] = "firefox&";
  }

  if (!strcmp(command->name, "W")){
    command->name = "clear";
    command->argv[0] = "clear";
  }

  if (!strcmp(command->name, "X")){
    command->name = command->argv[1];
    command->argv[0] = command->argv[1];
    command->argc = 1;
  }

  if (!strcmp(command->name, "L"))
  {
    printf("\n");

    // Execute PWD
    char* argv[2];
    argv[0] = "pwd";
    argv[1] = NULL;

    printf("\n");

    /* Create a child to print out pwd */
    int status, pid;
    if ((pid = fork()) == 0) {

      execvp("pwd", argv);
    }
    /* Wait for pwd to terminate */
    waitpid(pid, &status,0);
    printf("\n");


    //Prepare to execute list
    command->name = "ls";
    command->argc = 2;
    command->argv[0] = "ls";
    command->argv[1] = "-l";
 }

 if (!strcmp(command->name, "E")) {
   command->name = "echo";
   command->argv[0] = "echo";
 }

 if (!strcmp(command->name, "H")) {
   command->name = "more";
   command->argc = 2;
   command->argv[0] = "more";
   command->argv[1] = "help.txt";
 }
}



void printCommand_t(struct command_t x)
{
  printf("Name: %s, argc: %i\n", x.name, x.argc);
  for (int i = 0; i < x.argc; ++i)
  {
    printf("arg%i: %s\n", i, x.argv[i]);
  }

}

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd) {
   int argc;
   char **clPtr;
   /* Initialization */
   clPtr = &cLine;	/* cLine is the command line */
   argc = 0;
   cmd->argv[argc] = (char *) malloc(MAX_ARG_LEN);
   /* Fill argv[] */
   while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {
      cmd->argv[++argc] = (char *) malloc(MAX_ARG_LEN);
   }

   /* Set the command name and argc */
   cmd->argc = argc-1;
   cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
   strcpy(cmd->name, cmd->argv[0]);
   return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - pp. 79-80 */

void printPrompt() {
   /* Build the prompt string to have the machine name,
    * current directory, or other desired information
    */
   char* promptString = "\nlinux (tsi3 emf66 neb45) ¯\\_(ツ)_/¯ |>";
   printf("%s ", promptString);
}

void readCommand(char *buffer) {
   /* This code uses any set of I/O functions, such as those in
    * the stdio library to read the entire command line into
    * the buffer. This implementation is greatly simplified,
    * but it does the job.
    */
   fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */
