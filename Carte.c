#include "Uno.h"

// paquet rangé:
int initialisationPaquet(Carte_t *paquetCarte[]){

	int i;
	int nombre = 0;
	int codeCouleur = 0;
	/* code couleur :
	0 = rouge
	1 = bleu
	2 = vert
	3 = jaune
	4 = sans couleur
	*/

	
	for(i=0; i<=3; i++){
		Carte_t *carte = malloc(sizeof(*carte));
		carte->nbr= nombre;
		carte->couleur= codeCouleur;
		codeCouleur++;
		carte->spe = false;
		paquetCarte[i]= carte;
	}

	int acc=1;
	nombre = 1;
	codeCouleur = 0;
	int a = 5; // index
	
	while(nombre <= 12){
		while(acc<=4){
			for(i; i<= a ; i++){
				Carte_t *carte = malloc(sizeof(*carte));
				carte->nbr = nombre;
				carte->couleur = codeCouleur;
				paquetCarte[i]= carte;
			}
			a+=2;
			acc++;
			codeCouleur++;
		}
		nombre++;
		acc=1;
		codeCouleur = 0;
	}

	acc=1;
	a+=2;

	while(nombre <=14){
		while(acc<=2){
			for (i;i<=a;i++){
				Carte_t *carte = malloc(sizeof(*carte));
				carte->nbr = nombre;
				carte->couleur = 4;
				paquetCarte[i] = carte;
			}
			a+=4;
			acc++;
			nombre++;
		}
	}
}

//paquet melange:
void Melange(Carte_t *paquetCarte[]){
	initialisationPaquet(paquetCarte);
	srand(time(NULL));
	for (int i = 0; i < 500 ; ++i)
	{
		int Index1 = (rand() % 108);
		int Index2 = (rand() % 108);
		Carte_t *tmp1 = paquetCarte[Index1];
		Carte_t *tmp2 = paquetCarte[Index2];
		paquetCarte[Index1] = tmp2;
		paquetCarte[Index2] = tmp1;
	
	}
}


void empiler(Pile *pile, Carte_t *paquetCarte[], int index){
	Carte_t *nouvelleCarte = malloc(sizeof(*nouvelleCarte));

	nouvelleCarte = paquetCarte[index];
	if(pile == NULL){
		pile->premiereCarte = nouvelleCarte;
	}
	else{
		nouvelleCarte->suivante = pile->premiereCarte;
		pile->premiereCarte = nouvelleCarte;
	}
}

