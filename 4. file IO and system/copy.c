#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

/*
	2017707007 Minjun-KANG copy.c
	
	ssize_t read (int fd, void *buf, size_t nbytes);

*/
int main(int argc, char *argv[])
{
	int fd1, fd2;
	char buf[255];
	int n_Byte = 0;
	if( (fd1 = open(argv[1],O_RDONLY)) == -1 )
	{
		perror(argv[1]); //print error 
	}
	if( (fd2 = creat(argv[2],0777)) == -1 )
	{
		perror(argv[2]); //print error
	}
	while( (n_Byte = read(fd1, buf, 255)) > 0)
	{
		printf("%s\n",buf);
		write(fd2,buf,n_Byte);
	}
	close(fd1);
	close(fd2);
} 
