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
#include <sys/ioctl.h>	// ioctl()
#include <termios.h>	// struct winsize

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

int main(int argc, char *argv[]){
		// ---- for get window size ---- //
		struct winsize ws;
		int line_len = 0;		// length of a line

		DIR *d;
		struct stat statbuf;
		struct dirent *dent;
		struct dirent **sortDent;
		char perm[11];
		char pathname[80];
		char targetname[80];

		char filename[50];

		char option[20] = { 0 };
		int is_there_option = 0;

		// ---- uid, pid ----- //
		struct passwd *upw;	// this is for uid
		struct group *gentry;	// this is for gid
		char uowner[10];	// user owner name
		char gowner[10];	// group owner name

		char linkbuf[50];	// for symbolic link buffer

		// ---- about time ---- //
		struct tm * mtm;	// modified tm
		char tbuf[TIME_BUF_SIZE];

		// ---- is there option value ---- //		
		int option_l = 0; // if there is 'l' in option, it is 1
		int option_a = 0; // if there is 'a' in option, it is 1


		memset(option, 0, sizeof(option));
		ioctl(0, TIOCGWINSZ, &ws);

#ifdef DEBUG
		printf("lines %d\n", ws.ws_row);
		printf("columns %d\n", ws.ws_col);
#endif

		strcpy(filename, argv[0] + 2);

#ifdef DEBUG
		printf("filename : %s\n", filename);
#endif

		// if(argc < 2) exit(1);
		if(argc < 2){
				strcpy(targetname, ".");
		}else if(argc == 2){
				strcpy(targetname, argv[1]);
				if(argv[1][0] == '-'){
						strcpy(option, argv[1] + 1);
						is_there_option = 1;
						strcpy(targetname, ".");
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

		if(strchr(option, 'a') != NULL){
				option_a = 1;
		}
		if(strchr(option, 'l') != NULL){
				option_l = 1;
		}

//		printf("Lists of Directory(%s):\n", targetname);

		// if there is 'l' option, print total	
		if(option_l)
				printf("total : %ld", statbuf.st_blksize / 1024);

			
		int count = scandir(targetname, &sortDent, NULL, alphasort);
		for(int i=0; i<count; i++){
			sprintf(pathname, "%s/%s", targetname, sortDent[i]->d_name);
			lstat(pathname, &statbuf);

			if(strcmp(sortDent[i]->d_name, filename) == 0) continue;

			// there is no a option
			if(!option_a){ 
					if(sortDent[i]->d_name[0] == '.') continue;
			}
			// there is l option
			if(option_l){
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
					
					printf("\n%s %3ld %8s %8s %5ld %s ", perm, statbuf.st_nlink, uowner, gowner, statbuf.st_size, tbuf);
			}
			
			int file_len = 4;
			if(line_len + ws.ws_col/3 >= ws.ws_col){
					printf("\n");
					line_len = 0;
			}
			printf("%s", sortDent[i]->d_name);
			if(strlen(sortDent[i]->d_name) < file_len){
					int k = strlen(sortDent[i]->d_name);
					while(k % file_len != 0){
							printf(" ");
							k++;
							line_len ++;
					}
			}
			else
					line_len += strlen(sortDent[i]->d_name);	

			// when the file is a symbolic link
			if(perm[0] == 'l'){
					int len = readlink(pathname, linkbuf, 50);
					linkbuf[len] = '\0';
					printf("-> %s", linkbuf);
					line_len += (3 + strlen(linkbuf));
			} else{
					printf(" ");
					line_len += 1;
			}
#ifdef DEBUG
			printf("last option : %s\n", option);
#endif
		} 

		printf("\n");
		return 0;
}
