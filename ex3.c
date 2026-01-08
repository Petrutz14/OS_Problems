


void calc_size(char* folder,int total){
    DIR* dir;
    struct dirent* entry;
    struct stat tata;
    lstat(folder,&tata);
    if(S_ISREG(tata.st_mode)){
        printf("%ld\n",tata.st_size);
        exit(1);
    }

    dir=opendir(folder);
    while((entry=readdir(dir))!=NULL){
        if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0){
            continue;
        }
        char path[1024];
        snprintf(path,sizeof(path),"%s/%s",folder,entry->d_name);
        if(entry->d_type==DT_REG){
            struct stat stater;
            lstat(path,&stater);
            total+=stater.st_size;
        }
        if(entry->d_type==DT_DIR){
            pid_t pid=fork();
            if(pid==0){
                calc_size(path,total);
                exit(1);
            }
        }
    }
    while((wait(NULL))>0);
    printf("%d\n",total);



}


int main(int argc,char **argv){

    int total=0;
    calc_size(argv[1],total);

    return 0;
}