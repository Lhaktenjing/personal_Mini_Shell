#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//function declarations for built-in commands 
int falshCD(char ** args);
int faslhPwd(char ** args);
int falshExit(char ** args);
int falshSetpath(char ** args);

