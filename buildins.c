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
