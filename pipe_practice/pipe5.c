#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void){
		int data_processed;
		int file_pipes[2];
		const char some_data[] = "123";
		pid_t fork_result;

		if(pipe(file_pipes) == 0){
				fork_result = fork();
				if(fork_result == -1){
						fprintf(stderr, "Fork failure");
						exit(EXIT_FAILURE);
				}
				if(fork_result == 0){
						// close stdin
						close(0);
						// replace stdin to file_pipes[0].
						// dup allocate file_pipes[0] to 0 (this is lowest number in fd of this process)
						dup(file_pipes[0]);
						close(file_pipes[0]);
						close(file_pipes[1]);
						execlp("od", "od", "-c", (char *)0);
						exit(EXIT_FAILURE);
				}
				else{
						// close file_pipes[0] : input
						// input nothing
						close(file_pipes[0]);
						data_processed = write(file_pipes[1], some_data, strlen(some_data));
						close(file_pipes[1]);
						printf("%d - wrote %d bytes\n", (int)getpid(), data_processed);
				}
		}
		exit(EXIT_SUCCESS);
}


