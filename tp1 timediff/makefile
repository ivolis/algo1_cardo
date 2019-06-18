CFLAGS= -Wall -ansi -pedantic -O2
cc=gcc

all: time_difference

time_difference:main.o errors.o dates.o
	$(cc) $(CFLAGS) -o time_difference main.o errors.o dates.o

main.o:main.h main.c errors.h dates.h TYPES.h
	$(cc) $(CFLAGS) -o main.o -c main.c

errors.o:errors.h errors.c TYPES.h lang.h
	$(cc) $(CFLAGS)	-o errors.o -c errors.c

dates.o:dates.h dates.c TYPES.h
	$(cc) $(CFLAGS)	-o dates.o -c dates.c

clean:
	rm *.o
