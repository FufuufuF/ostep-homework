/*
编写一个程序，创建两个子进程，并使用 pipe()系统调用，将一个子进程的标准输
出连接到另一个子进程的标准输入。
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* args[]) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // 第一个子进程：写入数据到管道
        close(pipefd[0]); // 关闭读端
        printf("child process 1(pid: %d) says: hello\n", (int)getpid());
        write(pipefd[1], "hello from child 1", 20); // 向管道写入数据
        close(pipefd[1]); // 关闭写端
        exit(0);
    }

    int rc2 = fork();
    if (rc2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc2 == 0) {
        // 第二个子进程：从管道读取数据
        close(pipefd[1]); // 关闭写端
        char buffer[21];
        read(pipefd[0], buffer, 20); // 从管道读取数据
        buffer[20] = '\0'; // 确保字符串以 null 结尾
        printf("child process 2(pid: %d) received: %s\n", (int)getpid(), buffer);
        close(pipefd[0]); // 关闭读端
        exit(0);
    }

    // 父进程：关闭管道两端，等待子进程完成
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL); // 等待第一个子进程完成
    wait(NULL); // 等待第二个子进程完成

    return 0;
}