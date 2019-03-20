#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[]){
		int data_processed;
		char buffer[BUFSIZ + 1];
		int file_descriptor;
		memset(buffer, '\0', sizeof(buffer));

		// assign file_descriptor by argv[1]. it comes from pipe3
		sscanf(argv[1], "%d", &file_descriptor);

		// read from file_descriptor to buffer
		data_processed = read(file_descriptor, buffer, BUFSIZ);

		printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
		exit(EXIT_SUCCESS);
}
