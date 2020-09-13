#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Myheader.h"

//excute cmd
int exe_cmd(int argc, char *argv[], int a_src_fd, char *a_src_filename, 
	int a_dst_fd, char *a_dst_filename,int append, int backgnd)
{
	int pid;

	// don't have parameter and Mycmd ERROR
	if (argc == 0 || Mycmd(argc, argv, a_src_fd, a_dst_fd))
	{
		return 0;
	}

	// fork
	pid = fork();

	switch (pid)
	{
		// ERROR case, 
		case ERROR : 
			fprintf(stderr, "ERROR - don't create.\n");
			return 0;

		// child
		case 0 :     
			std_DC(a_src_fd, a_src_filename, a_dst_fd, a_dst_filename, append, backgnd);
			execvp(argv[0], argv);
			fprintf(stderr, "ERROR - exec : %s\n", argv[0]);
			exit(0);

		// parents
		default :
			// close src 
			if(a_src_fd > 0 && close(a_src_fd) == ERROR)
			{
				print_error("close a_src_fd");
			}

			// close dst
			if(a_dst_fd > 1 && close(a_dst_fd) == ERROR)
			{
				print_error("close a_dst_fd");
			}

			// case - background 
			if(backgnd)
			{
				printf("%d\n", pid);
			}
			
			return pid;
	}
}
