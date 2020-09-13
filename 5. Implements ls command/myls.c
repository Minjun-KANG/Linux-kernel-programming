#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h> //getopt
#include<grp.h> //group
#include<pwd.h> //passwd
#include<time.h> //time
#include<dirent.h> //directory
#include<string.h>
/*
	2017707007 

	checked file type

	int stat(const char *filename, struct stat *buf);
	Get file status by inode.
	lstat is used for symbolic links.



	if(lstat("test.txt",&buf) < 0)
		printf("error")
	else
		if(S_ISREG(buf.st_mode)) // S_ISREG is constant.
			printf("%s \n","regular file");

	
	int getopt(int argc, char *const argv[], const char *optstring)
	POST - Return the found option character.
	       '?' If ther is an unspecified option.
	       Returns -1 if there are no more option.


*/
int pass(char *);
void print_total(long);
void print_ls_R(DIR *, char *, int);
void is_dir_print(DIR *);
void print_ls_l(struct stat);
void print_permi(unsigned int); // print type and permission.
void print_name(uid_t, gid_t); //print UID, GID at String
void print_time(time_t); //print last modification time.

int main(int argc, char *argv[])
{
	//struct stat file_stat;
	//extern char *optarg;
	int option;
	int l_flag = 0;
	int R_flag = 0;
	int no_flag = 0;
	while( ( option = getopt(argc, argv, "lR")) != -1)
	{
		switch(option)
		{
			case 'l':
				l_flag = 1;
				break;
			case 'R':
				R_flag = 1;
				break;
			case '?':
				break;
			default:
				no_flag = 1;
				break;
		}
	}
	
	if(R_flag) //processing -Rl , -lR , -R
	{
	
		
		DIR *dp;
		char path[255] = ".";
		if(argc > 2)
		{
			struct stat f_stat;
			if(lstat(argv[2], &f_stat) < 0)
			{
				perror("lstat()");
			}
			if(S_ISDIR(f_stat.st_mode))
			{
				strcat(path, "/");
				strcat(path, argv[2]);
			}else{
				if(l_flag)
				{
					print_ls_l(f_stat);
					printf(" %s",argv[2]);
					printf("\n");
				}
				else
					printf("%s\n",argv[2]);
				return;
			}
		}	
		if( (dp = opendir(path))==NULL)
		{
			printf("directory empty");
		}
		
		print_ls_R(dp, path, l_flag);
	}
	if(argc < 3 && !R_flag) //processing -l
	{
		DIR *dp;
		struct dirent *dir_temp;
		if( (dp = opendir(".")) == NULL) //directory open
		{
			printf("directory empty");
		}
		
			
		long blk_size = 0;
		while((dir_temp = readdir(dp)) != NULL)
		{
			struct stat f;
			if(pass(dir_temp->d_name))
				continue;
			lstat(dir_temp->d_name, &f);
			blk_size += f.st_blocks;
		}
		print_total(blk_size/2);
		closedir(dp);
	
	
		if( (dp = opendir(".")) == NULL) //directory open
		{
			printf("directory empty");
		}

	
		Is_dir_print(dp);
	}
	else if(!R_flag && l_flag) //processing -l [target]
	{
		//When the target file exists
		
		struct stat f_stat;
		if((lstat(argv[2], &f_stat)) < 0)
		{
			perror("lstat()");
		}
		if(S_ISDIR(f_stat.st_mode))
		{
			DIR *dp;
			if( (dp = opendir(argv[2])) == NULL) //directory open
			{
				printf("directory empty");
			}
			Is_dir_print(dp);
		}
		else
		{
			print_ls_l(f_stat);
			printf(" %s\n",argv[2]);
		}
		
	}
}
void print_total(long size)
{
	printf("total : %d\n",size);
}
int pass(char *temp)
{

	if(temp[0] == '.')
		return 1;
	else
		return 0;
}
void print_ls_R(DIR *dp, char *path, int l_flag)
{	
	printf("%s:\n",path);
		
	DIR *dp2;
	struct dirent *dir;
	struct dirent *dir_temp;
	struct stat f_stat;
	
	int flag = 0;
	int is_start = 0;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
	long blk_size = 0;
	while((dir_temp = readdir(dp)) != NULL)
	{
		struct stat f;
		if(pass(dir_temp->d_name))
			continue;
	//	if(lstat(dir_temp->d_name, &f) < 0)
		if(lstat(path,&f)<0)
		{
	//		printf("%s\n",dir_temp->d_name);
			perror("lstat()");
		}
	//printf("%s\n",dir_temp->d_name);
	//	printf("%s\n",path);
		//printf("%d\n", f.st_blocks);
		blk_size += f.st_blocks;
	}
	print_total(blk_size);
	closedir(dp);
	

	if( (dp = opendir(path)) == NULL) //directory open
	{
		printf("directory empty");
	}



	if(dp == NULL)
		return;
	
	while( (dir = readdir(dp)) != NULL)
	{
	
		lstat(dir->d_name, &f_stat);

		if(dir->d_ino == 0)
			continue;
			
		if(pass(dir->d_name))
			continue;

		if(l_flag)
		{
			print_ls_l(f_stat);
			printf(" %s",dir->d_name);
			printf("\n");
		}
		else
			printf("%s   ",dir->d_name);
		
		if(S_ISDIR(f_stat.st_mode))
		{
			if(!is_start)
			{
				is_start = 1;
				strcat(path, "/");
				strcat(path, dir->d_name);
			}	

			flag = 1;
		//	dp2 = opendir(dir->d_name);
			dp2 = opendir(path);
		//	printf("%s\n",path);

		}
		
	}
	
	printf("\n\n");
	
	if(flag)
	{
		print_ls_R(dp2, path, l_flag);
	}
	closedir(dp);
}
void Is_dir_print(DIR *dp)
{	
	//When there is no target file
		
	struct dirent *dir;
	struct dirent *dir_temp;
	long blk_size = 0;
	
	
	while((dir = readdir(dp)) != NULL)
	{
	
		if(dir->d_ino == 0)
			continue;
		struct stat temp;
		if(pass(dir->d_name))
			continue;
		if(lstat(dir->d_name, &temp) < 0)
			perror("stat()");
		print_ls_l(temp);
		printf(" %s\n",dir->d_name);
	}
	closedir(dp);
	
}
void print_ls_l(struct stat f_stat)
{
	print_permi(f_stat.st_mode); //type and permission
	printf(" %d",f_stat.st_nlink);//file link
	print_name(f_stat.st_uid, f_stat.st_gid);//file name 
	printf(" %5d",f_stat.st_size); //file size
	print_time(f_stat.st_mtime); //file modification time
	//printf(" %s",argv[1]); // file name
}
void print_time(time_t time)
{
	struct tm *time_form;
	char temp[100];

	time_form = localtime(&time);
	strftime(temp, sizeof(temp), "%b %2e %H:%M",time_form);
	printf(" %s",temp);
}
void print_name(uid_t uid, gid_t gid)
{
	struct group *s_gid;
	struct passwd *s_uid;
	
	s_uid = getpwuid(uid);
	s_gid = getgrgid(gid);

	printf(" %s",s_uid->pw_name);
	printf(" %s",s_gid->gr_name);
}
void print_permi(unsigned int mode)
{
	//file type
	if(S_ISREG(mode))
		printf("-");
	else if(S_ISDIR(mode))
		printf("d");
	else if(S_ISCHR(mode))
		printf("c");
	else if(S_ISBLK(mode))
		printf("b");
	else if(S_ISFIFO(mode))
		printf("p");
	else if(S_ISLNK(mode))
		printf("l");
	else if(S_ISSOCK(mode))
		printf("s");



	//permission owner
	if(mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	if(mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if(mode & S_IXUSR)
		printf("x");
	else
		printf("-");
	//permission group
	if(mode & S_IRGRP)
		printf("r");
	else
		printf("-");
	if(mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	if(mode & S_IXGRP)
		printf("x");
	else
		printf("-");
	//permission Other
	if(mode & S_IROTH)
		printf("r");
	else
		printf("-");
	if(mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	if(mode & S_IXOTH)
		printf("x");
	else
		printf("-");
}
