#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

/*===================================TO DO================================
	-Il faut changer les structure de ma pile pour pouvoir y retirer des element sans laisser de trou.
	-Il faut encore pouvoir faire le vrais main "Jouer" une fonction qui tente de produire un jeu de A a Z.
	-Il faudra donc changer les fonctions qui dependent des changement fait precedement.
	-Oubliez pas de faire des test avant vos push et de liberer la mémoire (free).
==========================================================================*/

struct Carte{
	int num;
	int type;
	int color;
	int value;
};typedef struct Carte carte_t;
/* 	colors : 0->rouge ; 1->bleu ; 2->vert ; 3->jaune. 
	types :	0->simple ; 1->draw 2 ; 2->reverse ; 3->skip, 4->draw 4, 5->joker.
*/

struct node{
	carte_t carte;
	struct node* next;
};typedef struct node node_t;

struct Player{
	int num_joueurs;
	int points;
	node_t main;
	int top;
};typedef struct Player player_t;

static carte_t pioche[108];
static carte_t defausse[108];
static int top_pioche = -1;
static int top_defausse = -1;
// void newPlayer(void){
// 	int i=0;
// 	printf("Combien y'a t-il de joueurs ?");
// 	scanf("%d", &nbjoueurs);
// 	for(i=0; i<nbjoueurs; i++){
// 		player_t tmp;
// 		joueurs[i]=tmp;
// 	}
// }


carte_t remove_from_player(player_t player, int indice){
	int i;
	if(indice != ) 
	for(i=indice;i<player.top;i++){
		player.hand[i]=player.hand[i+1];
	}
}

void affiche_carte(carte_t *carte){
	if(carte->type==0 && carte->color==0 ){
			printf("Rouge : %d\n",carte->num);
		}else if(carte->type==0 && carte->color==1 ){
			printf("Bleu : %d\n",carte->num);
		}else if(carte->type==0 && carte->color==2 ){
			printf("Vert : %d\n",carte->num);
		}else if(carte->type==0 && carte->color==3 ){
			printf("Jaune : %d\n",carte->num);
		}
		//les draw +2
		else if(carte->type==1 && carte->color==0 ){
			printf("Rouge : pioche +2\n");
		}else if(carte->type==1 && carte->color==1 ){
			printf("Bleu : pioche +2\n");
		}else if(carte->type==1 && carte->color==2 ){
			printf("Vert : pioche +2\n");
		}else if(carte->type==1 && carte->color==3 ){
			printf("Jaune : pioche +2\n");
		//Les reverse
		}else if(carte->type==2 && carte->color==0 ){
			printf("Rouge : reverse\n");
		}else if(carte->type==2 && carte->color==1 ){
			printf("Bleu : reverse\n");
		}else if(carte->type==2&& carte->color==2 ){
			printf("Vert : reverse\n");
		}else if(carte->type==2 && carte->color==3 ){
			printf("Jaune : reverse\n");
		//Les skip
		}else if(carte->type==3 && carte->color==0 ){
			printf("Rouge : skip\n");
		}else if(carte->type==3 && carte->color==1 ){
			printf("Bleu : skip\n");
		}else if(carte->type==3 && carte->color==2 ){
			printf("Vert : skip\n");
		}else if(carte->type==3 && carte->color==3 ){
			printf("Jaune : skip\n");
		//les jokers et les draw +4	
		}else if(carte->type==4){
			printf("Carte : draw +4\n");
		}else if(carte->type==5){
			printf("Carte : Joker\n");
		}
}

void affiche(pile_t* pile){
	int i=0;
	for (i=0; i<pile->top; i++){//les carte simple
		affiche_carte(&pile->tab[i]);
	}
	//printf("||%d||",i);	
}		

void init(pile_t* pile){
	int i,j,k,l,m,n;
	for(i=0;i<4;i++){
		carte_t zero;
		zero.num =0;
		zero.type=0;
		zero.value=20;
		zero.color=i;
		push(pile, zero);
		for(j=1;j<10;j++){
			for(k=0;k<2;k++){
				carte_t carte;
				carte.num=j;
				carte.type=0;
				carte.value=20;
				carte.color=i;
				push(pile, carte);
			}
		}
		for(n=1;n<4;n++){
			for(m=0;m<2;m++){
				carte_t super;
				super.num=0;
				super.type=n;
				super.value=20;
				super.color=i;
				push(pile, super);
			}
		}
		carte_t joker;
		joker.num =0;
		joker.type=5;
		joker.value=50;
		joker.color=i;
		push(pile, joker);
		carte_t draw;
		draw.num =0;
		draw.type=4;
		draw.value=50;
		draw.color=i;
		push(pile, draw);
	}
}


int main(){
	
	return 0;
}