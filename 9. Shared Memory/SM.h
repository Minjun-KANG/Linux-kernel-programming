/*
	2017707007 Minjun-KANG
	Header file containing both producer and consumer.
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/mman.h>
#include<unistd.h>
#define MEM_SIZE 2048
#define MEM_NAME "OS"
#define BUF_SIZE 10

typedef struct _item
{
	char val[20];
}ITEM;


