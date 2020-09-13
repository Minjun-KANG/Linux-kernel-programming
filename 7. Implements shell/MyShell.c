#include <stdio.h>
#include <unistd.h>
#include "Myheader.h"

int main()
{
	int pid;
	TYPE r_type;

	//print shell, 
	print_shell(); // util.c

	while (1)
	{
		// User Command Analysis
		r_type = UserCmd(&pid, 0, NULL);

		// '&' exist
		if (r_type != E_REF && pid != 0)
		{
			//no back ground processing
			wating(pid);
		}

		// If Enter, last char is '\n', new print_shell()
		if (r_type == E_NEWL)
		{
			print_shell();
		}

		// close fd
		for (int fd=3; fd<MAX_FD; fd++)
		{
			close(fd);
		}
	}
}
