#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
// Race Condition Occur
int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	if((child = fork()) == 0) // Program counter of both process indicates here.
	{
		int i;
		for(i=1; i<10001; i++)
		{
			printf("C : %d\n",i);
			fflush(stdout);
		}
		exit(1);	
	}
	else if(child == -1)
	{
		perror("fork");
		return 0;
	}
	else
	{
		int j;
		for(j=1; j<10001; j++)
		{
			printf("P : %d\n",j);
			fflush(stdout);
		}
		wait(&status);
		printf("Finished ! %d \n",WEXITSTATUS(status));
	}
	return 0;
}


