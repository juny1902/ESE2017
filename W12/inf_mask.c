#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
struct two_double{
	double a;
	double b;
}data;
void sig_h()
{
	printf("%f, %f\n",data.a,data.b);
	alarm(1);
}
int main()
{	
	struct sigaction act;
	static struct two_double zeros={0.0,0.0}, ones={1.0, 1.0};

	sigemptyset(&act.sa_mask); // Unblock All
	act.sa_handler = sig_h;
	act.sa_flags = 0;

	if(sigaction(SIGALRM,&act,NULL) == -1)
	{
		perror("Act");
		return 0;
	}
	data = zeros;
	alarm(1); // Alarm affects only a time.
	while(1)
	{	
		data = zeros;
// The signal may affect during the structure 'data' is being writed from 'zeros' and 'ones'
// ->> NOT ATOMIC !!
		data = ones;
	}

	return 0;
}
