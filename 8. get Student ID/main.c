/*
	2017707007 Minjun-KANG QUIZ 



	STUDENT *set_STUDENT(STUDENT*);
	pre - empty
	post - have student data;

*/


#include"Myheader.h"

int main(int argc,char *argv[])
{

	int fd,flag;
	struct flock lock;
	STUDENT student;
	if(argc < 2)
	{
		printf("Lack of parameter\n");
		printf("ERROR!\n");
		return 0;
	}

	do
	{
		printf("\n1. Write mode\n2. Read mode\n");
		printf("File mode : ");
		scanf("%d",&flag);
	
		if(flag == 1) // Write Only mode
		{		
			printf("\n\nWirte ONLY mode\nFile name : %s\n", argv[1]);
			if((fd = open(argv[1],O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
			{
				perror(argv[1]);
				exit(2);
			}
			set_STUDENT(&student);
			
			//lseek(fd, (student.id - START_ID)*sizeof(STUDENT), SEEK_SET);
			if(!write_file(fd, &student))
			{
				perror("Wirte error\n");
				return 0;
			}
			close(fd);
		}
		else if(flag == 2) //Read Only mode
		{
			
			printf("\n\nRead ONLY mode\nFile name : %s\n", argv[1]);

			
			int id = 0;
			printf("Search num [1~n] : ");
			scanf("%d",&id);
			
			if((fd = open(argv[1],O_RDONLY)) == -1)
			{
				perror(argv[1]);
				exit(2);
			}
			

			
			lseek(fd, sizeof(STUDENT)*(id-1), SEEK_SET);
			if(!read_file(fd, &student))
			{
				perror("read error\n");
				return 0;
			}
			close(fd);

		
		}
	}while(flag == 1 || flag == 2);
}















