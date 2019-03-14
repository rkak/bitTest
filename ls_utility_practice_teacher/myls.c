#include <sys/types.h>
#include <dirent.h>	// S_ISDIR(), S_ISBLK(), ....  #include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>	// sprintf()
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>	// getpwuid()
#include <grp.h>	// getgrgid()
#include <time.h>

#define DEBUG

#define PATH_LENGTH 	100
#define PERM_LENGTH 	10

//=========================================
// dirent 구조체
//=========================================
/*
struct dirent
{
  	long d_ino; //inode 번호
	off_t d_off; // offset
	unsigned short d_reclen; //d_name 길이
	char d_name[NAME_MAX+1]; //파일 이름
};
*/

//=========================================
// stat 구조체
//=========================================
/*
struct stat {
	dev_t     st_dev;     // ID of device containing file 
	ino_t     st_ino;     // inode number 
	mode_t    st_mode;    // 파일의 종류 및 접근권한
	nlink_t   st_nlink;   // hardlink 된 횟수
	uid_t     st_uid;     // 파일의 owner
	gid_t     st_gid;     // group ID of owner
	dev_t     st_rdev;    // device ID (if special file)
	off_t     st_size;    // 파일의 크기(bytes)
	blksize_t st_blksize; // blocksize for file system I/O
	blkcnt_t  st_blocks;  // number of 512B blocks allocated
	time_t    st_atime;   // time of last access
	time_t    st_mtime;   // time of last modification
	time_t    st_ctime;   // time of last status change
};
*/

//=========================================
// group 구조체
//=========================================
/*
struct group {
	char   *gr_name;       // group name 
	char   *gr_passwd;     // group password 
	gid_t   gr_gid;        // group ID 
	char  **gr_mem;        // group members 
};
*/

//=========================================
// passwd 구조체
//=========================================
/*
struct passwd{
	char *pw_name;
	char *pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	time_t pw_change;
	char *pw_class;
	char *pw_gecos;
	char *pw_dir;
	char *pw_shell;
	time_t pw_expire;}
*/

//=========================================
// Function Name : access Name
// arg1 : permission value
// arg2 : mode 
// return : void
// Description : 
//=========================================
void access_perm(char *perm, mode_t mode)
{
	int i;
	char permchar[] = "rwx";
	memset(perm, '-', 10);
	perm[10] = '\0';

	if (S_ISDIR(mode)) perm[0] = 'd';
	else if (S_ISCHR(mode)) perm[0] = 'c';
	else if (S_ISBLK(mode)) perm[0] = 'b';
	else if (S_ISFIFO(mode)) perm[0] = 'p';
	else if (S_ISLNK(mode)) perm[0] = 'l';
											
	for (i = 0; i < 9; i++) 
	{
		if ((mode << i) & 0x100)
		perm[i+1] = permchar[i%3];
	}
	
	if (mode & S_ISUID) perm[3] = 's';
	if (mode & S_ISGID) perm[6] = 's';
	if (mode & S_ISVTX) perm[9] = 't';
}


int main(int argc, char *argv[])
{
	DIR *dp;				// DIR pointer
	struct stat statbuf;	// inode info
	struct dirent *dent;
	struct passwd *user_entry;
	struct group *group_entry;
	struct tm * tm;
					
	char perm[PERM_LENGTH + 1];	// 1 is for NULL
	char pathname[PATH_LENGTH];
	char dirname[PATH_LENGTH];

	int flag;
	char temp[20];
								
	if (argc == 1){
			flag = 0;
			strcpy(dirname, ".");
	}
	if(argc > 1){
			sprintf(temp,"-al");
			if(!strcmp(temp, argv[1])){
				flag = 1;
				strcpy(dirname, ".");
			}
			else{
				flag = 2;
				strcpy(dirname, argv[1]);
			}
	}
	if(argc > 2){
			// -al is already handling
			flag = 3;
			strcpy(dirname, argv[2]);
	}
								
#ifdef DEBUG
	printf("dir = %s\n", dirname);
	printf("flag = %d\n", flag);
#endif

	// read directory inode info
	stat(dirname, &statbuf);

	// If the file is not a directory, print error
	if (!S_ISDIR(statbuf.st_mode))
	{
		fprintf(stderr, "%s is not directory\n", dirname);
		exit(1);
	}
										
	// Directory open fail
	if ((dp = opendir(dirname)) == NULL) 
	{
		perror("Error:");
		exit(1);
	}
												
	// If directory open success, print dirctory name
	printf("Lists of Directory(%s):\n", dirname);
										
	// read directory info until no more info
	while((dent = readdir(dp)) != NULL) 
	{
		if(flag == 1 || flag == 3){
			sprintf(pathname, "%s/%s", dirname, dent->d_name); lstat(pathname, &statbuf);
			access_perm(perm, statbuf.st_mode);

			user_entry = getpwuid(statbuf.st_uid);
			group_entry = getgrgid(statbuf.st_gid);

			tm = localtime(&statbuf.st_mtime);
			strftime(temp, sizeof(temp), "%m월 %e %H:%M", tm);

			printf("%s %3ld %8s %8s %8ld %s %s\n", perm, statbuf.st_nlink, user_entry->pw_name, group_entry->gr_name, statbuf.st_size, temp, dent->d_name);
		} else{

		}
	}
	closedir(dp);
														
	return 0;
}
