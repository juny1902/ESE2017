#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int x=1;
void *func(void *data)
{
		x = x+1;
		pthread_exit((void *)42);
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
		pthread_join(mythread,(void **)&i);
		printf("%d\n",i);
}
