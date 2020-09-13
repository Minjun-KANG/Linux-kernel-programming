#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> // open, close
#include<unistd.h> // wirte, read ..
#include<string.h>

/*
	2017707007 Minjun-KANG homework
	int open(const char *path, int oflag, [mode_t mode]);
	int close(int fd)
	int wirte(int fd, void *buf, size_t nbytes);

*/

int main(int argc, char *argv[])
{
	char buf[4][255];
	int fd;
	
	if((fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1) //Read, Write 
	{
		printf("Fail file open\n");
	}
	else
	{
		printf("file is %s\nfile Descriptor %d\nSuccess file open\n",argv[1],fd); //file name and file Descriptor
	}

	
	
	
	printf("Name : ");
	gets(buf[0]); //scanf("%[^\n]s , buf[0]); 

	printf("Major : ");
	gets(buf[1]);
	
	printf("YYMMDD : "); 
	gets(buf[2]);
	
	printf("Phone Number : ");
	gets(buf[3]);


	strcat(buf[0], " - Name\n");
	strcat(buf[1], " - Major\n");
	strcat(buf[2], " - YYMMDD\n");
	strcat(buf[3], " - Phone Number\n");
	
	
	for(int i = 0 ; i < 4; i++)
	{
		if((write(fd,buf[i],strlen(buf[i])))==-1)
		{	
			printf("Write Error\n");
		}
		//printf("%s\n",buf[i]);
	}
	close(fd);
	
	printf("\nSuccess file write\n");
}
