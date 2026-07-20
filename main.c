#include <stdio.h>
#include "shell.h"
#include <strings.h>

int shell_builds(char** args,char** env,char* initial_directory){
    
    if(strcmp(args[0],"cd")==0){
        return command_cd(args,initial_directory);
    }
    else if(strcmp(args[0],"echo")==0){
        return command_echo(args,env);
    }
    else if(strcmp(args[0],"pwd")==0){
        return command_pwd();
    }
    else if(strcmp(args[0],"which")==0){
        return command_which(args,env);
    }
    else if(strcmp(args[0],"env")==0){
        return command_env(env);
    }
    else if(strcmp(args[0],"exit")==0){
        exit(EXIT_SUCCESS);
    }
    else{
        //not a buildin command
        
        return 1;
    }

    return 1;
}

void shell_loop(char** env){
    char* input = NULL;
    size_t input_size=0;
    char** args;

    char* initial_directory = getcwd(NULL,0);
    
    while(1){
        char* cwd;
        cwd = getcwd(NULL,0);
        if(cwd!=NULL){
            printf("\e[32m[My_Shell] /%s>\e[0m",cwd);
            if(getline(&input,&input_size,stdin)==-1){
                perror("getline");
                break;
            }
            
            args = parse_input(input);
            
            if(args[0]){
                shell_builds(args,env,initial_directory);
            }
        }
        else{
            perror("getcwd");
            return;
        }
        
    }
    free_tokens(args);
}

int main(int argc,char** argv,char** env){
    (void)argc;
    (void)argv;

    shell_loop(env);
}



