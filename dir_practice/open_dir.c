#include <stdio.h>	// printf()
#include <unistd.h>	//
#include <dirent.h>	// DIR struct, mkdir()

int main(void){
		DIR * dir_info;
		struct dirent *dir_entry;

		mkdir("makeA", 0755);
		mkdir("makeB", 0755);

		dir_info = opendir(".");	// get current directory info
		
		if(dir_info != NULL){
				while(dir_entry=readdir(dir_info)){
						printf("%s\n", dir_entry->d_name);
				}
				closedir(dir_info);

		}

		return 0;
}
