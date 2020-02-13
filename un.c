#include"un.h"
player_t new_player(int num_player){
	player_t new;
	new.num_player=num_player;
	new.points = 0;
	new.main.top=-1;
	new.main.array=NULL;
	return new;
}

lj_t creat_roster(lj_t * rost){
	int i=0;
	printf("Il y a combien de joueuer ?\n");
	scanf("%d",&rost->nb_joueurs);
	rost->roster = malloc(rost->nb_joueurs*sizeof(player_t));
	assert(rost->roster);
	for(i=0;i<rost->nb_joueurs;i++){
		rost->roster[i]=new_player(i);
	}
	printf("=========================\nIl y a donc %d joueurs\n=========================\n",rost->nb_joueurs);
	return *rost;
}

carte_t new_carte(int color, int type, int num, int value){
	carte_t new;
	new.color=color;
	new.type=type;
	new.num=num;
	new.value=value;
	return new;
}

void push(liste_t *liste, carte_t carte){
	if(liste->top < 0){
		liste->top++;
		liste->array = malloc(1*sizeof(carte));
		assert(liste->array);
		liste->array[liste->top]=carte;
	}else if(liste->top>=0){
		liste->top++;
		liste->array = realloc(liste->array, (liste->top) * sizeof(carte));
		assert(liste->array);
		liste->array[liste->top]=carte;
	}
}

carte_t pop(liste_t *liste){
	printf(" start pop ");
	carte_t tmp;
	if(liste->top == 0){
		tmp.color=liste->array[0].color;
		tmp.type=liste->array[0].type;
		tmp.num=liste->array[0].num;
		tmp.value=liste->array[0].value;
		liste->array = NULL;
		liste->top--;
	}else if(liste->top>0){
		tmp.color=liste->array[liste->top].color;
		tmp.type=liste->array[liste->top].type;
		tmp.num=liste->array[liste->top].num;
		tmp.value=liste->array[liste->top].value;
		liste->array = realloc(liste->array, (liste->top - 1)*sizeof(tmp));
		assert(liste->array);
		liste->top--;
	}else{
		printf(" exit pop\n");
		exit(1);
	}
	printf(" return pop\n");
	return tmp;
} 

void affiche_carte(carte_t carte){
	if(carte.type==0 && carte.color==0 ){
		printf("Rouge : %d\n",carte.num);
	}else if(carte.type==0 && carte.color==1 ){
		printf("Bleu : %d\n",carte.num);
	}else if(carte.type==0 && carte.color==2 ){
		printf("Vert : %d\n",carte.num);
	}else if(carte.type==0 && carte.color==3 ){
		printf("Jaune : %d\n",carte.num);
	}
//les draw +2
	else if(carte.type==1 && carte.color==0 ){
		printf("Rouge : pioche +2\n");
	}else if(carte.type==1 && carte.color==1 ){
		printf("Bleu : pioche +2\n");
	}else if(carte.type==1 && carte.color==2 ){
		printf("Vert : pioche +2\n");
	}else if(carte.type==1 && carte.color==3 ){
		printf("Jaune : pioche +2\n");
//Les reverse
	}else if(carte.type==2 && carte.color==0 ){
		printf("Rouge : reverse\n");
	}else if(carte.type==2 && carte.color==1 ){
		printf("Bleu : reverse\n");
	}else if(carte.type==2&& carte.color==2 ){
		printf("Vert : reverse\n");
	}else if(carte.type==2 && carte.color==3 ){
		printf("Jaune : reverse\n");
//Les skip
	}else if(carte.type==3 && carte.color==0 ){
		printf("Rouge : skip\n");
	}else if(carte.type==3 && carte.color==1 ){
		printf("Bleu : skip\n");
	}else if(carte.type==3 && carte.color==2 ){
		printf("Vert : skip\n");
	}else if(carte.type==3 && carte.color==3 ){
		printf("Jaune : skip\n");
//les jokers et les draw +4	
	}else if(carte.type==4){
		printf("Carte : draw +4\n");
	}else if(carte.type==5){
		printf("Carte : Joker\n");
	}
}

void affiche_all(liste_t *liste){
	int i =0;
	for(i=0;i<liste->top;i++){
		printf("%d: ",i);
		affiche_carte(liste->array[i]);
	}
}

void init(liste_t *pile){
	int i,j,k,m,n;
	for(i=0;i<4;i++){
		push(pile,new_carte(i,0,0,20));
		for(j=1;j<10;j++){
			for(k=0;k<2;k++){
				push(pile, new_carte(i,0,j,20));
			}
		}
		for(n=1;n<4;n++){
			for(m=0;m<2;m++){
				push(pile, new_carte(i,n,0,20));
			}
		}
		push(pile, new_carte(0,5,0,50));
		push(pile, new_carte(0,4,0,50));
	}
}

