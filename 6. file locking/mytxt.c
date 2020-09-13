/*
	2017707007 Minjun-KANG hoemwork [file record lock]

	locks(int fd, int type, off_t offset, int whence, off_t len)
	pre - File not locked.
	post - In record unit, lock.


	STUDENT *set_STUDENT(STUDENT*);
	pre - empty
	post - have student data;

	struct student
	{
		int id;
		char *name;
		char *phone;
		float GPA;
	}

	struct flock{
		short l_type;
		off_t l_type;
		short l_whence;
		off_t l_len;
		pid_t l-pid;
	}
*/


#include"Myheader.h"
//int g_Write_flag = 0;
int main(int argc,char *argv[])
{

	int fd,flag;
	STUDENT student;
	if(argc < 2)
	{
		printf("Lack of parameter\n");
		printf("ERROR!\n");
		return 0;
	}

	do
	{
		printf("\n1. Write mode\n2. Read mode\n3. Modify mode\n4. END\n");
		printf("File mode : ");
		
		scanf("%d",&flag);
		system("clear");
	
		if(flag == 1) // Write Only mode
		{		
			printf("\n\nWirte ONLY mode\nFile name : %s\n", argv[1]);
			if((fd = open(argv[1],O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
			{
				perror(argv[1]);
				exit(2);
			}
			
			set_STUDENT(&student);
			
			lseek(fd, (long)(student.id - START_ID)*sizeof(STUDENT), SEEK_SET);
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
			

			
			lseek(fd, (long)sizeof(STUDENT)*(id-START_ID), SEEK_SET);
			if(!read_file(fd, &student))
			{
				perror("read error\n");
				return 0;
			}
			close(fd);

		
		}else if(flag == 3)
		{
			
			
			printf("\n\nModify ONLY mode\nFile name : %s\n", argv[1]);
			
			//if(fctrl

			
			//char r_temp[sizeof(STUDENT)+4];
			int id = 0;
			printf("Search num [1~n] : ");
			scanf("%d",&id);
		
			if((fd = open(argv[1],O_RDWR)) == -1)
			{
				perror(argv[1]);
				exit(2);
			}
			lseek(fd, (long)sizeof(STUDENT)*(id - START_ID), SEEK_SET);
			
			if(!read_file(fd, &student))
			{
				perror("Read error\n");
				return 0;
			}
			
			

			lseek(fd, -sizeof(STUDENT), SEEK_CUR);
	
			if( (locks(fd, (W_LOCK | A_LOCK), -sizeof(STUDENT), SEEK_CUR, sizeof(STUDENT))) == -1)
			{
				printf("file locking error");
				return 0;
			}

			set_STUDENT(&student);

			if(!write_file(fd, &student))
			{
				perror("Modify error\n");
				return 0;
			}
			sleep(60);
			locks(fd, U_LOCK, (id-START_ID)*sizeof(STUDENT), SEEK_SET, sizeof(STUDENT));


			close(fd);
		}
		else if(flag == 4)
		{
			return 0;
		}
	}while(flag > 0 && flag < 5);

}















