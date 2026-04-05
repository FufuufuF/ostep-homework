/*
使用 fork()编写另一个程序。子进程应打印“hello”，父进程应打印“goodbye”。你
应该尝试我保子进程始终先打印。你能否我谁父进程调用 wait()而做到这一点呢？
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* args[]) {
    int pipefd[2];
    int flag = pipe(pipefd);
    if (flag < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process(pid: %d) says: hello\n", (int)getpid());
        close(pipefd[0]); // 关闭读端
        write(pipefd[1], "done", 4); // 向管道写入数据，通知父进程
        close(pipefd[1]); // 关闭写端
    } else {
        close(pipefd[1]); // 关闭写端
        char buffer[5];
        read(pipefd[0], buffer, 4); // 从管道读取数据，等待子进程完成
        buffer[4] = '\0'; // 确保字符串以 null 结尾
        printf("parent process(pid: %d) says: goodbye\n", (int)getpid());
        close(pipefd[0]); // 关闭读端
    }
}