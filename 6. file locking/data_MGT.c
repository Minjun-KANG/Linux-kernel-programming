#include"Myheader.h"


void set_STUDENT(STUDENT *st)
{
	
	printf("%-10s, %-8s, %-8s, %-4s\n","ID","name","phone","GPA");
	scanf("%d %s %s %f", &st->id, st->name, st->phone, &st->GPA);
	/*printf("Student name : ");
	scanf("%s", st->name);
	printf("Student Phone number : ");
	scanf("%s", st->phone);
	printf("GPA : ");
	scanf("%d", &st->GPA);*/
}

int write_file(int fd, STUDENT *st)	//error 0;
{
	
	int return_num = -1;
	//char temp[20]= {0,};
	/*if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;*/

	/*

	//strcpy(temp, "ID - ");
	//strcpy(temp, st->id);
//	strcat(st->id,"\n");
	if( (write(fd,st->id,strlen(st->id))) == -1 )
		return_num++;

	

	//strcpy(temp, "NAME - ");
	//strcpy(temp, st->name);
//	strcat(st->name,"\n");
	if( (write(fd,st->name,strlen(st->name))) == -1 )
		return_num++;
	
	

	//strcpy(temp,"PHONE - ");
	//strcpy(temp, st->phone);
//	strcat(st->phone,"\n");
	if( (write(fd,st->phone,strlen(st->phone))) == -1 )
		return_num++;
	

	//strcpy(temp,"GPA - ");
	//strcpy(temp, st->GPA);
//	strcat(st->GPA,"\n");
	if( (write(fd,st->GPA,strlen(st->GPA))) == -1 )
		return_num++;
	*/
	write(fd, (char*)st,sizeof(STUDENT));
	return return_num;

}

/*
kakaotalk 05_14 04:20 memo


*/
int read_file(int fd, STUDENT *st) //error 0;
{
	


	//printf("\n%d\n%x", BUFSIZ, BUFSIZ);
	
	
	int return_num = -1;
	
	if(read(fd, (char *)st, sizeof(STUDENT)) == -1 )
		return_num ++;

/*	if(read(fd,st->name,BUFSIZ) == -1 )
		return_num ++;
	
	if(read(fd,st->phone,BUFSIZ) == -1 )
		return_num ++;

	if(read(fd,st->GPA,BUFSIZ) == -1 )
		return_num ++;
*/	
	printf("\n\n%s\n","==========");
	printf("ID    : %d\n",st->id);
	printf("NAME  : %s\n",st->name);
	printf("PHONE : %s\n",st->phone);
	printf("GPA   : %0.1f\n",st->GPA);
	return return_num;
}
