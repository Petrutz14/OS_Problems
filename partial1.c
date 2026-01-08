#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/wait.h>
#define SIZE 32

int main(int argc,char **argv){
    for(int i=1;i<argc;i++){
        pid_t pid=fork();
        if(pid==0){
            //printf("Copil nr %d\n",i);
            for(int j=0;j<strlen(argv[i]);j++){
                if(argv[i][j]>='a' && argv[i][j]<='z'){
                    argv[i][j]-=32;
                }
            }
            printf("%s ",argv[i]);
            exit(i);
        }
    }
    while((wait(NULL))>0);




    return 0;
}
