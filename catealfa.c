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

int alpha(char c){
  if(c>='A' && c<='z'){
    return 1;
  }
  return 0;
}

int main(int argc,char**argv) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1=fork();
    if(pid1==0){
      close(pipefd[0]);
      dup2(pipefd[1],STDOUT_FILENO);
      execlp("cat","cat",argv[1],NULL);
      close(pipefd[1]);
      exit(1);
    }

    pid_t pid2=fork();
    if(pid2==0){
      int n,total=0;
      char c;
      close(pipefd[1]);
      while((n=read(pipefd[0],&c,1))>0){
        if(alpha(c)){
          total++;
        }
      }
      printf("Cate alfa:%d\n",total);
      close(pipefd[0]);
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    while((wait(NULL))>0);

    return 0;
}