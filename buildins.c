#include <stdio.h>
#include "shell.h"



//cd, cd.., cd ~, handle non existing dir, permission issues
int command_cd(char** args,char* initial_directory){
    if(args[1]==NULL){
        printf("Expected an argument with \'cd [path]\'\n");
    }
    else if(chdir(args[1])==0){
        //chdir returns 0 for success
        printf("cd Worked\n");
    }
    else{
        perror("cd");
    }
    return 0;
}

int command_pwd(){
    char* cwd;

    cwd = getcwd(NULL,0); //This uses dynamic allocation

    if(cwd!=NULL){
        printf("%s\n",cwd);
        free(cwd);
    }
    else{
        perror("getcwd");
    }
    return 0;  
}

int command_env(char** env){
    size_t j = 0;
    while(env[j]){
        printf("%s",env[j]);
        j++;
    }
    printf("\n");
    return 0;
}

//echo HI, echo -n HI, echo $PATH
int command_echo(char** args,char** env){
    
    int new_line = 1;
    size_t i=1;    

    if(args[1]!=NULL && strcmp(args[1],"-n")==0){
        new_line=0;
        i++;
    }

    //process remaining args using loop
    for(;args[i];i++){
        if(args[i][0] == '$'){
            //handle env variables and then print path
            char* path = getenv(args[i]+1);
            if(path!=NULL){
                printf("%s",path);
            }
        }
        else{
            printf("%s",args[i]);
        }

        if(args[i+1]!=NULL){ 
            new_line=0;
            printf(" ");
        }

        if(new_line) printf("\n");
    }
    return 0;
}


//external function path finder in PATH
char* find_cmd_path(const char* command,char** env){
    
}

int command_which(char** args,char** env){

    if(args[1]==NULL){
        printf("Expected arguments with \'which\'\n");
        return 1;
    }

    //build in cmd
    const char* build_in_cmds[] = {"cd","pwd","echo","env","setenv","unsetenv","which","exit",NULL};
    for (size_t i = 0; build_in_cmds[i]; i++){
        if(strcmp(args[1],build_in_cmds[i])==0){
            printf("Shells Build in Command %s\n",args[1]);
            return 0;
        }
    }
    
    //external cmd
    char* path = find_cmd_path(args[1],env);
    
    if(path!=NULL){
        printf("PATH : %s\n",path);
        free(path);
        return 0;
    }
    
    if(path==NULL){
        printf("Path Not Found\n");
    }
}

int command_clear(){
    system("clear");
}

int command_help(){
    printf("Avaliable Commands :\n");
    printf("%-25s - %s\n","      cd <path to directory>","Changes the current directory");
    printf("%-25s - %s\n","      pwd","Prints the current working directory");
    printf("%-25s - %s\n","      env","Displays all working enviroment variables");
    printf("%-25s - %s\n","      echo <text>","Prints the given text");
    printf("%-25s - %s\n","      which","Locates an executable in the system's path");
    printf("%-25s - %s\n","      help","Displays this help message");
    printf("%-25s - %s\n","      clear","Clears the terminal");
    printf("%-25s - %s\n","      exit","Exit the shell");

    return 0;
}


