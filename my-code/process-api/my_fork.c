#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * fork api的作用是拷贝当前父进程的所有状态到一个子进程
 * 但是fork的返回值和父进程不一样:
 *  - 父进程中返回子进程的pid
 *  - 子进程中返回0
 */

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