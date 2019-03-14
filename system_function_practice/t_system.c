#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_CMD_LEN 200

int main(int argc, char *argv[]){
		// str for command which is executed on system function
		char str[MAX_CMD_LEN];
		int status;		// result of system function

		for(;;){	// == while(1)
				printf("Command: ");
				fflush(stdout);
				if(fgets(str, MAX_CMD_LEN, stdin) == NULL) // maximum 200 length words can get in it
						break;
				// ok of str
				status = system(str);
				printf("system() returned: status = 0x%04x(%d, %d)\n",
								(unsigned int) status, status >> 8, status & 0xff);
				// instruction about the result
				if(status == -1){
						printf("system");
				} else{
						if(WIFEXITED(status) && WEXITSTATUS(status) == 127)
								printf("(Probably) could not invoke shell\n");
				}
		}

				exit(0);

}
