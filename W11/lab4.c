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
		printf("C : Hi, I'm child process.\n");
		execl("/bin/ps","ps","-ef",NULL);
		printf("C : This will be ignored.\n"); // Because 'execl' makes him different program
		exit(123); // This would not be effective.
	}
	else if(child == -1)
	{
		perror("fork");
		return 0;
	}
	else
	{
		printf("P : My baby, Would you call ps -ef ?\n");
		wait(&status); // status code of 'ps'
		printf("P : Finished ! %d\n",WEXITSTATUS(status));
	}
	return 0;
}


