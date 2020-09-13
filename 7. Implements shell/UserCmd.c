#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //pipe
#include "Myheader.h"

//User Command Analysis
TYPE UserCmd(int *a_waitpid, int a_setpipe, int *a_pipefdp)
{
	TYPE one_case, return_type;
	int argc = 0, src_fd = 0, dst_fd = 1;
	int pid, pipefd[2];
	char *argv[MAX_ARG+1], src_filename[MAX_FILENAME];
	char dst_filename[MAX_FILENAME];
	char word[MAX_WORD];
	int append;

	while (1) 
	{
		// one_case Analysis
		switch (one_case = getType(word))		
		{
			// General word case
			case E_WORD :					
				if(argc == MAX_ARG) //Exception handling
				{
					fprintf(stderr, "ERROR - args.\n");
					break;
				}

				argv[argc] = (char *) malloc(strlen(word)+1);
				
				if(argv[argc] == NULL) 
				{
					fprintf(stderr, "ERROR - memory.\n");
					break;
				}

				strcpy(argv[argc], word);
				argc++;
				continue;

			// case '<'
			case E_RIGHT   : 
			
				//set pipe
				if(a_setpipe) 
				{
					fprintf(stderr, "ERROR - <.\n");
					break;
				}

				// Detect type of Source file
				if(getType(src_filename) != E_WORD) 
				{
					fprintf(stderr, "ERROR - <.\n");
					break;
				}

				src_fd = ERROR_FD;
				continue;

			//'>' or ">>" case
			case E_LEFT :
			case E_DLEFT :

				// destination file not defined
				if(dst_fd != 1) 
				{
					fprintf(stderr, "ERROR - don't have target.\n");
					break;
				}

				// destination file not character
				if(getType(dst_filename) != E_WORD) 
				{
					fprintf(stderr, "ERROR - input.\n");
					break;
				}

				// ">>" case is append
				dst_fd = ERROR_FD;
				append = (one_case == E_DLEFT);
				continue;

			// case |, &, ;, 
			case E_PIPE  :
			case E_REF  :
			case E_SEMI :
			case E_NEWL   :
			
				argv[argc] = NULL;
				// pipe case
				if(one_case == E_PIPE) 
				{
					if(dst_fd != 1) 
					{
						fprintf(stderr, "ERROR - pipe.\n");
						break;
					}
					
					// Recusive UserCmd, Analysis of current fd
					return_type = UserCmd(a_waitpid, 1, &dst_fd);
				}
				
				// End case
				else
				{
					return_type = one_case;
				}

				// if set pipe, connection pipe
				if (a_setpipe) 
				{
					if (pipe(pipefd) == ERROR)
					{
						print_error("pipe");
					}
					*a_pipefdp = pipefd[1];
					src_fd = pipefd[0];
				}

				// exe_cmd,
				pid = exe_cmd(argc, argv, src_fd, src_filename,
								dst_fd, dst_filename,append, return_type == E_REF);

				// not pipe case, wait PID
				if (one_case != E_PIPE)
				{
					*a_waitpid = pid;
				}

				// don't have parmameter case
				if (argc == 0 && (one_case != E_NEWL || src_fd > 1))
				{
					fprintf(stderr, "ERROR - don't have parameter.\n");
				}

				// Deallocate used arguments.
				while (--argc >= 0)
				{
					free(argv[argc]);
				}

				return return_type;

			// Wrong command case
			case E_EOF : 
				exit(0);
		} 
	}    
}
