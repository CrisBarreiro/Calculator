CC:= gcc
CFLAGS:= -lm -g

all: flex.c bison.tab.c
	$(CC) *.c $(CFLAGS) -o calculator
clean:
	rm -f *.o calculator flex.c flex.h bison.tab.c bison.tab.h

flex.c:
	flex --header-file=flex.h --outfile=flex.c flex.l

bison.tab.c:
	bison -d bison.y