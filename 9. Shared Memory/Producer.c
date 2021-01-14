/*
	2017707007 Minjun-KANG
	Prdoucer source code

	SM.h included list
---------------------------	
	MEM_SIZE 4096
	MEM_NAME "OS"
	st{
		char val[20];
	}
---------------------------

*/


#include"SM.h"
//#include<sys/shm.h>

//#define temp (512*8)

int main()
{
	printf("%s -  producer \n",MEM_NAME);

	/*char test_case[temp+5] = {0,};
	for(int i=0; i<temp; i++)
	{
		test_case[i] = 'A';
	}
	test_case[temp] = 'L';
	test_case[temp+1] = 'O';
	test_case[temp+2] = 'V';
	test_case[temp+3] = 'E';
	printf("Runtime error check1\n");*/
	
	char temp[20] = "I am "; //use in bounded buf
	ITEM send[BUF_SIZE];
	for(int i = 0; i<BUF_SIZE; i++)
	{
		char a = 65+i;
		temp[5] = a;
		strcpy(send[i].val, temp);
		strcat(send[i].val, "\n");
	}
	int shm_fd;
	void *ptr;
	int full_state = 0;
	int in=0;

	shm_fd = shm_open(MEM_NAME, O_CREAT | O_RDWR, 0666);
	
	ftruncate(shm_fd, MEM_SIZE);
	//printf("Runtime error check2\n");
	//printf("%lld \n",sizeof(size_t));
	ptr = mmap(0, MEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	/*sprintf(ptr, "%s", "Hello World!");
	ptr += strlen("Hello World!");*/
	
	//printf("Runtime error check3");	
	/*const char *msg = "This is Data of Shared memory\n";
	sprintf(ptr, "%s", msg);
	ptr += strlen(msg);*/

	for(int i =0; i<BUF_SIZE; i++){
		sprintf(ptr, "%s", send[i].val);
		printf("%s\n",(char*)ptr);
		ptr += sizeof(strlen(send[i].val)); // Consumer recived ITEM type
	}	
	
	return 0;	
}

