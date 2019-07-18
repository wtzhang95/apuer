// wipeoutzombie2.c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
  printf("before fork\n");

  // 生成 5 个子进程
  pid_t pid, n = 5;
  while(n--) {
    pid = fork();
    if (pid == 0) break;
    else if (pid < 0) {
      perror("fork");
      return 1;
    }   
  }

  // 每个子进程一生出来就睡眠 4*n + 1 秒，不要问为什么是 4*n + 1，这只是我随便写的，只想保证每个子进程睡眠时间不一样。
  if (pid == 0) {
    sleep(4*n + 1); 
    printf("hello, I'm child [ %d ]; my father is [ %d ]\n\n", getpid(), getppid());

    // 这一句，我故意让这个子进程 core 掉，主要用来看效果。
    if (4*n + 1 == 5) *((int*)0) = 0;

    // 子进程再退出的时候，返回它的睡眠时间
    return 4*n + 1;
  }


  int status = 0;
  while(1) {
    // 这里 waitpid 接收所有子进程状态，但是没有打开 WNOHANG 开关，同学们可以自行加上看看效果
    pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);

    // 出错情况，这种一般是子进程全部结束了。
    if (pid == -1) {
      perror("wait");
      sleep(5);
      printf("I'm father [ %d ]; I have wiped out all zombies\n\n", getpid());
      return 1;
    }   
    // 这种只会在 WNOHANG 开关打开的情况下出现
    else if (pid == 0) {
      printf("Hello, I'm father; I'm waiting child\n\n");
    } 
    // 这种是只要有一个子进程状态发生改变就会进来。注意 4 类情况，比较多。  
    else {

      if (WIFEXITED(status)) {
        printf("child [ %d ] <exited> with code [ %d ]\n\n", pid, WEXITSTATUS(status));
      }   
      else if (WIFSIGNALED(status)) {
        printf("child [ %d ] <terminated> abnormally, signal [ %d ]\n\n", pid, WTERMSIG(status));
#ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
          printf("<core file generated> in child [ %d ]\n\n", pid);
        }   
#endif
      }   
      else if (WIFSTOPPED(status)) {
        printf("child [ %d ] <stopped>, signal [ %d ]\n\n", pid, WSTOPSIG(status));
      }   
      else if (WIFCONTINUED(status)) {
        printf("child [ %d ] <continued>\n\n", pid);
      }   
    }   

  }
  return 0;
}