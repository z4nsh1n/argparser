
#test: and -o test must be the same
test: main.c 
	gcc main.c -lm  -o test

run: test
	./test -v -i 22 -n 3.1415 -f "test.txt"
