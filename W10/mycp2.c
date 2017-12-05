// Headers for Linux System Calls
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
// Headers for C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// For Char array buffer
#define SZ_BUF 1024

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		perror("Invalid Argument "); // On Argument Error
		exit(0);
	}
	int src_fd, dest_fd; // Declare File descriptors
	src_fd = open(argv[1],O_RDONLY); // Source File
	if(src_fd == -1)
	{
		perror("File Open "); // On opening error
		exit(0);
	}
	dest_fd = open(argv[2], O_WRONLY | O_CREAT,0666); // Destination File
	if(dest_fd == -1)
	{
		perror("File Create "); // On create error
		exit(0);
	}
	int nb;	// An integer variable to count what we need.
	char buf[SZ_BUF]; // A char array to read a file.
	while(nb = read(src_fd,buf,SZ_BUF)) // While reading into buffer...
	{
		write(dest_fd,buf, nb); // Write what we read.
	}

	struct stat src_s_buf; // A struct for get stat information
	fstat(src_fd,&src_s_buf); // Get stat of src file to src_buf
	fchmod(dest_fd,src_s_buf.st_mode); // Set mode of dest file to mode of src file
	printf("Copy Successful !\n");	
	// Don't forget to close files.
	close(src_fd);
	close(dest_fd);
}

