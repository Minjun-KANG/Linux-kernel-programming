#include <stdio.h>
#include "Myheader.h"
typedef enum MyEnum
{
	GENERAL,
	DLEFT,
	DQU,
	WORD
}SIGN;
//Type Analysis
TYPE getType(char *a_word)
{
	//type sign
	/*
	int GENERAL = 0;
	int DLEFT = 1;
	int DQU = 2;
	int WORD = 3;
	*/

	int state = GENERAL;
	char *w = a_word;
	int c;


	while ((c = getchar()) != EOF) 
	{
		switch (state) 
		{
			/*
			E_WORD, //0 
			E_PIPE, //1 have pipe
			E_REF, //2 background task
			E_SEMI, //3
			E_NEWL, //4 
			E_LEFT, //5
			E_DLEFT, //6 
			E_RIGHT, //7
			E_EOF //8
			*/
			case GENERAL :
				switch (c) 
				{
					case '|':
						return E_PIPE;
					case '&':
						return E_REF;
					case ';' :
						return E_SEMI;
					case '\n':
						return E_NEWL;
					case '>':
						state = DLEFT; //Prepare for double cases.
						continue;
					case '<':
						return E_RIGHT;
			
					case ' ' :
					case '\t':
						continue;

					case '"' : 
						state = DQU;
						continue;

					default  : 
						state = WORD;
						*w++ = c;
						continue;
				}

			case DLEFT:
				if (c == '>')
				{
					return E_DLEFT;
				}
				ungetc(c, stdin);
				return E_LEFT;

			case DQU:
				switch (c) 
				{
					case '\\' : 
						*w++ = getchar();
						continue;

					case '"'  : 
						*w = '\0';
						return E_WORD;

					default   : 
						*w++ = c;
						continue;
				}

			case WORD:
				switch (c ) 
				{
					case ';' :
					case '&' :
					case '|' :
					case '<' :
					case '>' :
					case '\n':
					case ' ' :
					case '\t': 
						ungetc(c, stdin);
						*w = '\0';
						return E_WORD;

					default  : 
						*w++ = c;
						continue;
				}
		}
	}

   return E_EOF;
}
