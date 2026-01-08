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
int x[1];
int main(int argc,char** argv){
    if(argc<2){
        fprintf(stderr,"sa moara ma ta");
        exit(-1);
        }  
    pid_t pid=fork();
    if(pid==0){
        execlp("","",argv[1],argv[2],NULL);
        perror("execlp failed");
        exit(1);
    }else if(pid>0){
        wait(NULL);
        printf("Child complete");
    }

    


    return 0;
}