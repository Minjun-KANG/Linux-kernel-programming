#include "Myheader.h"

int locks(int fd, int type, off_t offset, int whence, off_t len) //error -1 
{
	int return_num = 0;
	struct stat f_stat;
	if( (fstat(fd, &f_stat)) < 0 )
	{
		perror("File state error");
		exit(1);
	}

	struct flock f_lock;
	if((type & W_LOCK) == W_LOCK)
	{
		printf("Write locking\n");
		f_lock.l_type = F_WRLCK;
		//g_Write_flag = 1;
	}else if((type & R_LOCK) == R_LOCK)
	{
		f_lock.l_type = F_RDLCK;
	}
	

	if((type & M_LOCK) == M_LOCK)
	{
		//Mandatory locking -- forced
		if((fchmod(fd, S_ISGID)) == -1)
		{
			perror("File change mode error ");
			return_num--;
		}
	
	}else if((type & A_LOCK) == A_LOCK)
	{
		
		printf("advisory locking\n"); 
		f_lock.l_whence = whence;
		f_lock.l_start = offset;
		f_lock.l_len = len;
		/*if(fcntl(fd, F_GETLK, &f_lock) == -1)
		{
			perror("File locking get error");
		}
		if(f_lock.l_type != F_UNLCK)
		{
			perror("This file is locking");
			return -1;
			
		}*/
		
		
		if(fcntl(fd, F_SETLKW, &f_lock) == -1)
		{
			perror("A_LOCK error ");
			return_num--;
		}
	//	sleep(30);
			
	}else if((type & U_LOCK) == U_LOCK)
	{
		//Unlocking
		if(f_stat.st_mode & S_ISGID)
		{
			if((fchmod(fd,777)) == -1)
			{
				perror("File change mode error");
				return_num --;
			}
		}
		if(f_lock.l_type != F_UNLCK)
		{
			f_lock.l_type = F_UNLCK;
			if(fcntl(fd, F_SETLKW, &f_lock) == -1)
			{
				perror("File unlock fail");
				return_num--;
			}
		}
	}
	return return_num;
}
