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
#define SIZE 1024

void search(char* folder,char* file){
    DIR* dir;
    struct dirent* entry;
    int found=0;
    dir=opendir(folder);
    while((entry=readdir(dir))!=NULL && found==0){
        if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0){
            continue;
        }
        char path[1024];
        snprintf(path,sizeof(path),"%s/%s",folder,entry->d_name);
        if(strcmp(file,entry->d_name)==0){
            found=1;
            int fd=open(path,O_RDONLY);
            int n;
            char content[1024];
            while((n=read(fd,content,SIZE))>0){
                printf("%s",content);
                content[n]='\0';
            }
            close(fd);
        }
        if(entry->d_type==DT_DIR){
            pid_t pid=fork();
            if(pid==0){
                printf("Child is in %s with pid %d\n",path,pid);
                search(path,file);
                exit(1);
            }
        }
    }
    while((wait(NULL))>0);



}


int main(int argc,char **argv){

    search(argv[1],argv[2]);


    return 0;
}