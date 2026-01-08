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

void afis(char *folder){
    DIR* dir;
    struct dirent* entry;

    if((dir=opendir(folder))<0){
        printf("Error opening the folder %s\n",folder);
        exit(-1);
    }

    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
            continue;
        }
        char path[1024];
        snprintf(path,sizeof(path),"%s/%s",folder,entry->d_name);
        if(entry->d_type==DT_DIR){
            afis(path);
        }
        else{
            printf("%s:\n\n\n\n\n\n",path);
            int fd=open(path,O_RDONLY);
            if(fd<0){
                printf("Error opening the file %s\n",path);
                exit(-1);
            }
            int n;
            char buf[1024];
            while((n=read(fd,buf,SIZE))>0){
                buf[n]='\0';
                printf("%s",buf);
            }
            if(n<0){
                printf("Error reading from file %s",path);
                exit(-1);
            }
            close(fd);
        }
        closedir(dir);




    }



}



int main(int argc,char **argv){
    if(argc!=2){
        printf("Incorect ussage:./<executable> <folder>");
        exit(-1);
    }

    afis(argv[1]);


    return 0;
}