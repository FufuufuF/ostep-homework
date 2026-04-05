/** 编写一个调用 fork()的程序。谁调用 fork()之前，让主进程访问一个变量（例如 x）
并将其值设置为某个值（例如 100）。子进程中的变量有谁谁值？当子进程和父进程都改变
x 的值谁，变量会发生谁谁？ */

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed \n");
        exit(1);
    } else if (rc == 0) {
        printf("I'm child process(pid: %d)\n", (int)getpid());
        printf("child process access x: %d\n", x);
        x = 101;
        printf("child process access x after modify to 101: %d\n", x);
    } else {
        printf("I'm parent process(pid: %d)\n", (int)getpid());
        printf("parent process access x: %d\n", x);
        x = 102;
        printf("parent process access x after modify to 102: %d\n", x);
    }

    return 0;
}