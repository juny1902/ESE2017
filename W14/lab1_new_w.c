#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 8
volatile int cnt[NUM_THREADS] = {0, };
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *worker(void *ptr)
{
		int i;
		int cnt_t=0;
		for(i=0; i<100000/NUM_THREADS; i++)
		{
				pthread_mutex_lock(&mutex);
				cnt_t++;
				pthread_mutex_unlock(&mutex);
		}
		return (void *)cnt_t;
}
int main()
{
		int i;
		int cnt_sum = 0;
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
				if(pthread_join(w_thread[i],(void **)&cnt[i]) == -1)
				{
						perror("Thread join");
						break;
				}
				printf("[%d] count is %d\n",i,cnt[i]);
				cnt_sum += cnt[i];
		}
		printf("Total count is %d.\n",cnt_sum);
		return 0;
}
