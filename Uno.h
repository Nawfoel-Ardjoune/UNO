#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

typedef Carte Carte_t;
struct Carte{// les cartes ont une valeur, une couleur, un type et leurs nombres
	int nbr;
	int couleur;
	int valeur;
	bool spe;
	Carte_t *suivante;
};

typedef Pile Pile;
 struct Pile{
	Carte_t *premiereCarte;
	int top = -1;
};

typedef struct Joueur Joueur_t;
struct Joueur{
	Pile main;
	int score;
};


int initialisationPaquet();
void Melange();
void empiler();

void push(Pile_t pile, Carte_t carte);
Carte_t pop(Pile_t pile);
void empty(Pile_t pile);

