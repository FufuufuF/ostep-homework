#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t child_exited = 0;
void sigchld_handler(int signum) {
    child_exited = 1;
}

int main(int argc, char* args[]) {
    signal(SIGUSR1, sigchld_handler); // 注册 SIGUSR1 信号处理函数
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   
        printf("child process(pid: %d) says: hello\n", (int)getpid());
        kill(getppid(), SIGUSR1); // 向父进程发送 SIGUSR1 信号
        exit(0); // 子进程退出
    } else {
        while (!child_exited) {
            pause(); // 等待信号
        }
        printf("parent process(pid: %d) says: goodbye\n", (int)getpid());
    }

    return 1;
}