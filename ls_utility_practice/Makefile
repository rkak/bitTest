all:myls

myls:myls.o
	gcc -o $@ $^

myls.o:myls.c
	gcc -c $?

clean:
	rm -rf myls myls*.o
