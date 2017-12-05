#include <sys/types.h>
#include <unistd.h>

#include <time.h>

#include <stdio.h>
void func_a();
void func_b();
void func_c();

void func_a()
{
	sleep(1);
	printf("[%d]I'm func A\n",getpid());
	func_b();
}
void func_b()
{
	sleep(1);
	printf("[%d]I'm func B\n",getpid());
	func_c();
}
void func_c()
{
	sleep(1);
	printf("[%d]I'm func C\n",getpid());
	func_a();
}
int main()
{	
	func_a();
	sleep(1);
	return 0;
}
