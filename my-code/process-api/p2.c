#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>   // open() 需要的头文件
#include <string.h>  // strlen() 需要的头文件

int main(int argc, char* args[]) {
    // 使用底层的 open() 系统调用，绕过 C 语言的缓冲机制
    // O_CREAT: 如果没有文件就创建; O_WRONLY: 只写; O_TRUNC: 如果有文件就清空
    // 0644 (或 S_IRUSR|S_IWUSR|...): 赋予文件读写权限
    int fd = open("./resource/tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "open file failed\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("I'm child process(pid: %d)\n", (int)getpid());
        
        // 增加到 10000 次，逼迫 CPU 在中途切换进程
        for (int i = 0; i < 10000; i++) {
            char buffer[50];
            // 先把字符串准备好
            snprintf(buffer, sizeof(buffer), "child write: %d\n", i);
            // 直接呼叫内核，立刻把这段字节写进文件！
            write(fd, buffer, strlen(buffer)); 
        }
    } else {
        printf("I'm parent process(pid: %d)\n", (int)getpid());
        
        for (int i = 0; i < 10000; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "parent write: %d\n", i);
            write(fd, buffer, strlen(buffer));
        }
    }
    
    // 关闭文件描述符
    close(fd);

    return 0;
}