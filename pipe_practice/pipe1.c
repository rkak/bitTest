#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
		// a number of r/w data
		int data_processed;
		// fd. file_pipes[0] : input
		// file_pipes[1] : output
		int file_pipes[2];
		const char some_data[] = "123";
		// buffer. BUFSIZ = 8192
		char buffer[BUFSIZ + 1];

		// initialization buffer to NULLs
		memset(buffer, '\0', sizeof(buffer));

		if(pipe(file_pipes) == 0){
				// write some_data to file_pipes[1]
				data_processed = write(file_pipes[1], some_data, strlen(some_data));
				printf("Worte %d bytes\n", data_processed);
				// read data in file_pipes[0] to buffer
				data_processed = read(file_pipes[0],buffer, BUFSIZ);
				printf("Read %d bytes : %s\n", data_processed, buffer);
				exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
}
