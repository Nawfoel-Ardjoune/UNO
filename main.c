#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Uno.h"


int main (){
	Carte_t *paquetCarte[108];
	Pile *pile;
	Melange(paquetCarte);
	for (int i = 0; i <= 108; ++i)
	{
		printf("%d \n",paquetCarte[i]->nbr);
	}
	

	for (int i = 0; i <= 108; ++i)
	{
		empiler(pile,paquetCarte,i);
	}
	
	return 0;
}
