#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
// Making zombie process
int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	if((child = fork()) == 0) // Program counter of both process indicates here.
	{
		int i;
		printf("C : Hug me mom !! T_T\n"); // defunct -> Indicates zombie process
		exit(123);
	}
	else if(child == -1)
	{
		perror("fork");
		return 0;
	}
	else
	{
		printf("P : I'm sooooooo busy !!!!\n");
		while(1);
		wait(&status);
		printf("Finished ! %d \n",WEXITSTATUS(status));
	}
	return 0;
}


