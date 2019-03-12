all:cal_check_palindrome

cal_check_palindrome:cal_check_palindrome.o
	gcc -o $@ $^

cal_check_palindrome.o:cal_check_palindrome.c
	gcc -c $?

clean:
	rm -rf cal_check_palindrome cal_*.o
