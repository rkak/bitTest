#include <stdio.h>	// printf(), fgets()
#include <string.h>	// strlen(), memset()

// #define DEBUG

int swap(char *a, char *b);
int palindrome(char * str, int start, int end);

int main(int argc, char *argv[]){
	char word[52];	
	int len;
	int start, end;

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
			printf("%d\n", 0);
			return 0;
	}
	start = 0;		// start index end = len - 1;	// end index
	end = len - 1;

	int result = palindrome(word, start, end);
	int min = len - 1;

	// need reconstructing
	for(int i=0; i < len/2; i++){
			for(int j=len-1; j>len/2; j--){
					if(min > palindrome(word, i, j) + i)
							min = palindrome(word, i, j) + i;
			}
	}
	printf("%d\n", result);
	printf("min : %d\n", min);
}

// return num -> result_count
// return -1 -> no
int palindrome(char * str, int start, int end){
	int result_cnt = 0;
	int once_ins = 0;	// if once instrument is used once, it set 1.
	while(start < end){
		if(str[start] != str[end]){
				if(start != end - 1 &&str[start] == str[end-1] && once_ins == 0){
						swap(&str[end], &str[end-1]);
						once_ins = 1;
				}
				else{
						str[end] = str[start];
				}
				result_cnt++;
		}
		start++;
		end--;
	}

#ifdef DEBUG
	printf("%s\n", word);
#endif

//	return 0;
	return result_cnt;

}

int swap(char *a, char *b){
		char tmp;
		tmp = *a;
		*a = *b;
		*b = tmp;
}
