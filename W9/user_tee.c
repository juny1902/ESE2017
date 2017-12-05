// ESE 201503120 - Week 9 Homework.
// - Making an immitation of 'tee' -

// Header for linux system calls
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Header for C libraries
#include <stdio.h>
#include <stdlib.h>

// Define buffer for reading file
#define SZ_BUF 1024

int main(int argc, char* argv[])
{
	if(argc != 2) // Argument number check
	{	
		perror("Invalid Argument !!\n"); 
		exit(0);
	}
	
	// Declear file discriptor and make a new file for writing with 0666 permission.
	int fd = open(argv[1], O_WRONLY | O_CREAT , 0666);

	if (fd == -1) // If declearation of file discriptor failed...
	{
		fprintf(stderr,"Create \"%s\" Failure\n",argv[2]);
	}
	
	int nb; // Declear a variable for number of writing buffer 
	char buf[SZ_BUF]; // Declear buffer for character of SZ_BUF
	while(nb = read(0,buf,SZ_BUF)) // While actual reading ... (nb != -1)
	{
		write(fd,buf,nb); // Write on a file
		write(1,buf,nb); // Write on standard output
	}
	close(fd); // File closure.
	return 0;
}

