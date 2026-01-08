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
#define SIZE 32

void depth(char *folder,int *i){
    DIR* dir;
    struct dirent* entry;

    dir=opendir(folder);
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
            continue;
        }

        char path[1024];
        snprintf(path,sizeof(path),"%s/%s",folder,entry->d_name);

        if(entry->d_type==DT_DIR){
            pid_t pid=fork();
            if(pid==0){
                i++;
                depth(path,i);
                exit(i);
            }
        }
    }



}


int main(int argc,char **argv){
    int i=0;
    int depthmax=0;
    depth(argv[1],i);
    int status;
    while((wait(&status))>0){
        if(WEXITSTATUS(status)>depthmax){
            depthmax=WEXITSTATUS(status);
        }
    }
    printf("%d",depthmax);


    return 0;
}