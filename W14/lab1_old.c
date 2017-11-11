#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 8
volatile int cnt = 0;
void *worker(void *ptr)
{
		int i;
		for(i=0; i<50000; i++)
		{
				cnt++;
		}
		pthread_exit(NULL);
}
int main()
{
		int i;
		pthread_t w_thread[NUM_THREADS];
		for(i=0;i<NUM_THREADS;i++)
		{
				pthread_create(&w_thread[i],NULL,worker,NULL);
		}
		for(i=0;i<NUM_THREADS;i++)
		{
				pthread_join(w_thread[i],NULL);
		}
		printf("Total count is %d.\n",cnt);
		return 0;
}
