#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "Myheader.h"

//std I/O difference case
void std_DC(int m_src_fd, char *m_src_filename, int m_dst_fd, 
	char *m_dst_filename, int append, int m_backgnd)
{
	int flag, fd;

	// When running in the background,
	if (m_src_fd == 0 && m_backgnd) 
	{
		strcpy(m_src_filename, "/dev/null");
		m_src_fd = ERROR_FD;
	}

	//If there is a source file descriptor
	if (m_src_fd != 0) 
	{
		// Close std input.
		if (close(0) == ERROR)
		{
			print_error("close");
		}

		if (m_src_fd > 0) 
		{
			// duplication std 
			if (dup(m_src_fd) != 0)
			{
				Dup_error("ERROR - Duplication");
			}
		}

		// open src file
		else if (open(m_src_filename, O_RDONLY, 0) == ERROR)
		{
			fprintf(stderr, "ERROR - open : %s\n", m_src_filename);
			exit(0);
		}
	}
   
	// If exist dst_fd
	if (m_dst_fd != 1) 
	{
		// close std output
		if (close(1) == ERROR)
		{
			print_error("close");
		}

		// redefined std out
		if (m_dst_fd > 1) 
		{
			if (dup(m_dst_fd) != 1)
			{
				Dup_error("dup");
			}
		}

		else
		{
			// don't have file, 
			flag = O_WRONLY | O_CREAT;
			
			// no append mode, set trunc
			if (!append)
			{
				flag= flag | O_TRUNC;
			}

			// open file
			if (open(m_dst_filename, flag, 0777) == ERROR) 
			{
				fprintf(stderr, "ERROR - Create : %s\n", m_dst_filename);
				exit(0);
			}

			// appen case
			if (append)	
			{
				if (lseek(1, 0L, 2) == ERROR) //set last offset
					print_error("ERROR - lseek"); 
			}
		}
	}

	// close fd
	for (fd =3; fd < MAX_FD; fd++)
	{
		close(fd);
	}

	return;
}
