#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("Hello, World! %d\n", (int)getpid());
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Hello from the child process! %d\n", (int)getpid());
    } else {
        printf("Hello from the parent process! %d\n", (int)getpid());
    }

    return 0;
}