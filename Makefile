c=gcc
op=-Wall -Wextra -lpthread

all : exe

exe : segment.o exemple.c
	@$(c) -o exemple.o -c exemple.c $(op)
	@$(c) -o exe segment.o exemple.o $(op)

segment.o : segment.c segment.h
	@$(c) -o segment.o -c segment.c $(op)
	
clean :
	@rm -f exe
	rm -f segment.o exemple.o cli.o exe.o cli exemple exe
