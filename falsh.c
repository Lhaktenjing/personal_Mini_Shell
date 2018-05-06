#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_INPUT 256
//function declarations for built-in commands
//function for "cd" command
int falshCD(char ** args)
{
    //no arguments passed
    if (args[1] == NULL) {
    fprintf(stderr, "falsh: expected command is: cd [dir]\n");
    } else {
    //do chdir, if not sucessfull(doesn't return 0)
    if (chdir(args[1]) != 0) {
    fprintf(stderr, "falsh: no such file or directory\n");
    }
  }
  return 1;
}
//funtion to print description to screen
void falshHelp()
{
     //print help
     printf("Welcome to the falsh shell program\n");
     printf("You can run the following built in commands\n")
     printf("Note: arguments in [] are optional, in <> are mandatory\n")
     printf("1. exit- usage:exit - exits the shell\n");
     printf("2. pwd- usage:pwd - prints current directory\n")
     printf("3. cd- usage:cd [dir] - chages specified directory\n");
     printf("4. setpath- usage setpath <dir> [dir]...[dir] - sets the path as specified\n");
}
void faslhPwd();
{
     char workingDirectory[1024];
     getcwd(workingDirectory, sizeof(workingDirectory));
     printf("\nDir: %s", workingDirectory);
}
int falshExit(char ** args);
{
     return 0;
}
int falshSetpath(char ** args);
{


}


