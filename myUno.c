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

node_t * delete(node_t *liste){
	if(liste == NULL){ 
        return NULL;
    } 
    if (liste->next == NULL) { 
        free(liste); 
        return NULL; 
    }else{
        node_t *todelete = liste->next;
        liste->next = liste->next->next;
        free(todelete);
    }
}

node_t * deleteall(node_t *liste){
	if (liste == NULL){ 
        return NULL;
    } 
    if (liste->next == NULL){ 
        free(liste); 
        return NULL; 
    } 
	while(liste->next !=NULL ){
		node_t *todelete = liste;
        liste = liste->next;
        free(todelete);
        printf(".");
	}
	printf(" Done");
	return NULL;
}

int my_equal(carte_t a, carte_t b){
	if(a.type == b.type && a.num == b.num && a.color == b.color){
		return 1;
	}else{
		return 0;
	}
}

node_t* delete_one(node_t *liste, carte_t carte) { 
    if (liste == NULL){ 
        return NULL; 
    }
    if (liste->next == NULL){ 
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

// node_t* delete_one(node_t * liste, carte_t *carte){
// 	if(liste->next == NULL){
// 		exit(EXIT_FAILLURE);
// 	}else{
// 		node_t *todelete = liste->next;
// 		while(todelete->next !=NULL ){
// 			todelete->next = todelete->next->next;
// 			if(my_equal(todelete->carte,carte)){
// 				detele
// 			}
// 		}
// 	}
// 	return liste;
// }


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
		add_node(pile, new_node(i,5,0,50));
		add_node(pile, new_node(i,4,0,50));
	}
}

void affich_node(node_t * liste){
	if (liste == NULL){
		exit(EXIT_FAILURE);
	}
	node_t *me = liste->next;

	while(me != NULL){
		affiche_carte(&me->carte);
		me = me->next;
	}
}


int main(){
	node_t * first;
	node_t * test =new_node(0,0,0,20);
	// //printf("num=%d, color=%d, type=%d, value%d\n",test->carte.num,test->carte.color,test->carte.type,test->carte.value);
	// test->carte.num=1;
	// test->carte.color=2;
	// test->carte.type=3;
	// test->carte.value=100;
	// test->next=NULL;
	// first->next=test;
	add_node(first,new_node(0,0,0,10));
	add_node(first,new_node(0,0,0,20));
	add_node(first,new_node(0,0,0,30));
	//init(first);
	//affich_node(first);
	//delete_one(first, test->carte);
	affich_node(first);
	deleteall(first);
	//printf("num=%d, color=%d, type=%d, value%d\n",test->carte.num,test->carte.color,test->carte.type,test->carte.value);
	// free(first->next);
	//free(first);
	return 0;
}