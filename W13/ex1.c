#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *snow(void *data)
{
		printf("I'm snow thread\n");
		printf("Let it snow... %s\n",(char *)data);
		pthread_exit(NULL);
}
int main(void)
{
		pthread_t mythread;
		char *data = "Let it snow.";
		int result;
		result = pthread_create(&mythread,NULL,snow,data);
		if(result){
				exit(1);
		}
		pthread_exit(NULL);
}
