#include <stdio.h>
#include <unistd.h>

int main(){
    printf("hello sig from %d\n", getpid());
    while(1){
        write(STDOUT_FILENO,".",1);
        sleep(1);
    }
    return 0;
}
