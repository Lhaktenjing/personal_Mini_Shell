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
void falshCD(char * args[])
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
void faslhPwd()
{
     char workingDirectory[1024];//to store the returned path of current dir
     getcwd(workingDirectory, sizeof(workingDirectory));//get the directory and store in workingDirectory
     printf("\nDir: %s", workingDirectory);//print it to the screen
}
//--------------------------------------------------------
//function for setpath
//sets the path as specified by the arg
void setPath()
{


}
//---------------------------------------------------------
//function to return an array of args passed by user
//reads user input and breaks it into arguments
//and returns the args ordered in an array user input line
char ** getArrayOfArgs()
{
     char Input[MAX_CHAR_INPUT];//to store user input
     char * Args[MAX_CHAR_INPUT];//array of pointers to store each user input arg
     char letter; //to read each letter from arg
     char line[MAX_CHAR_INPUT];
     fgets(line, MAX_CHAR_INPUT, stdin);//get user input and store in line
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
    FILE *file = fopen(Args[argEnd + 1], "w" );
    if (file ==NULL) fprinf(stderr,"file opening failed");//couldn't open file
    excvp(Args[0], Args);//execute command
    fclose(file);
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
     printf("falcon shell");
     printf("> ");
     char * Args[MAX_CHAR_INPUT];
     Args = getArrayOfArgs();//get array of Args
     while(Args[numOfArgs] != NULL)//to count number of args in arg array
     {
        numOfArgs++;//next index in arg array
     }
     if (numOfArgs > 0 && numOfArgs < 2)//for 1 or 2 args
     {
     if(strcmp(Args[0],"exit")==0) return; //if user entered exit
     else if (strcmp(Args[0],"cd")==0) //if first arg is "cd"
     {
        if(numOfArgs == 2) falshCD(Args[1]); //if file was passed after "CD" go to file
        else if (numOfArgs == 1) chdir(getenv("HOME"));//else only "cd" is typed go to home dir
        else printf("Accepted command syntax is: cd [dir]\n")//else invalid command style
     }
     else if (strcmp(Args[0],"pwd")==0) falshPwd();//if user entered pwd
     else if (strcmp(Args[0],"help")==0) falshHelp();//if user entered help
     }
     else if(numOfArgs>=4)//more than 4 args means file redirection
     {
         redirection(Args);
     }
     }
}
int main(int argc, char * argv[])
{
    if (argc == 1)//only ./falsh called
        processArg();//loop
    else if (argc == 2 && argv[1]=="-h")
    {
        falshHelp();//print help
        processArg();//go to loop
    }
    return 0;
}
