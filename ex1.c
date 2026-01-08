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
#define SIZE 16

int main(int argc,char **argv){
    int fdcom=open(argv[1],O_RDWR | O_APPEND);
    for(int i=2;i<argc;i++){
        pid_t pid=fork();
        if(pid==0){
            int fd=open(argv[i],O_RDONLY);
            char buf[1024];
            int n;
            while((n=read(fd,buf,SIZE))>0){
                write(fdcom,buf,n);
            }
            close(fd);
            exit(i);
        }
    }
    while((wait(NULL))>0);
    lseek(fdcom,0,SEEK_SET);
    int n;
    char buf[1024];
    while((n=read(fdcom,buf,SIZE))>0){
        printf("%s",buf);
        buf[n]='\0';
    }


    return 0;
}