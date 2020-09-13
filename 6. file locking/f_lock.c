/*
int locks(int fd, int type, off_t offset, int whence, off_t len)
// Set the desired lock on a specific record in the file received as a parameter.

type - F_RDLCK or F_WRLCK
offset - offset is byte offset as of whence.
whence - whence is standard point, SEEK_SET, SEEK_CUR, SEEK_END
len - byte length(size)
*/


#include "Myheader.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
//extern int g_Write_flag;

int main(int argc, char *argv[])
{
	int id;
	int option, flag = 0;
	

	if(argc < 3)
	{
		printf("-m  mandatory locking\n");
		printf("-a  advisory locking\n");
		printf("-u  unlocking of target file\n");
		printf("-w  write locking\n");
		printf("=r  read locking\n");
		perror("please Enter the option : \n");
		return 0;
		
	}
	printf("search id : ");
	scanf("%d",&id);
	
	while( ( option = getopt(argc, argv, "mau:wr:MAU:WR:")) != -1)
	{

		if(option > 64 && option < 97)
			option += 32;

		switch(option)
		{
			case 'm':
				flag = M_LOCK;
				break;
			case 'a':
				flag = A_LOCK;
				break;
			case 'u':
				flag = U_LOCK;
				break;
			case 'w':
				flag += W_LOCK;
				break;
			case 'r':
				flag += R_LOCK;
				break;
			case '?':
				printf("Unknown flag\n");
				exit(1);
			default:
				break;
		}
	}
	
	int fd = open(argv[2], O_RDWR);
	if(fd == -1)
	{
		perror("File opne error");
		exit(1);
	}


	struct stat f_stat;
	if( (lstat(argv[2], &f_stat)) < 0 )
	{
		perror("File state error");
		exit(1);
	}
	//lseek(fd, (long) (id-START_ID)*sizeof(STUDENT), SEEK_SET);
	locks(fd, flag, (id-START_ID)*sizeof(STUDENT), SEEK_SET, sizeof(STUDENT)); 

}

