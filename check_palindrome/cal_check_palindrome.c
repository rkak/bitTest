#include <stdio.h>	// printf(), fgets()
#include <string.h>	// strlen(), memset()

// #define DEBUG

int swap(char *a, char *b);

int main(int argc, char *argv[]){
	char word[52];	
	int len;
	int start, end;
	int result_cnt = 0;
	int once_ins = 0;	// if once instrument is used once, it set 1.

	memset(word, 0, sizeof(word));

	if(argc >= 2){
		strcpy(word, argv[1]);
		len = strlen(word);
	} else{
			fgets(word, sizeof(word), stdin);
			len = strlen(word);
			len--;	// word get a enter
			word[len] = '\0';
	}

#ifdef DEBUG
	printf("argv : %s\nword : %s\n", argv[1], word);
#endif

	len = strlen(word);

#ifdef DEBUG
	printf("len : %d\n", len);
#endif

	if(len < 1 + 1){	// The word has a digit
			result_cnt = 0;
			printf("%d\n", result_cnt);
			return 0;
	}
	start = 0;		// start index end = len - 1;	// end index
	end = len - 1;

	while(start < end){
		if(word[start] != word[end]){
				if(start != end - 1 &&word[start] == word[end-1] && once_ins == 0){
						swap(&word[end], &word[end-1]);
						once_ins = 1;
				}
				else{
						word[end] = word[start];
				}
				result_cnt++;
		}
		start++;
		end--;
	}

	printf("%d\n", result_cnt);

#ifdef DEBUG
	printf("%s\n", word);
#endif

	return 0;
}

int swap(char *a, char *b){
		char tmp;
		tmp = *a;
		*a = *b;
		*b = tmp;
}
