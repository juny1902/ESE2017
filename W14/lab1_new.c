#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 8
volatile int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *worker(void *ptr)
{
		int i;
		int cnt_t=0;
		for(i=0; i<50000; i++)
		{
				pthread_mutex_lock(&mutex);
				cnt_t++;
				pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_lock(&mutex);
		cnt = cnt + cnt_t;
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
}
int main()
{
		int i;
		pthread_t w_thread[NUM_THREADS];
		for(i=0;i<NUM_THREADS;i++)
		{
				if(pthread_create(&w_thread[i],NULL,worker,NULL) == -1)
				{
						perror("Thread create");
						break;
				}
		}
		for(i=0;i<NUM_THREADS;i++)
		{
				if(pthread_join(w_thread[i],NULL) == -1)
				{
						perror("Thread join");
						break;
				}
		}
		printf("Total count is %d.\n",cnt);
		return 0;
}
