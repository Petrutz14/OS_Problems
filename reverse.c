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
    if(argc < 2) {
        printf("Usage: ./a.out <file1> ... <fileN>\n");
        exit(1);
    }

    for(int i = 1; i < argc; i++) {
        pid_t pid = fork();

        if(pid == 0) {
            int fd_out = open("reverse.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            int fd_in  = open(argv[i], O_RDONLY);

            if(fd_in < 0) { perror("open input"); exit(1); }
            if(fd_out < 0) { perror("open output"); exit(1); }

            char c;
            off_t pos = lseek(fd_in, 0, SEEK_END);   // ⭐ correct file
           
            while(pos > 0) {
                pos = lseek(fd_in, -1, SEEK_CUR);    // go back one byte
                read(fd_in, &c, 1);                  // read it
                write(fd_out, &c, 1);                // write it
                lseek(fd_in, -1, SEEK_CUR);          // back again to continue
            }

            close(fd_in);
            close(fd_out);
            exit(0);
        }
    }

    while(wait(NULL) > 0);
    return 0;
}

