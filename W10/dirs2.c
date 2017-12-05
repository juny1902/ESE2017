// Handmade ls Method.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	DIR *list;
	struct stat s_buf;
	if(argc == 2)
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
		stat(curd->d_name,&s_buf);
		printf("%s ",curd->d_name);
		switch(s_buf.st_mode & S_IFMT)
		{
			case S_IFREG: printf("\t| Regular File |"); break;
			case S_IFDIR: printf("\t| Directory |"); break;
			case S_IFLNK: printf("\t| Symbolic Link |"); break;
			default: printf("\t| Unknown |"); break;
		}
		printf("\n");
	}
	printf("\n");	
	closedir(list);
	return 0;
}


