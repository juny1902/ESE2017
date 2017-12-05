#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
int t = 0; // For elapsed time
struct two_double{
	double a;
	double b;
}data;
void sig_h() // Signal Handler
{
	t++;
	printf("%f, %f [Elapsed time : %d]\n",data.a,data.b,t);
	alarm(1); // Set the alram again.
}
int main()
{	
	struct sigaction act;
	static struct two_double zeros={0.0,0.0}, ones={1.0, 1.0}; 
	// (0,0) or (1,1)
	sigemptyset(&act.sa_mask); // Unblock All
	act.sa_handler = sig_h; // Set the handler
	act.sa_flags = 0;

	if(sigaction(SIGALRM,&act,NULL) == -1) // If the signal failed ...
	{
		perror("Act");
		return 0;
	}
	data = zeros; // Initial value of data is (0,0)
	alarm(1); // This alarm affects only a time.
	while(1)
	{
		// Block the signal while the data (0,0) is being fetched.
		sigprocmask(SIG_BLOCK,&act.sa_mask,NULL);
		data = zeros;	
		sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL);

		// Block the signal while the data (1,1) is being fetched.
		sigprocmask(SIG_BLOCK,&act.sa_mask,NULL);
		data = ones;
 		sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL);		
	}

	return 0;
}
