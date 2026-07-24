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
    char* original_path = NULL; //stores the original path
    char* duplicate_path = NULL; //duplicated and store the path to prevent changing of env
    char* token = NULL; //tokenizes dir from path
    char full_path[1024]; //Buffer to store the path
    
    for (size_t i = 0; env[i]; i++){
        if(strncmp(env[i],"Path=",5)==0||strncmp(env[i],"PATH=",5)==0||strncmp(env[i],"path=",5)==0){
            original_path = env[i]+5;
            break;
        }
    }

    if(original_path == NULL){
        printf("Could not Find Path in env\n");
        return NULL;
    }

    duplicate_path = strdup(original_path);

    if(duplicate_path==NULL){
        perror("strcpy");
        return NULL;
    }

    token = strtok(duplicate_path,":");
    while ((token!=NULL)){
        size_t len = strlen(token);
        if(token[len-1]!='/'){
            snprintf(full_path,sizeof(full_path),"%s%s%s",token,"/",command);
        }
        else{
            snprintf(full_path,sizeof(full_path),"%s%s",token,command);

        }
        if(access(full_path,F_OK)==0){
            free(duplicate_path);
            return strdup(full_path);
        }

        token = strtok(NULL,":");
    }
    
    free(duplicate_path);
    return NULL;
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

int command_history(char** history){
    for(int i=0;i<MAX_HISTORY;i++){
        if(history[i]==NULL) continue;
        printf("%d - %s\n",i+1,history[i]);
    }
    return 0;
}
int command_help(){
    printf("Avaliable Commands :\n");
    printf("%-30s - %s\n","      cd <path to directory>","Changes the current directory");
    printf("%-30s - %s\n","      pwd","Prints the current working directory");
    printf("%-30s - %s\n","      env","Displays all working enviroment variables");
    printf("%-30s - %s\n","      echo <text>","Prints the given text");
    printf("%-30s - %s\n","      which","Locates an executable in the system's path");
    printf("%-30s - %s\n","      clear","Clears the terminal");
    printf("%-30s - %s\n","      exit","Exit the shell");
    printf("%-30s - %s\n","      help","Displays this help message");
    

    return 0;
}


