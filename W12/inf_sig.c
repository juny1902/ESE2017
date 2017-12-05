#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
void ouch()
{
	printf("Ouch !! \n");
}
void argh()
{
	printf("Argh !! \n");
}
void term()
{
	printf("Good Night.\n");
	exit(0);
}
int main()
{	
	struct sigaction act, act2, act3;

	sigemptyset(&act.sa_mask); // Unblock All
	act.sa_handler = ouch;
	act.sa_flags = 0;

	sigemptyset(&act2.sa_mask); // Unblock All
	act2.sa_handler = argh;
	act2.sa_flags = 0;

	sigemptyset(&act3.sa_mask);
	act3.sa_handler = term;
	act3.sa_flags = 0;

	if(sigaction(SIGINT,&act,NULL) == -1)
	{
		perror("Act");
		return 0;
	}
	if(sigaction(SIGQUIT,&act2,NULL) == -1)
	{
		perror("Act2");
		return 0;
	}
	if(sigaction(SIGTERM,&act3,NULL) == -1)
	{
		perror("Act3");
		return 0;
	}
	while(1)
	{
		printf("The only way to get out here is \'Ctrl+Z\'\n");
		sleep(1);
	}

	return 0;
}
