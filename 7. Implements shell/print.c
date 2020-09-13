#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h> //wait
#include "Myheader.h"

//ERROR Duplication
void Dup_error(char *m_error)
{
	fprintf(stderr, "Error: %s\n", m_error);
	exit(1);
}

//error_print
void print_error(char *m_error)
{
	fprintf(stderr, "[%d] %s", errno, m_error);
	exit(1);
}


//parents wait for child 
void wating(int pid)
{
	int wpid, status;

	// process wait
	while ((wpid = wait(&status)) != pid && wpid != ERROR);
}

//shell print
void print_shell()
{
	char *ps;

	// read PS2 env
	if((ps = (char*)getenv("PS2")) != NULL)
	{
		//each string end by '\0' and last list is nullptr
		while(*ps != '\0')
		{
			// If'\' exists, next string
			if(*ps == '\\')
			{
				ps++;

				// print of user info
				if(*ps == 'u')
				{
					printf("%s", getenv("USER"));
				}
				
				// print of hostname
				else if(*ps == 'h')
				{
					printf("%s", getenv("HOSTNAME"));
				}
				/*
				// print of cur directory
				else if(*ps == 'w')
				{
					char line[1024];
					printf("%s", getcwd(line, 1024));
				}*/
			}
			
			// do not predefined case
			else
			{
				printf("%c", *ps);
				ps++;
			}
		}
	}
	
	// don't have env
	else
	{
		printf("Myshell >>> ");
	}
}

//processing basic operation
int Mycmd(int argc, char *argv[], int m_src_fd, int m_dst_fd)
{

	// cd
	if(!strcmp(argv[0], "cd"))
	{
		My_cd(argc, argv);
	}
	// ls
	else if(!strcmp(argv[0], "ls"))
	{
		My_ls(argc, argv);
	}
	// exit
	else if(!strcmp(argv[0], "exit"))
	{
		My_exit();
	}
	else
	{
		return 0;
	}

	if (m_src_fd != 0 || m_dst_fd != 1)
	{
		fprintf(stderr, "ERROR - pipe or ridirection.\n");
	}

	return 1;
}
