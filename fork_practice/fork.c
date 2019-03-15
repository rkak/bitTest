#include <stdio.h>
#include <unistd.h>	// fork()
#include <sys/types.h>	// some types

int global = 10;

int main(void){
		pid_t pid;
		int i = 20;

		if((pid = fork()) == 0){
				global += 10;
				i += 10;
		} else{
				global += 100;
				i += 100;

		}
		printf("global = %d, i = %d\n", global, i);

		return 0;

}
