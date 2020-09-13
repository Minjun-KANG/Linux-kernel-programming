#include "Myheader.h"

void reverse(char *ID)
{
	printf("reverse student id : ");
	for(int i = strlen(ID); i>=0; i--)
	{
	
		printf("%c",ID[i]);
	}
	printf("\n");
	
}
