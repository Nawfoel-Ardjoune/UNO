CC=gcc
SRC= Uno.c Carte.c Joueur.c Pile.c 
OBJ=$(SRC:.c=.o) 
FLAGS=-Wall

Uno.exe : $(OBJ) Uno.h
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o *~ core
