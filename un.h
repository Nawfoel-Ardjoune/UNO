#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<time.h>
struct Carte{
	int color;
	int type;
	int num;
	int value;
/* 	colors : 0.rouge ; 1.bleu ; 2.vert ; 3.jaune. 
types :	0.simple ; 1.draw 2 ; 2.reverse ; 3.skip, 4.draw 4, 5.joker.
*/
};typedef struct Carte carte_t;

struct liste{
	int top;
	carte_t * array;
};typedef struct liste liste_t;

struct Player{
	int num_player;
	int points;
	liste_t main;
};typedef struct Player player_t;

struct liste_joueurs{
	int nb_joueurs;
	player_t * roster;
};typedef struct liste_joueurs lj_t;

player_t new_player(int num_player);
lj_t creat_roster(lj_t * rost);
carte_t new_carte(int color, int type, int num, int value);
void push(liste_t *liste, carte_t carte);
carte_t pop(liste_t *liste);
void affiche_carte(carte_t carte);
void affiche_all(liste_t *liste);
void init(liste_t *pile);
void deleteall(liste_t *liste);
void delete_roster(lj_t * roster);
void melange(liste_t * liste, int indice);
void distribution(lj_t * liste_player, liste_t * pioche);
int test(carte_t from,carte_t to );
int verif(player_t player, liste_t defausse);
void choix(player_t *player, liste_t * defausse);
void activation(liste_t *pioche, liste_t *defausse, lj_t *roster, int *indice , int *riv);