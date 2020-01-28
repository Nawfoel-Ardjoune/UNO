#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Carte{// les cartes ont une valeur, une couleur, un type et leurs nombre
	int nbr;
	int couleur;
	int valeur;
	bool spe;
};
typedef Carte Carte_t;

 struct Pile{
	Carte_t carte;
	Carte_t *suivante;
	int top = -1;
};
typedef Pile Pile_t;

void push(Pile_t pile, Carte_t carte);
Carte_t pop(Pile_t pile);
void empty(Pile_t pile);

