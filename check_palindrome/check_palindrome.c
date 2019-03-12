#include <stdio.h>	// printf(), fgets()
#include <string.h>	// strlen(), memset()

#define DEBUG

int main(void){
	char word[100];	
	int len;
	int start, end;

	memset(word, 0, sizeof(word));
	fgets(word, sizeof(word), stdin);

#ifdef DEBUG
	printf("input word : %s\n", word);
#endif

	len = strlen(word);

#ifdef DEBUG
	printf("len : %d\n", len);
#endif

	if(len < 1 + 2){
			printf("OK\n");
			return 0;
	}
	start = 0;		// start index
	end = len - 2;	// end index

	while(start < end){
		if(word[start] != word[end]){
			printf("No palindrome word\n");
			return 0;
		}
		start++;
		end--;
	}

	printf("OK\n");
	return 0;
}
