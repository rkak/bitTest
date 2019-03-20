#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){
		int data_processed;
		int file_pipes[2];
		const char some_data[] = "123";
		char buffer[BUFSIZ + 1];
		pid_t fork_result;
		memset(buffer, '\0', sizeof(buffer));

		// create pipe 
		if(pipe(file_pipes) == 0){
				fork_result = fork();

				if(fork_result == -1){
						fprintf(stderr, "Fork failure");
						exit(EXIT_FAILURE);
				}
				// child process
				if(fork_result == 0){
						// file_pipes[0] : input to buffer(string)
						sprintf(buffer, "%d", file_pipes[0]);
						// execute pipe4 and send a arg, buffer(string)
						execl("pipe4", "pipe4", buffer, (char *)0);
						exit(EXIT_FAILURE);
				}
				else{
						// send some_data using file_pipes[1]
						data_processed = write(file_pipes[1], some_data, strlen(some_data));
						printf("%d - wrote %d bytes\n", getpid(), data_processed);
				}
		}
		exit(EXIT_SUCCESS);
}
