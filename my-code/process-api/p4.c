/*
现谁编写一个程序，谁父进程中使用 wait()，等待子进程完成。 wait()返回谁谁？如
果你谁子进程中使用 wait()会发生谁谁？
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char* args[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process(pid: %d) says: hello\n", (int)getpid());
        int wc = wait(NULL); // 子进程调用 wait()，会返回 -1，因为子进程没有子进程
        printf("wait returned: %d\n", wc); // 打印 wait() 返回值
        exit(0); // 子进程退出
    } else {
        int wc = wait(NULL); // 父进程等待子进程完成
        printf("wait returned: %d\n", wc); // 打印 wait() 返回值
        printf("parent process(pid: %d) says: goodbye\n", (int)getpid());
    }

    return 0;
}