void deleteall(liste_t *liste){
	while(liste->top>-1){
		if(liste->top>0){
			liste->array = realloc(liste->array, (liste->top - 1)*sizeof(liste->array[0]));
			assert(liste->array);
			liste->top--;
		}else{
			liste->array = NULL;
			liste->top--;
		}
		printf(".");
	}
	printf(" Done for cardes.\n");
}

void delete_roster(lj_t * roster){
	while(roster->nb_joueurs>-1){
		if(roster->nb_joueurs>0){
			roster->roster = realloc(roster->roster, (roster->nb_joueurs - 1)*sizeof(roster->roster[0]));
			assert(roster->roster);
			roster->nb_joueurs--;
		}else{
			free(roster->roster);
			roster->nb_joueurs--;
		}
		printf("*");
	}
	printf(" Done for roster.\n");
}

void melange(liste_t * liste, int indice){
	int i=0;
	int ra;
	carte_t tmp;
	for(i=0;i<indice;i++){
		tmp=liste->array[i];
		do{
			ra=rand()% liste->top;
		}while(ra == i );
		liste->array[i]=liste->array[ra];
		liste->array[ra]=tmp;
	}
}

void distribution(lj_t * liste_player, liste_t * pioche){
	printf(" start distrib ");
	int i =0;
	int j =0;
	for(i=0;i<liste_player->nb_joueurs;i++){
		for(j=0;j<7;j++){
			printf(" boucle for distrib j ");
			push(&liste_player->roster[i].main,pop(pioche));
		}
	}
	printf(" end distrib\n");
}

int test(carte_t from,carte_t to ){
	if(from.type == 4 || from.type == 5){
		return 1;
	}else if(from.num == to.num || from.color==to.color){
		return 1;
	}else if(from.type == to.type && from.type >0){
		return 1;
	}else{
		return 0;
	}
}

int verif(player_t player, liste_t defausse){
	int i =0;
	for(i=0;i<player.main.top;i++){
		if(test(player.main.array[i],defausse.array[defausse.top])){
			return 1;
		}
	}
	return 0;
}

void choix(player_t *player, liste_t * defausse){
	int num;
	do{
		affiche_all(&player->main);
		printf("Selectionnez votre carte : ");
		scanf("%d",&num);
	}while(!test(player->main.array[num],defausse->array[defausse->top]));
	carte_t tmp;
	tmp = player->main.array[player->main.top];
	player->main.array[player->main.top]=player->main.array[num];
	player->main.array[num]=tmp;
	push(defausse,pop(&player->main));
}
//types :	0.simple ; 1.draw 2 ; 2.reverse ; 3.skip, 4.draw 4, 5.joker.
void activation(liste_t *pioche, liste_t *defausse, lj_t *roster, int *indice , int *riv){
	if(defausse->array[defausse->top].type == 1){
		push(&roster->roster[*indice+1].main,pop(pioche));
		push(&roster->roster[*indice+1].main,pop(pioche));
		(*indice)++;
	}else if(defausse->array[defausse->top].type == 2){
		*riv = 1 ? 0 : 1; 
	}else if(defausse->array[defausse->top].type == 3){
		(*indice)++;
	}else if(defausse->array[defausse->top].type == 4){
		push(&roster->roster[*indice+1].main,pop(pioche));
		push(&roster->roster[*indice+1].main,pop(pioche));
		push(&roster->roster[*indice+1].main,pop(pioche));
		push(&roster->roster[*indice+1].main,pop(pioche));
		(*indice)++;
	}else if(defausse->array[defausse->top].type == 5){
		int new_color;
		printf("choisir une couleur: 0->rouge; 1->bleu; 2->vert; 3->jaune\n");
		scanf("%d\n",&new_color);
		defausse->array[defausse->top].color= new_color;
	}

}

int main(){
	lj_t roster;
	liste_t pioche;
	liste_t defausse;
	int i =0;
	int riv =0;
	int victoire =0;
	creat_roster(&roster);
	init(&pioche);
	melange(&pioche,108);
	melange(&pioche,108);
	//affiche_all(&pioche);
	distribution(&roster,&pioche);
	push(&defausse,pop(&pioche));
	activation(&pioche,&defausse,&roster,&i,&riv);
	//printf("================================================\n");
	do {
		printf("======================================== Au tour du joueur %d ========================================\n",i);
		if( verif(roster.roster[i], defausse)) {
			printf("DEFAUSSE : ");
			affiche_carte(defausse.array[defausse.top]);
			choix(&roster.roster[i], &defausse);
			activation(&pioche,&defausse,&roster,&i,&riv);
			if(roster.roster[i].main.top<0){
				victoire = 1;
				break;
			}
		} else {
			push(&roster.roster[i].main, pop(&pioche));
		}
		if(riv == 0){
			i++;
			if(i>roster.nb_joueurs-1){
				i=0;
			}
		} else {
			i--;
			if(i<0){
				i=roster.nb_joueurs-1;
			}
		}
	} while(!victoire);
	printf("Victoire du joueurs %d",i);
	free(roster.roster);
	roster.nb_joueurs = -1;
	free(pioche.array);
	pioche.top = -1;
	return 0;
}