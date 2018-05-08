#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_INPUT 256
//function declarations for built-in commands
//-------------------------------------------------
//function for "cd" command
//switches to directory specified by args
int falshCD(char * args)
{
    //no arguments passed
    if (args[1] == NULL) {
    fprintf(stderr, "falsh: expected command is: cd [dir]\n");
    } else {
    //go to dir stored args[1], if not sucessfull(doesn't return 0)
    if (chdir(args[1]) != 0) {
    fprintf(stderr, "falsh: no such file or directory\n");
    }
  }
  return 1;//no errors
}
//--------------------------------------------------
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
//----------------------------------------------------
//function for 'pwd' command
//prints the path to current directory
void faslhPwd();
{
     char workingDirectory[1024];//to store the returned path of current dir
     getcwd(workingDirectory, sizeof(workingDirectory));//get the directory and store in workingDirectory
     printf("\nDir: %s", workingDirectory);//print it to the screen
}
//-------------------------------------------------------
//function to exit the shell
int falshExit();
{
     return 0;//just exit the shell
}
//--------------------------------------------------------
//function for setpath
//sets the path as specified by the arg
void setPath();
{


}
//---------------------------------------------------------
//function to return an array of args passed by user
//reads user input and breaks it into arguments
//and returns the args ordered in an array user input line
char getArrayOfArgs()
{
     char Input[MAX_CHAR_INPUT];//to store user input
     char * Args[MAX_CHAR_INPUT];//array of pointers to store each user input arg
     char letter; //to read each letter from arg
     const char delim[2] = " ";//for delimeter
     int position = 0;//to keep track of where are we at the arg array
     char * arg = strtok(line, delim);
     while(arg != NULL)
     {
	Args[position] = arg;//store current arg to arg array
        position++;//increase counter
        arg = strtok(NULL, delim);//next token
     }
     Args[position] = NULL; //end of args
     return Args;//return array containing args
}

//---------------------------------------------------------
//function to take user input and process those inputs
//compares user inpput commands and calls appropraite function to run
//
void processArg()
{
     char line[MAX_CHAR_INPUT];//to store user input args
     int numOfArgs = 0;//no args read yet
     while(1)//keeps on looping unless user chooses to exit
     {
	falshPwd();
	printf("> ");
	char * Args[MAX_CHAR_INPUT] = getArrayOfArgs();
	
     }
}


