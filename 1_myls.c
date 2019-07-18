#include <dirent.h>
//#include <sys/types.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <myerr.h>
#include <apue.h>

int main(int argc, char *argv[])
{
	DIR *dp = NULL;
	//struct dirent *dirp = NULL;
	struct dirent *dirp;

	if(argc != 2)
        err_quit("a single argument (the directory name) is required");
	if((dp = opendir(argv[1])) == NULL)
	    err_sys("can't open %s", argv[1]);
	while((dirp = readdir(dp)) != NULL)
	    printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
