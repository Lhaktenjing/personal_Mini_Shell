falsh : falsh.o
	gcc -o falsh falsh.o 

flash.o : flash.c 
	gcc -O -Wall -c falsh.c

clean : 
	rm -f falsh.o falsh
