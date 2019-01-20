#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/

typedef int TElement;

typedef struct Cellule{

	TElement donnee;

	struct Cellule *suivant;

}*liste;

/* primitives pour les liste chaînées */

TElement valCellule(liste l){

	return l->donnee;

}

liste suivCellule(liste l){

	return l->suivant;

}



/* 		<<<<<<<	LES PILE >>>>>>>			*/

/*		{ représentation Chaînées }		*/


typedef liste pile;

/* primitives pour les piles */

TElement sommetPile(pile p){

	return p->donnee;

}

liste suivant(pile p){

	return p->suivant;

}

/*1) initialiser une pile*/

liste initPile(){

	return NULL;

}

/*2) teste si une pile est vide ou pas */

int videPile(liste l){

	return l == NULL;

}

/*3) afficher une pile */

void affPile(pile p){


	while(!videPile(p)){

		printf("%d\t",sommetPile(p));
	
		p = suivant(p);

	}

	printf("\n");

}

/*4) determiner la hauteur d'une pile */

int hauteur(pile p){

  int lg = 0;

	while(!videPile(p)){

		lg = lg+1;

		p = suivant(p);

	}

	return lg;

}

/* 5) empiler "ajouter une valeur au sommet d'une pile" */

void empile(TElement X,pile *p){

pile cel;

	//création de la cellule

	cel = (pile) malloc (sizeof(struct Cellule));

	//remplissage de la cellule

	cel->donnee = X;

	//chainage

	cel->suivant = *p;

	*p = cel ;

}

/*6) depiler "retirer la valeur au sommet de la pile */

void depile(pile *p){

pile cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *p;

	//realisation du chainage

	*p = suivant(*p);

	//liberation de la memeoire de la premier cellule

	free(cel);

}

/*7) generation aleatoirement d'une pile */

pile generPile(){

 int n,i;

 TElement X;

 pile p;

 p = initPile();

 printf("rentrez le nombre d'element \n");

 scanf("%d",&n);

	for(i=0 ; i<n ; i++){

		X = rand()%10;

		empile(X,&p);

        }

	return p;

}

/* 		<<<<<<<	LES FILES >>>>>>>			*/

/*		{ représentation Chaînées }		*/

typedef struct {


  liste tete;

  liste queue;


}file;

/* premitives pour les Files */

liste teteFile(file f){

	return f.tete;

}

liste queueFile(file f){

	return f.queue;

}

/*1) initialiser une file */

file initFile(){

 file f;

 f.tete = f.queue = NULL;

	return f;

}

/*2) teste si une file est vide ou pas */

int videFile(file f){

	return ( f.tete == NULL );

}

/*3) determoner la valeur du sommet de la file*/

TElement sommetFile(file f){

	return valCellule(teteFile(f));

}

/*4) emfiler "ajouter une valeur donnée en queue de la file" */

void emfile(TElement X,file *f){

 liste cel;

 cel = (liste) malloc (sizeof(struct Cellule));

 cel->donnee = X;

 cel->suivant = NULL;

	if( videFile(*f) )

		f->tete = f->queue = cel ;

	else{

		(f->queue)->suivant = cel;

		f->queue = cel;

	}

}

/*5) defiler "retire la valeur en tete de la file" */

void defile(file *f){

 liste ff;

 ff = f->tete;

 f->tete = suivCellule(f->tete);

 free(ff);

}

/*6) afficher les element de la file */

void affFile(file f){


	while( !videFile(f) ){

		printf("%d\t",sommetFile(f));
	
		(f.tete) = (suivCellule(f.tete));

	}

	printf("\n");

}

/*7) genere aléatoirement une file */

file generFile(){

 int n,i;

 TElement X;

 file f;

 f = initFile();

 printf("rentrez le nombre d'element \n");

 scanf("%d",&n);

	for(i=0 ; i<n ; i++){

		X = rand()%10;

		emfile(X,&f);

        }

	return f;

}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/

int main (void) {


srand(time(0));

pile p1;

file f1;

p1 = generPile();

f1 = generFile();

affPile(p1);

affFile(f1);

defile(&f1);

depile(&p1);

affPile(p1);

affFile(f1);

emfile(21,&f1);

empile(12,&p1);

affPile(p1);

affFile(f1);

return 0;

}
