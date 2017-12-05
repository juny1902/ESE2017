// Unix Standard Library
#include <unistd.h>
// System Call header
#include <sys/types.h>
#include <sys/wait.h>
// C Standard Library
#include <stdio.h>
#include <stdlib.h>
int my_system(char *command) // Implementing system(3) func.
{
	pid_t sys; // Var for PID
	int status; // Var for status
	if((sys=fork()) == 0) // Clone this process
	{
		// And change the code area into 'bash' and arguments.
		execl("/bin/bash","/bin/bash","-c",command,NULL);
	}
	else
	{
		wait(&status); // Wait for a child process to return a code.
		return status; // Return status code.
	}
}
int main(int argc, char *argv[])
{
	int status; // VAr for status
	status = my_system("ls -l | wc"); // My_system will return a exit code
	printf("Exit code : %d\n", WEXITSTATUS(status)); // Print the exit code
	return 0;
}
