#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
// 부모 프로세스와 자식 프로세스 예제
int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	if((child = fork()) == 0) // Program counter of both process indicates here.
	// child == 0 -> Child process
	{
		printf("B[%ld] : I'm a baby !, Morning Mom[%ld] !\n",(long)getpid(),(long)getppid());
		exit(123);
	}
	else if(child == -1)
	{
		perror("fork");
		return 0;
	}
	else // child != 0 -> Parent Process
	{
		printf("P[%ld] : Where's my baby?\n",(long)getpid());
		wait(&status); // wait for child process
		printf("Status code is %d ! \n",WEXITSTATUS(status));
		printf("P[%ld] : Welcome back my baby !\n",(long)getpid());
	}
	return 0;
}


