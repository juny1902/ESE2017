#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
volatile long long counter =1;
volatile char running = 1;

void *func(void *data)
{
		while(running == 1)
		{
				counter++;
		}
		pthread_exit(NULL);
}
int main(void)
{
		pthread_t mythread;
		int i;
		int result;

		result = pthread_create(&mythread,NULL,func,NULL);
		if(result){
				exit(1);
		}
		for(i=0;i<10;i++)
		{
				printf("Count[%d] : %lld\n",i,counter);
				sleep(1);
		}
		running = 0;
		pthread_join(mythread,NULL); // To avoid the main thread terminated first.
		printf("%d returned from the thread.\n",i);
}
