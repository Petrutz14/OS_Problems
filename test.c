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

int main(int argc,char **argv){
    for(int i=1;i<argc;i++){
        int fd=open(argv[i],O_RDONLY);
        char buf[1024];
        int n;
        char inainte=' ';
        int cate=0;
        while((n=read(fd,buf,SIZE))>0){
            buf[n]='\0';
            for(int j=0;j<n;j++){
                char c=buf[j];
                if(!(c==' ' || c=='\n' || c=='\t') && (inainte==' ' || inainte=='\n' || inainte=='\t')){
                    cate++;
                }
                inainte=c;
            }
        }
        printf("%d ",cate);
        close(fd);
    
    }



    return 0;
}