#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// #include <sys/wait.h>

#define MAX_INPUT 1024

char** parse_input(char* input);
void free_tokens(char** tokens);
int shell_builds(char** args,char** env,char* initial_directory);

//build commands 
int command_cd(char** args,char* initial_directory);
int command_echo(char** args,char** env);
int command_which(char** args,char** env);
int command_env(char** env);
int command_pwd();