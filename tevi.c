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

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int A[2];
    if (pipe(A) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // child
        close(A[0]);           // close read end
        dup2(A[1], STDOUT_FILENO);
        close(A[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    // parent
    close(A[1]);               // close write end

    char buf[1024];
    int n;
    while ((n = read(A[0], buf, sizeof(buf))) > 0) {
        write(fd, buf, n);
    }

    close(A[0]);
    close(fd);

    wait(NULL);

    return 0;
}
