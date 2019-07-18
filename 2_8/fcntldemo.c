// 文件名：fcntldemo.c
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("USAGE: fcntldemo [fd]\n");
    exit(1);
  }

  int fd = atoi(argv[1]);

  int flags = fcntl(fd, F_GETFL);

  if (flags == -1) {
    perror("fcntl");
    exit(1);
  }

  if (flags & O_RDONLY) {
    printf("O_RDONLY\n");
  }
  if (flags & O_WRONLY) {
    printf("O_WRONLY\n");
  }
  if (flags & O_RDWR) {
    printf("O_RDWR\n");
  }
  if (flags & O_NONBLOCK) {
    printf("O_NONBLOCK\n");
  }
  if (flags & O_APPEND) {
    printf("O_APPEND\n");
  }       

  return 0;   

}       