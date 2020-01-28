#include "Uno.h"
 /*______________________TO-DO la pile n'est pas encore dynamique_________________*/
 void push(Pile_t pile, Carte_t carte) {
 	++pile.top = carte;
}

 int pop(Pile_t pile) {
 	return pile.top--;
 }

int empty(Pile_t pile) {
	return pile.top < 0;
 }