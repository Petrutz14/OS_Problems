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

void afisare(char *folder){
    //Declaram fisiery
    DIR *dir;

    //Declaram formularu magic
    struct dirent *entry;

    //Deschidem fisieru
    dir=opendir(folder);
    printf("%s:\n\n",folder);
    //Parcugem prin fisier
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 ){
            continue;
        }
        char path[1024];
        snprintf(path,sizeof(path),"%s/%s",folder,entry->d_name);
        printf("%s\n",entry->d_name);

        if(entry->d_type==DT_DIR){
            afisare(path);
        }


        //*------------------------------
        


    }



}


int main(int argc,char **argv){

    afisare(argv[1]);



    return 0;
}