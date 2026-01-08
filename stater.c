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
    int fd=open(argv[1],O_RDONLY);
    struct stat stater;

    fstat(fd,&stater);
    printf("%s",stater.st_mode & S_IRUSR ? "r" : "-");
    printf("%s",stater.st_mode & S_IWUSR ? "w" : "-");
    printf("%s",stater.st_mode & S_IXUSR ? "x" : "-");
    printf("%s",stater.st_mode & S_IRGRP ? "r" : "-");
    printf("%s",stater.st_mode & S_IWGRP ? "w" : "-");
    printf("%s",stater.st_mode & S_IXGRP ? "x" : "-");
    printf("%s",stater.st_mode & S_IROTH ? "r" : "-");
    printf("%s",stater.st_mode & S_IWOTH ? "w" : "-");
    printf("%s",stater.st_mode & S_IXOTH ? "x" : "-");







    return 0;
}