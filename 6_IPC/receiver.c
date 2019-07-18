// recver.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 信号处理函数，从文件中读取数据，并转换成大写打印到屏幕
void handler(int sig) {
  char buf[64];
  int i;
  int fd = open("tmp", O_RDONLY);
  if (fd < 0) {
    perror("open");
    return;
  }

  int n = 0;

  if ((n = read(fd, buf, 64)) < 0) {
    perror("read");
    close(fd);
    return;
  }
  close(fd);
  unlink("tmp"); // 读取完成后将文件删除
  for (i = 0; i < n; ++i)
    putchar(toupper(buf[i])); // 将数据转换成大写并打印到屏幕。toupper 是 C 库函数，声明于 ctype.h 文件中

  if (*buf == 'q') exit(0); // 如果收到的数据以 q 开头就退出
}

int main() {
  printf("I'm %d\n", getpid());

  // 注册 SIGUSR1 信号
  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  if (sigaction(SIGUSR1, &act, NULL) < 0) {
    perror("sigaction");
    return 1;
  }

  // main 函数进入休眠
  while(1) pause();
}