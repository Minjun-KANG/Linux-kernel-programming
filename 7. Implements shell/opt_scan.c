#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "Myheader.h"

//option scan
int opt_scan(char *argv[], const char *option)
{
	int count = 0;

	while(*argv != '\0')
	{
		// if exist option?
		if(!strcmp(argv[count], option))
		{
			return 1;
		}

		argv++;
	}

	return 0;
}

//Change Directory
void My_cd(int argc, char *argv[])
{
	char *path;

	// if exist parameter set argv[1]
	if(argc > 1)
	{
		path = argv[1];
	}
	
	// If no parameter, set Home directory 
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		// no env, It becomes the current directory.
		path = ".";
	}

	//change directory
	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "ERROR - cd.\n");
	}
}

//End of program 
void My_exit()
{
	exit(1);
}
void My_mkdir(int argc, char *argv[])
{
	// 
	if (argc < 2)
	{
		fprintf(stderr, "ERROR - ARGS.\n");
		return;
	}

	// 디렉토리를 생성한다.
	if (mkdir(argv[1], 0755))
	{
		fprintf(stderr, "ERROR - mkdir.\n");
	}
}
//ls
void My_ls(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *temp;
	char *path;
	int count;
	int opt_a;
	int opt_l;

	// no parameter, set cur dir
	if(argc < 2)
	{
		path = ".";
	}
	
	// exist parameter, set argv[1] dir
	else
	{
		path = argv[1];
	}

	// open dir
	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "ERROR - open");
		return;
	}

	// option scanf -a or -l
	opt_a = opt_scan(argv, "-a");
	opt_l = opt_scan(argv, "-l");

	count = 0;

	//scanf file or dir
	while((temp = readdir(dp)) != NULL)
	{
		// not -a, Do not show hidden files.
		if(!opt_a)
		{
			if(temp->d_name[0] == '.')
			{
				continue;
			}
		}
		
		//print
		printf("%s\t", temp->d_name);

		// case : -l 
		if(opt_l)
		{
			printf("\n");
		}
		
		// Prints three per line.
		else
		{
			if(count > 3)
			{
				printf("\n");
				count = 0;
			}
			else
			{
				count++;
			}
		}
	}

	// close dir
	closedir(dp);
	printf("\n");
}

