// used this example until you understand the function

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

const char * path = ".";

int main(int argc, char *argv[]){
		struct	dirent ** namelist;
		int		count;
		int		idx;

		if(argc < 2){
				printf("argv[1] is empty\n");
				return 1;
		}

		path = argv[1];

		if((count = scandir(path, &namelist, NULL, alphasort)) == -1){
				fprintf(stderr, "%s Directory Scan Error: %s\n", path, strerror(errno));
				return 1;
		}

		for(idx = 0; idx <count; idx++){
				printf("%s\n", namelist[idx]->d_name);
		}

		// each namelist memory free
		for(idx = 0; idx < count; idx++){
				free(namelist[idx]);
		}

		// namelist memory free
		free(namelist);

		return 0;
}
