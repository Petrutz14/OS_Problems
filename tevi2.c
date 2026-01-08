#include <sys/wait.h>
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

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s output_file\n", argv[0]);
        return 1;
    }
    int pipefd[2];
    pipe(pipefd);
    int fd;
    pid_t pid1=fork();
    if(pid1==0){
        close(pipefd[0]);
        dup2(pipefd[1],STDOUT_FILENO);
        execlp("cat","cat",argv[1],NULL);
        close(pipefd[1]);
        exit(1);
    }
    pid_t pid2=fork();
    if (pid2==0){
        close(pipefd[1]);
        int n;
        dup2(pipefd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        close(pipefd[0]);
        exit(1);
    }
    close(pipefd[1]);
    close(pipefd[0]);
    //while (wait(NULL) > 0);
    wait(NULL);
    wait(NULL);
    
    return 0;
}