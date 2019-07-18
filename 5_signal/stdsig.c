// stdsig.c
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

void waitchild(int sig) {
  int status;
  pid_t pid;
/*
	waitpid第一个参数> 0，表示 waitpid 只等待子进程 pid。
	waitpid第一个参数=  0，表示 waitpid 等待和当前调用 waitpid 一个组的所有子进程。
	waitpid第一个参数= -1，表示等待所有子进程。
	waitpid第一个参数< -1，表示等等组 id=|pid|id=|pid| （绝对值 pid）的所有子进程。
	这里 waitpid 接收所有子进程状态，并且没有打开 WNOHANG 开关
*/
  while ((pid = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0) {
    if (WIFEXITED(status)) {
      printf("child %d exited! return code = %d\n\n", pid, WEXITSTATUS(status));
    }   
    else if (WIFSIGNALED(status)) {
      printf("child %d terminated by signal %d\n\n", pid, WTERMSIG(status));
    }   
    else if (WIFSTOPPED(status)) {
      printf("child %d stopped by signal %d\n\n", pid, WSTOPSIG(status));
    }   
    else if (WIFCONTINUED(status)) {
      printf("child %d continued\n\n", pid);
    }   
  }
  sleep(1);
}


void child(int n) {
  if (n == 9) *((int*)0) = 0;
  exit(n + 1); 
}
int main() {
  printf("I'm %d\n", getpid());

  if (SIG_ERR == signal(SIGCHLD, waitchild)) {
    perror("signal SIGSTOP");
  }


  int n = 10; 
  pid_t pid;

  while(n--) {
    pid = fork();
    if (pid == 0) {
      child(n);
    }   
    else if (pid == -1) {
      perror("fork");
    }   
  }

  while(1) {
    write(STDOUT_FILENO, ".", 1); 
    sleep(10);
  }   
  return 0;
}