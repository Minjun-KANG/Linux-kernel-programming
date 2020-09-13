#include"Myheader.h"


void set_STUDENT(STUDENT *st)
{
	
	//printf("%-10s, %-8s, %-8s, %-4s\n","ID","name","phone","GPA");
	//scanf("%d %s %s %f", &st->id, st->name, st->phone, &st->GPA);
	printf("name : ");
	scanf("%s", st->name);
	printf("ID   : ");
	scanf("%s", st->id);
	printf("Address : ");
	scanf("%s", st->address);
	printf("money[WON] : ");
	scanf("%s",st->money);
	printf("family : ");
	scanf("%s ",st->family);
	
}

int write_file(int fd, STUDENT *st)	//error 0;
{
	
	int return_num = -1;
	char temp[50]= {"===================\n"};
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;

	strcpy(temp, "NAME - ");
	strcpy(temp, st->name);
	strcat(temp,"\n");
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;
	

	strcpy(temp, "ID - ");
	strcpy(temp, st->id);
	strcat(temp,"\n");
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;

	

	strcpy(temp, "ADDRESS - ");
	strcpy(temp, st->address);
	strcat(temp,"\n");
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;
	
	

	strcpy(temp,"MONEY - ");
	strcpy(temp, st->money);
	strcat(temp,"\n");
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;
	

	strcpy(temp,"FAMILY - ");
	strcpy(temp, st->family);
	strcat(temp,"\n");
	if( (write(fd,temp,strlen(temp))) == -1 )
		return_num++;
	
//	write(fd, (char*)st,sizeof(STUDENT));
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
	printf("name    : %s\n",st->name);
	printf("id      : %s\n",st->id);
	printf("address : %s\n",st->address);
	printf("money   : %s\n",st->money);
	printf("family  : %s\n",st->family);
	return return_num;
}
