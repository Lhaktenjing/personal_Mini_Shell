#define _GNU_SOURCE
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
void falshCD(char * arg)
{  //no arguments passed
    if (arg == NULL)
    fprintf(stderr, "falsh: expected command is: cd [dir]\n");
    //go to dir stored args[1], if not sucessfull(doesn't return 0) fail gracefully
    else if (chdir(arg) != 0)
    fprintf(stderr, "falsh: no such file or directory\n");
}
//--------------------------------------------------
//funtion to print description to screen
void falshHelp()
{
     //print help
     printf("Welcome to the falsh shell program\n");
     printf("You can run the following built in commands\n");
     printf("Note: arguments in [] are optional, in <> are mandatory\n");
     printf("1. exit- usage:exit - exits the shell\n");
     printf("2. pwd- usage:pwd - prints current directory\n");
     printf("3. cd- usage:cd [dir] - chages specified directory\n");
     printf("4. setpath- usage setpath <dir> [dir]...[dir] - sets the path as specified\n");
}
//----------------------------------------------------
//function for 'pwd' command
//prints the path to current directory
void falshPwd()
{
     char workingDirectory[1024];//to store the returned path of current dir
     getcwd(workingDirectory, sizeof(workingDirectory));//get the directory and store in workingDirectory
     printf("Dir: %s\n", workingDirectory);//print it to the screen
}
//--------------------------------------------------------
//function for setpath
//sets the path as specified by the arg
void setPath(char * Arg [], int numArg)
{
    char * current;
    int i =1;//first Arg i.e. Arg[0] is "setpath"
    for(i; i< numArg; i++){
    current = getenv("PWD");
    if(setenv(current, Arg[i], 1)!= 0)
    fprintf(stderr,"cannot set path\n");
    }
}
//------------------------------------------------
//function to redirect command output to textfile
//takes in the command and the text and the text filename as parameter
void redirection(char * Args[])
{
    int index = 0;//counter
    while(Args[index]!=">")//while reaches the end of args before ">"
    {
        index++;
    }
    char * otherArgs;
    int argEnd = index;
    FILE * file = fopen(Args[argEnd + 1], "w" );
    if (file ==NULL)
    fprintf(stderr,"file opening failed\n");//couldn't open file
    dup2(fileno(file),1);//redirect stdout output to text file
    execvp(Args[0], Args);//execute command
    fclose(file);
 }
//---------------------------------------------------------
//function to take user input and process those inputs
//first tokenizes the user input into a string array which ends at NULL
//compares user inpput commands and calls appropraite function to run
//
void processArg()
{
     while(1)//keeps on looping unless user chooses to exit
     {
     char * commands[] = {"pwd","cd","help","setpath","exit"};//strtok adds \n at end
     char * Args[MAX_CHAR_INPUT];
     char line[1024]; //to read user input from arg
     const char delim[1] = " ";//for delimeter
     char * temp;
     char * arg;
     int numOfArgs;
     printf("falcon shell");
     printf("> ");
     fflush(stdin);
     fgets(line, 1024, stdin);//get user input and store in line
     numOfArgs = 0;//to count number of arguments
     arg = strtok(line, delim);
     while(arg != NULL)
     {
        Args[numOfArgs] = arg;//store current arg to arg array
        numOfArgs++;
        arg = strtok(NULL, delim);//next token
     }
     int length = strlen(Args[numOfArgs-1]);
     Args[numOfArgs-1][length-1] = NULL;//strtok adds a /n to the last token
     Args[numOfArgs] = NULL; //end of args
     if (numOfArgs > 0 && numOfArgs < 3)//for 1 or 2 args
     {
     if(strcmp(Args[0],commands[4])==0) { printf("exiting\nThank you for using Falcon Shell\n"); return;} //if user entered exit
     else if(strcmp(Args[0],commands[1])==0) //if first arg is "cd"
     {
        if(numOfArgs == 2) falshCD(Args[1]); //if file was passed after "CD" go to file
        else if (numOfArgs == 1) chdir(getenv("HOME"));//else only "cd" is typed go to home dir
        else printf("Accepted command syntax is: cd [dir]\n");//else invalid command style
     }
     else if (strcmp(Args[0],commands[0])==0) falshPwd();//if user entered pwd
     else if (strcmp(Args[0],commands[2])==0) falshHelp();//if user entered help
     else printf("%s command not found. Type help for available commands.\n",Args[0]);
     }
     else if(numOfArgs>=4)//more than 4 args means file redirection
     {
     if(strcmp(Args[0],commands[3])==0) setPath(Args,numOfArgs);
     else redirection(Args);
     }
     }
}
int main(int argc, char * argv[])
{
    if (argc == 1)//only ./falsh called
        processArg();//loop
    else if (argc == 2 && strcmp(argv[1],"-h")==0)
    {
        falshHelp();//print help
        processArg();//go to loop
    }
    return 0;
}
