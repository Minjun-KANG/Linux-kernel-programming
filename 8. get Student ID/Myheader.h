
/*
header
It includes <stdio.h> and <fcntl.h> headers.

function declaration
int locks(int fd, int type, off_t offset, int whence, off_t len)
// Set the desired lock on a specific record in the file received as a parameter.

type - F_RDLCK or F_WRLCK
offset - offset is byte offset as of whence.
whence - whence is standard point, SEEK_SET, SEEK_CUR, SEEK_END
len - byte length(size)



*/
#include<sys/types.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<fcntl.h>
//2017707007

#define START_ID 2017707001 // start ID

typedef struct _STUDENT
{
	
	char name[20];
	char id[14];
	char address[30];
	char money[20];
	char family[20];
	

}STUDENT;




int locks(int fd, int type, off_t offset, int whence, off_t len); //locks prototypev
void set_STUDENT(STUDENT*);
int write_file(int fd, STUDENT *student);	//error -1;
int read_file(int fd, STUDENT *student);
