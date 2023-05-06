
#test: and -o test must be the same
test: argparse.o main.c 
	gcc -Wall -Wextra main.c argparse.c  -o test

#argparse: argparse.o
#	gcc -c argparse.c -o argparse.o

run: test
	./test -v -i 22 -n 3.1415 -f "test.txt"

