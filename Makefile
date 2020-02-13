CC=gcc
SRC= un.c
OBJ=$(SRC:.c=.o)
FLAGS=-Wall

Uno:    $(OBJ) un.h
	$(CC) -o $@ $(OBJ)
%.o:	%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o *~ core