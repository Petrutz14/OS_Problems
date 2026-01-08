#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#define SIZE 32

int main(int argc,char** argv){
    pid_t pid[argc+1];
    for(int i=1;i<argc;i++){
        pid[i]=fork();
        if(pid[i]==0){
            printf("Sunt la %d\n",i);
            usleep(10000);
            fflush(stdout);
            exit(i);
        }
    }
    for(int i=1;i<argc;i++){
        int status;
        waitpid(pid[i],&status,0);
        printf("Copilu cu %d a iesit cu %d\n",pid[i],WEXITSTATUS(status));
        //fflush(stdout);
    }




    return 0;
}