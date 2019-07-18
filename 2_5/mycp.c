#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUFFERSIZE 4096

int main(int argc, char* argv[]){
    int srcfd=open(argv[1],O_RDONLY);
    int dstfd=open(argv[2],O_CREAT| O_WRONLY, 0666);

    int len=0;
    char buffer[BUFFERSIZE] = {0};
    while((len=read(srcfd, buffer,BUFFERSIZE))>0){
        write(dstfd,buffer,len);
    }
    close(srcfd);
    close(dstfd);
    return 0;
}
