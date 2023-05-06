
#test: and -o test must be the same
test: main.c 
	gcc main.c -lm  -o test

run: test
	./test -v -b 12 -f "test.txt"
