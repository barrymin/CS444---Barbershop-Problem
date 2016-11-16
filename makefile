default: all
all:
	gcc -g -o barber barber.c -lpthread

clean:
	rm barber

