#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4
#define WORK_PER_THREAD 100
struct thread_args{
		int myid;
		long long start;
		long long end;
};

volatile long long sum[NUM_THREADS];

void *func(void *data)
{
		struct thread_args *cp_data;
		cp_data = (struct thread_args *)data;
		return (void *)(cp_data->start + cp_data->end);
}

int main(void)
{
		pthread_t mythread[NUM_THREADS];
		struct thread_args range[NUM_THREADS];
		
		int i;
		for(i=0; i<NUM_THREADS; i++)
		{
				range[i].myid=i;
				range[i].start=i*WORK_PER_THREAD+1;
				range[i].end=(i+1)*WORK_PER_THREAD+1;

				pthread_create(&mythread[i],NULL,func,(void *)&range[i]);
				// 구조체의 '주소'를 void * 로 캐스팅 (주소만 넘겨도 ok)
		}
		for(i=0; i<NUM_THREADS;i++)
		{
				pthread_join(mythread[i],(void **)&sum[i]);
				printf("%ith sum: %lld\n",i,sum[i]);
		}
}
