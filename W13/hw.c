#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 4
#define START_VAL (long long)0
#define END_VAL (long long)1000000000
volatile long long sum[NUM_THREAD] = {0, };
struct pth_info{
		int pid;
		long long start;
		long long end;
};

void *para(void *val)
{
		int i;
		struct pth_info *cp_pth;
		cp_pth = (struct pth_info *)val;

		printf("[%d] %lld 부터 %lld 까지 더합니다.\n",cp_pth->pid,cp_pth->start+1,cp_pth->end);
		for(i=cp_pth->start;i<cp_pth->end;i++)
		{
				sum[cp_pth->pid] = sum[cp_pth->pid]+i; 
		}
		return (void *)sum[cp_pth->pid];
}
int main(void)
{
		int i;
		long long div = (END_VAL-START_VAL)/NUM_THREAD;
		long long total = 0;
		printf("%lld 부터 %lld 까지의 값을\n",START_VAL,END_VAL);
		printf("%lld 씩 %d 개의 스레드로 나눠 작업합니다.\n",div,NUM_THREAD);
		struct pth_info p_info[NUM_THREAD];
		pthread_t pid[NUM_THREAD];
		
		for(i=0; i<NUM_THREAD; i++)
		{
				p_info[i].pid = i;
				p_info[i].start =div*i;
				p_info[i].end = div*(i+1);
				pthread_create(&pid[i],NULL,para,(void *)&p_info[i]);
		}
		for(i=0; i<NUM_THREAD; i++)
		{
				total = total + sum[i];
				pthread_join(pid[i],(void **)&sum[i]);
				printf("[%i] 합 : %lld\n",i,sum[i]);
		}
		printf("[총합]\t %lld\n",total);
}
