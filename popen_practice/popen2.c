#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
		// file structure pointer
		FILE *write_fp;

		// buffer, BUFISZ = 8912
		char buffer[BUFSIZ + 1];
		// write to buffer "Once upon ..."
		sprintf(buffer, "Once upon a time, there was...\n");

		// pipe open of write_fp to od -c for writing
		// popen return : FILE pointer
		write_fp = popen("od -c", "w");

		if(write_fp != NULL){
				// input buffer to write_fp(od -c)
				// == od -c < "Once upon ..."
				// -- "Once upon ..." | od -c
				fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
				pclose(write_fp);
				exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
}
