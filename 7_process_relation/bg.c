// bg.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
  if (sig == SIGTTIN) {
    printf("hello SIGTTIN\n");
    sleep(5);
  }
  if (sig == SIGTTOU) {
    printf("hello SIGTTOU\n");
    exit(0);
  }
}

int main(int argc, char* argv[]) {
  int len;
  char buf[64];
  int n=5;
  //int srcfd = open(argv[1],O_RDONLY);
  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_flags &= ~SA_RESTART;

  if (sigaction(SIGTTIN, &act, NULL) < 0) {
      perror("signal SIGTTIN");
  }
  if (sigaction(SIGTTOU, &act, NULL) < 0) {
      perror("signal SIGTTOU");
  }

//  while(1){

	while(len = read(STDIN_FILENO, buf, 64)){
    write(STDOUT_FILENO, buf, len);
   /* if (len > 0) {
      write(STDOUT_FILENO, buf, len);
      write(STDOUT_FILENO, buf, len);
      write(STDOUT_FILENO, buf, len);
    }
    else {
      perror("read");
    }*/
    sleep(1);
//    n--;
  }
  return 0;
}
