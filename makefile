all:
	gcc -o shell shell.c

run: all
	./shell

clean:
	rm -rf shell