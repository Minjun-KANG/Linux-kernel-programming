/*
	2017707007 Minjun-KANG
	Consumer source code
	
	SM.h included list
---------------------------
	MEM_SIZE 4096
	MEM_NAME "OS"
---------------------------
*/


#include"SM.h"

int main()
{
	printf("%s - Consumser \n",MEM_NAME);
	
	int shm_fd;
	void *ptr;
	ITEM recv[BUF_SIZE];
	

	shm_fd = shm_open(MEM_NAME, O_RDONLY, 0666);

	ptr = mmap(0, MEM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	//printf("%s\n", (char *)ptr);
	//printf("%s", (char*)ptr);

	
	for(int i=0; i<BUF_SIZE; i++)
	{
		strcpy(recv[i].val ,ptr+i);
		ptr+=strlen(recv[i].val);
		//memcpy(recv[i].val,ptr+(ITEM*i),sizeof(ITEM));
	}

	int num =0;
	printf("found data index : ");
	scanf("%d",&num);
	
	printf("shared data : %s\n", recv[num].val);
	
	//printf("%d and %c\n",recv[0].num, recv[0].val);



	shm_unlink(MEM_NAME);
	
	return 0;
}
