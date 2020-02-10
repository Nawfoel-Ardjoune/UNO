#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

/*===================================TO DO================================
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
	int num_player;
	int points;
	node_t * main;
	int nbcarte;
};typedef struct Player player_t;

static carte_t pioche[108];
static carte_t defausse[108];
static int top_pioche = 0;
static int top_defausse = 0;
static int indice;


//node_t * distribution(node_t * main);
void add_node(node_t * first, node_t * n);

int set_nbPlayer(void){
	int nbjoueurs;
	int good=0;
	do{
		printf("Combien y'a t-il de joueurs ?\n");
		scanf("%d", &nbjoueurs);
		if(nbjoueurs<11 && nbjoueurs>1){	
			good = 1;
		}else{
			printf("Il y a eu une erreur\n");
			good=0;
		}
	}while(good!=1);
	return nbjoueurs;
}

player_t * new_player(void){
	player_t *new =malloc(1*sizeof(new));
	assert(new);
	new->num_player=indice;
	indice++;
	//distribution(new->main);
	return new;
}

player_t * new_roster(player_t roster[],int nbj){
	int i;
	for(i=0;i<nbj;i++){
		roster[i] = *new_player();
	}
	return roster;
}

node_t * new_node(int color, int type, int num, int value){
	node_t *n =malloc(1*sizeof*n);
	assert(n);
	n->carte.value=value;
	n->carte.type=type;
	n->carte.num=num;
	n->carte.color=color;
	n->next=NULL;
	return n;
}

void add_node(node_t * first, node_t * n){
	n->next = first->next;
	first->next = n;
}

// node_t * distribution(node_t * main){
// 	int num = rand();
// 	int i=0;
// 	for(i=0;i<7;i++){
// 		num = rand() % top_pioche;
// 		add_node(main,&pioche[top_pioche]);
// 	}
// 	return main;
// }


void delete(node_t *here){
	if(here == NULL){ 
        exit(0);
    } 
    if (here->next == NULL) { 
        free(here);  
    }else{
        node_t *todelete = here->next;
        here->next = here->next->next;
        free(todelete);
    }
}

void deleteall(node_t *liste){
	node_t * next;
	while(liste->next !=NULL){
		next=liste->next;
		liste->next=liste->next->next;
		free(next);
        printf(".");
	}
	free(liste->next);
	printf(" Done");
}

int my_equal(carte_t a, carte_t b){
	if(a.type == b.type && a.num == b.num && a.color == b.color){
		return 1;
	}else{
		return 0;
	}
}

node_t * delete_one(node_t *liste, carte_t carte) { 
    if(liste == NULL){ 
        return NULL; 
    }
    if(liste->next == NULL){ 
        free(liste); 
        return NULL; 
    } 
  
    node_t *slow_ptr = liste; 
    node_t *fast_ptr = liste; 
  
    node_t *prev;
    while (fast_ptr != NULL && fast_ptr->next != NULL) 
    { 
        fast_ptr = fast_ptr->next->next; 
        prev = slow_ptr; 
        slow_ptr = slow_ptr->next;
        if(my_equal(slow_ptr->carte,carte)){
    		prev->next = slow_ptr->next; 
   	 		free(slow_ptr); 
  			return liste;    	
        } 
    } 
    return liste;
} 

node_t * transit(node_t * from, node_t * to, carte_t carte){
	if(from == NULL){
		printf("Il n'y à pas de carte\n");
		exit(1);
	}
	node_t *cursor = from;
	while(cursor->next !=NULL){
		if(my_equal(cursor->next->carte, carte)){
			add_node(to,cursor->next);
			delete(cursor);
		}
		cursor=cursor->next;
	}
	return from;
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

void init(node_t* pile){
	int i,j,k,l,m,n;
	for(i=0;i<4;i++){
		add_node(pile,new_node(i,0,0,20));
		for(j=1;j<10;j++){
			for(k=0;k<2;k++){
				add_node(pile, new_node(i,0,j,20));
			}
		}
		for(n=1;n<4;n++){
			for(m=0;m<2;m++){
				add_node(pile, new_node(i,n,0,20));
			}
		}
		add_node(pile, new_node(0,5,0,50));
		add_node(pile, new_node(0,4,0,50));
	}
}

void affich_node(node_t * liste){
	node_t *me = liste->next;

	while(me->next != NULL){
		affiche_carte(&me->carte);
		me = me->next;
	}
	affiche_carte(&me->carte);
}

void affich_pioche(){
	int i=0;
	for(i=0;i<108;i++){
		affiche_carte(&pioche[i]);
	}
}

void mise_pioche(node_t *liste){
	node_t * cursor=NULL;
	cursor=liste->next;
	while(cursor->next!=NULL){
		pioche[top_pioche]=cursor->carte;
		cursor=cursor->next;
		top_pioche++;
	}
}

int main(){
	node_t * first;
	first->next =NULL;
	// node_t * test =new_node(0,0,2,20);
	// printf("num=%d, color=%d, type=%d, value%d\n",test->carte.num,test->carte.color,test->carte.type,test->carte.value);
	// test->carte.num=1;
	// test->carte.color=2;
	// test->carte.type=3;
	// test->carte.value=100;
	// test->next=NULL;
	// first->next=test;
	// add_node(first,new_node(0,0,1,10));
	// add_node(first,new_node(0,0,2,20));
	// add_node(first,new_node(0,0,3,30));
	init(first);
	mise_pioche(first);
	// affich_node(first);
	// delete_one(first, test->carte);
	affich_pioche();
	deleteall(first);
	top_pioche=0;
	// reset();
	return 0;
}