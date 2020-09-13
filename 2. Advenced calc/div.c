//div.c division operating
#include<stdio.h>

int funcDiv(int nAlpha, int nBeta)
{
	if(!nBeta) // If Beta is zero
	{
		printf("nBeta is zero\n");
		return 0;
	}
	return nAlpha / nBeta;
}
