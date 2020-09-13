#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	if( (fd = open(argv[1],O_RDONLY)) == -1 )
	{
		printf("Error");
	}
	printf("%s Descriptor : %d\n",argv[1],fd);
	close(fd);
}
