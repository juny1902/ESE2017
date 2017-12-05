// Handmade ls Method.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	DIR *list;
	if(argc == 1)
	{
		list = opendir(".");
	}
	else if(argc == 2)
	{
		list = opendir(argv[1]);
	}
	else
	{
		fprintf(stderr,"Argument Error !\n");
		return 0;
	}
	if(list == NULL)
	{
		fprintf(stderr,"Invalid Directory !\n");
		return 0;
	}
	struct dirent *curd;
	while(curd = readdir(list))
	{
		printf("%s\n",curd->d_name);
	}
	printf("\n");	
	closedir(list);
	return 0;
}


