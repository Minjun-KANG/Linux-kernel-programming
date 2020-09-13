#ifndef MYSHELL_H
#define MYSHELL_H

#define ERROR		(-1)
#define ERROR_FD		(-2)

#define MAX_FILENAME	10
#define MAX_ARG			10
#define MAX_WORD		20
#define MAX_FD			20





// file type define
typedef enum //enum is automatic initialize started from 0, mean ->each type sign
{
	E_WORD, //0 
	E_PIPE, //1 have pipe
	E_REF, //2 background task
	E_SEMI, //3
	E_NEWL, //4 
	E_LEFT, //5
	E_DLEFT, //6 
	E_RIGHT, //7
	E_EOF //8
} TYPE;

void print_shell(); //shell print processing env
TYPE UserCmd(int *m_waitpid, int m_setpipe, int *m_pipefdp);
/*
User Command Analysis
Called by main.
Each command is processed.
	pre - pid, pipe presence, pipe fd
	post - Return information needed for next state
*/
TYPE getType(char *a_word); 
/* 
type Analysis
Called by Usercmd.
	pre - It takes a string as a parameter.
	post - Returns one character of the filtered type.

*/
int exe_cmd(int argc, char *argv[], int a_src_fd, char *a_src_filename,
	int a_dst_fd, char *a_dst_filename, int append, int backgnd);
/*
Execute the command on the target received as an argument.
call by UserCmd
	pre - It takes the target files as arguments.
	post - execute my command.

	Running MyCmd() internally.
*/

void print_error(char *message);
/*
print error
	pre - Receives the parameter passed at each error point.
	post - Error number and output according to the form.
*/

void std_DC(int m_src_fd, char *m_src_filename, int m_dst_fd,
	char *m_dst_filename, int append, int m_backgnd);
/*
	pre - It takes the target files as arguments.
	post - Standard I/O also selects file I/O.
*/
void wating(int pid);
int Mycmd(int argc, char *argv[], int m_src_fd, int m_dst_fd);
void Dup_error(char *m_error);
void My_cd(int argc, char *argv[]);
void My_exit();
void My_ls(int argc, char *argv[]);
void My_mkdir(int argc, char *argv[]);
#endif
