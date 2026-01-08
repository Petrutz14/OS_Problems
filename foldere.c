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



void copy_file(const char* sursa,const char* destinatie){
  int fd1=open(sursa,O_RDONLY);
  int fd2=open(destinatie,O_WRONLY|O_CREAT|O_TRUNC,0777);
  char buf[SIZE];
  int n;
  while((n=read(fd1,buf,SIZE))>0){
    write(fd2,buf,n);
  }
  close(fd1);close(fd2);
}


void copy_folder(char* sursa,char* destinatie){
  mkdir(destinatie,0777);

  DIR* dir=opendir(sursa);
  struct dirent* entry;

  while(entry=readdir(dir)){
    if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
      continue;
    }
    char sursa_path[1024];
    char destinatie_path[1024];

    snprintf(sursa_path,sizeof(sursa_path),"%s/%s",sursa,entry->d_name);
    snprintf(destinatie_path,sizeof(destinatie_path),"%s/%s",destinatie,entry->d_name);

    if(entry->d_type=DT_REG){
      copy_file(sursa_path,destinatie_path);
    }
    else{
      copy_folder(sursa_path,destinatie_path);
    }
  }
  closedir(dir);


}

int main(int argc,char**argv){

    struct stat stat1;
    struct stat stat2;
    stat(argv[1],&stat1);
    stat(argv[2],&stat2);

    if(S_ISREG(stat1.st_mode) && S_ISREG(stat2.st_mode)){
        copy_file(argv[1],argv[2]);

    }
    else if(S_ISREG(stat1.st_mode) && S_ISDIR(stat2.st_mode)){
      char destinatie[1024];
      snprintf(destinatie,sizeof(destinatie),"%s/%s",argv[2],argv[1]);
      copy_file(argv[1],destinatie);

    }
    else{
      copy_folder(argv[1],argv[2]);

    }




    return 0;
}