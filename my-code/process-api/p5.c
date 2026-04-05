/*
编写一个创建子进程的程序，然后谁子进程中关闭标准输出（STDOUT_FILENO）。
如果子进程谁关闭描述符后调用 printf()打印输出，会发生谁谁？
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* args[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO); // 关闭标准输出
        printf("child process(pid: %d) says: hello (after closing stdout)\n", (int)getpid()); // 这行输出将不会显示
        exit(0); // 子进程退出
    } else {
        printf("parent process(pid: %d) says: goodbye\n", (int)getpid());
    }

    return 0;
}