#include <unistd.h>	// fork()
#include <sys/types.h>	// pid_t
#include <stdio.h>	// setbuf(), stdout
#include <stdlib.h>	// exit()

static void DisplayChar(char *str){
		char *ptr; int c;

		setbuf(stdout, NULL);	// buf off
		for(ptr = str; c = *ptr++;)
				putc(c, stdout);
}

int main(void){
		pid_t pid;
		if( (pid = fork()) < 0)
				perror("fork error");
		else if (pid == 0)
				DisplayChar("output from child\n");
		else
				DisplayChar("output from parent\n");
		exit(0);

}
