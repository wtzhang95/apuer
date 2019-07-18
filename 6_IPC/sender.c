// sender.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {
  // 要想发送信号，必须知道另一个进程的进程 id 号，所以这里通过参数将进程 id 传进来
  if (argc < 2) {
    printf("usage: %s <pid>", argv[0]);
    return 1;
  }

  pid_t pid = atoi(argv[1]);
  char buf[64] = { 0 };
  int n = 0;
  while(1) {
    // 从标准输入中读取数据，并写到文件中
    if ((n = read(STDIN_FILENO, buf, 64)) > 0) {
      int fd = open("tmp", O_WRONLY | O_CREAT | O_EXCL, 0664);
      if (fd < 0) {
        perror("open");
        continue;
      }   
      write(fd, buf, n); 
      // 写完数据后，向接收进程发送 SIGUSR1 信号
      close(fd);
      if (kill(pid, SIGUSR1) < 0) {
        perror("kill");
      }   
      // 如果用户输入 q，就关闭程序
      if (*buf == 'q') return 0;
    }   
  }
  return 0;
}