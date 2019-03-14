#include <stdio.h>	// printf(), sprintf()
#include <sys/stat.h>	// stat(), lstat()
#include <sys/types.h>
#include <unistd.h>	// lseek(), SEEK_CUR
#include <dirent.h>	// DIR , S_ISDIR(), S_ISBLK(), ...
#include <string.h>	// memset()
#include <stdlib.h>	// exit()
#include <time.h>	// time()
#include <pwd.h>	// struct passwd, getpwuid()
#include <grp.h>	// struct group, getgrgid() #define TIME_BUF_SIZE 20

#define TIME_BUF_SIZE 20
// #define DEBUG

void access_perm(char * perm, mode_t mode){
		char permchar[] = "rwx";
		memset(perm, '-', 10);
		perm[10] = '\0';

		if(S_ISDIR(mode)) perm[0] = 'd';
		else if(S_ISBLK(mode)) perm[0] = 'b';
		else if(S_ISCHR(mode)) perm[0] = 'c';
		else if(S_ISFIFO(mode)) perm[0] = 'p';
		else if(S_ISLNK(mode)) perm[0] = 'l';
		else if(S_ISSOCK(mode)) perm[0] = 's';

		for(int i=0; i<9; i++){
				if( (mode << i) && 0x100)
						perm[i+1] = permchar[i%3];
		}
		if(mode & S_ISUID) perm[3] = 's';
		if(mode & S_ISGID) perm[6] = 's';
		if(mode & S_ISVTX) perm[9] = 't';
}

int compare_l(const void * file1, const void *file2){
		char filename1[100];
		char filename2[100];
		char temp_str[100];
		long temp_l;

		sscanf((char *)file1, "\n%s %ld %s %s %ld %s %s %s %s", temp_str, &temp_l, temp_str, temp_str, &temp_l, temp_str, temp_str, temp_str, filename1);
		sscanf((char *)file2, "\n%s %ld %s %s %ld %s %s %s %s", temp_str, &temp_l, temp_str, temp_str, &temp_l, temp_str, temp_str, temp_str, filename2);

		if(strcmp(filename1, filename2) < 0)
				return -1;
		else if (strcmp(filename1, filename2) == 0)
				return 0;
		else
				return 1;
}

int compare(const void * file1, const void *file2){
		if(strcmp((char*)file1, (char*)file2) < 0)
				return -1;
		else if (strcmp(file1, file2) == 0)
				return 0;
		else
				return 1;
}

int main(int argc, char *argv[]){
		DIR *d;
		struct stat statbuf;
		struct dirent *dent;
		char perm[11];
		char pathname[80];
		char targetname[80];

		char filename[50];

		char option[20] = { 0 };
		int is_there_option = 0;

		char uowner[10];	// user owner name
		char gowner[10];	// group owner name
		struct passwd *upw;	// this is for uid
		struct group *gentry;	// this is for gid

		char linkbuf[50];	// for symbolic link buffer

		// ---- about time ---- //
		struct tm * mtm;	// changed tm
		char tbuf[TIME_BUF_SIZE];


		// ---- for sorting ---- //
		char fileinfo[255][255];
		int index;

		
		int option_l = 0; // if there is 'l' in option, it is 1
		int option_a = 1; // if there is 'a' in option, it is 1

		memset(option, 0, sizeof(option));

		strcpy(filename, argv[0] + 2);

#ifdef DEBUG
		printf("filename : %s\n", filename);
#endif

		// if(argc < 2) exit(1);
		if(argc < 2){
				strcpy(targetname, ".");
		}else if(argc == 2){
				strcpy(targetname, ".");
				if(argv[1][0] == '-'){
						strcpy(option, argv[1] + 1);
						is_there_option = 1;
				}
		}else{
				strcpy(targetname, argv[1]);
				if(argv[1][0] == '-'){
						strcpy(option, argv[1] + 1);
						is_there_option = 1;
				}
				strcpy(targetname, argv[2]);
		}

#ifdef DEBUG
		printf("option : %s\n", option);
#endif

		stat(targetname, &statbuf);
		if(!S_ISDIR(statbuf.st_mode)){
				fprintf(stderr, "%s is not directory\n", targetname);
				exit(1);
		}

		if( (d = opendir(targetname)) == NULL){
				perror("Error : ");
				exit(1);
		}

//		printf("Lists of Directory(%s):\n", targetname);

		// if there is 'l' option, print total	
		if(strchr(option, 'l') != NULL)
				sprintf(fileinfo[index++], "total : %ld", statbuf.st_blksize / 1024);

			
		while((dent = readdir(d)) != NULL){
			sprintf(pathname, "%s/%s", targetname, dent->d_name);
			lstat(pathname, &statbuf);

			if(strcmp(dent->d_name, filename) == 0) continue;

			if(strchr(option, 'a') == NULL){ 
#ifdef DEBUG
					printf("a is not in option\n");
					printf("path name : %s\n", pathname);
#endif
					option_a = 0;
					if(dent->d_name[0] == '.') continue;
			}
			if(strchr(option, 'l') != NULL){
#ifdef DEBUG
					printf("l in option\n");
#endif
					option_l = 1;

					// set permission string
					access_perm(perm, statbuf.st_mode);

					// set time
					mtm = localtime(&statbuf.st_mtime);
					strftime(tbuf, sizeof(tbuf), "%m월 %d %H:%M", mtm);

					// set user name, group name
					upw = getpwuid(statbuf.st_uid);
					gentry = getgrgid(statbuf.st_gid);
					sprintf(uowner, "%s", upw->pw_name);
					sprintf(gowner, "%s", gentry->gr_name);
					
					// print in fileinfo[index] of perm, hard link, user name, group name, buf size, time data
					sprintf(fileinfo[index], "\n%s %3ld %8s %8s %5ld %s ", perm, statbuf.st_nlink, uowner, gowner, statbuf.st_size, tbuf);
			}
			
			strcat(fileinfo[index], dent->d_name);
			strcat(fileinfo[index], " ");

			// when the file is a symbolic link
			if(perm[0] == 'l'){
					int len = readlink(pathname, linkbuf, 50);
					linkbuf[len] = '\0';
					strcat(fileinfo[index], "-> ");
					strcat(fileinfo[index], linkbuf);
			} else{
					strcat(fileinfo[index], " ");
			}
#ifdef DEBUG
			printf("last option : %s\n", option);
#endif
			index++;
		} 

		// do qsort
		if(option_l){
				qsort(fileinfo + 1, index - 1, sizeof(fileinfo[0]), compare_l);
		}else{
				qsort(fileinfo, index - 1, sizeof(fileinfo[0]), compare);
		}
		strcat(fileinfo[index++], "\n");

		for(int i=0; i<index; i++){
				printf("%s", fileinfo[i]);
		}
		return 0;
}
