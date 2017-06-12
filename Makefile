all: filter mysize dircount

filter:
	gcc -Wall -o filter filter.c 
	
dircount:
	gcc -Wall -o dircount dircount.c
	
mysize:
	gcc -Wall -o mysize mysize.c 

clean:
	rm -f filter dircount mysize
