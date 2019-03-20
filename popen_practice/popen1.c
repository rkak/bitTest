#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

int main(void){
		// file structure pointer
		FILE * read_fp;
		// buffer BUFSIZ = 8192
		char buffer[BUFSIZ + 1];
		int chars_read;

#ifdef DEBUG
		printf("buffer size = %ld\n", sizeof(buffer));
#endif

		// buffer initialization to NULLs
		memset(buffer, '\0', sizeof(buffer));

		// pipe open 'uname -a'
		read_fp = popen("uname -a", "r");
		if(read_fp != NULL){
				chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
				if(chars_read > 0){
						printf("Output was : -\n%s\n", buffer);
				}
				pclose(read_fp);
				exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
}
