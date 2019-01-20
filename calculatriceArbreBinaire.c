#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define ZERO '0'

#define NEUF '9'

#define MAX_NB 1000

typedef char TElement;

int parenthese(char car){

	return car == '(';

}

int separateur(char car){

	return car == ' ' || car== ',' ;

}

int chiffre(char car){

	return car >= ZERO && car <= NEUF;

}

int operateur(char car){

	return car == '+' || car == '-' || car == '*' || car == '/';

}

int parentheseFermente(char car){

	return car == ')';

}

int finChar(char car){

	return (car == '\0');

}

/*	<<<<<<< STRUCTURE DES ARBRES BINAIRES >>>>>>>		*/

typedef struct noeud{

	TElement donnee;

	struct noeud * filsG;

	struct noeud * filsD;

}*Arbre;

/*1)primetive des ARBRES BINAIRE */

TElement donnee(Arbre a){

	return a->donnee;

}

Arbre filsG(Arbre a){

	return a->filsG;

}

Arbre filsD(Arbre a){

	return a->filsD;

}

/*2)les differents fonction utiles vu en CM */

/*a)initialiser un Arbre */

Arbre initArbre(){

	return NULL;

}

/*b)teste si un Arbre Binaire est vide ou pas */

int videArbre(Arbre a){

	return (a == NULL);

}

/*c)creation d'une feuille */

Arbre creatFeuille(TElement X){

 Arbre f;

 f = (Arbre) malloc (sizeof(struct noeud));

 f->donnee = X;

 f->filsG = f->filsD = NULL;

 return f;

}

int estFeuille(Arbre a){

	return videArbre(filsG(a)) && videArbre(filsD(a));

}

/*d)creation d'un noeud */

Arbre creatNoeud(TElement X, Arbre fG, Arbre fD){

 Arbre nd;

 nd = (Arbre) malloc (sizeof(struct noeud));

 nd->donnee = X;

 nd->filsG = fG;

 nd->filsD = fD;

 return nd;

}

/*Parcour Postfixe*/	/*(GDR)*/

void parcourPostfixe(Arbre a){

	

	if(!videArbre(a)){

		parcourPostfixe(a->filsG);

		parcourPostfixe(a->filsD);

		printf("%c ",donnee(a));

	}

}

/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/

typedef char TElement;

typedef struct Cellule{

	TElement donnee;

	struct Cellule *suivant;

}*listeCar;

typedef struct CelluleA{

	Arbre donnee;

	struct CelluleA *suivant;

}*listeArb;

typedef struct CelluleF{

	float donnee;

	struct CelluleF *suivant;

}*listeReel;

/* primitives pour les liste chaînées */

TElement valCellule(listeCar l){

	return l->donnee;

}

listeCar suivCellule(listeCar l){

	return l->suivant;

}

/***********************************************/
Arbre valCelluleArb(listeArb l){

	return l->donnee;

}

listeArb suivCelluleArb(listeArb l){

	return l->suivant;

}

/********************************************/

/* 		<<<<<<<	LES PILE CARACTERE >>>>>>>			*/

/*		{ représentation Chaînées }		*/


typedef listeCar pileCarac;

/* primitives pour les piles */

TElement sommetPileCarac(pileCarac p){

	return p->donnee;

}

pileCarac  suivantCarac(pileCarac p){

	return p->suivant;

}

/*1) initialiser une pile*/

pileCarac initPileCarac(){

	return NULL;

}

/*2) teste si une pile est vide ou pas */

int videPileCarac(pileCarac p){

	return p == NULL;

}

/* 3) empiler "ajouter une valeur au sommet d'une pile" */

void empileCarac(TElement X, pileCarac *p){

pileCarac cel;

	//création de la cellule

	cel = (pileCarac) malloc (sizeof(pileCarac));

	//remplissage de la cellule

	cel->donnee = X;

	//chainage

	cel->suivant = *p;

	*p = cel ;

}

/*4) depiler "retirer la valeur au sommet de la pile */

void depileCarac(pileCarac *p){

pileCarac cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *p;

	//realisation du chainage

	*p = suivantCarac(*p);

	//liberation de la memeoire de la premier cellule

	free(cel);

}

/* 		<<<<<<<	LES PILE ARBRE>>>>>>>			*/

/*		{ représentation Chaînées }		*/


typedef listeArb pileArbre;

/* primitives pour les piles */

Arbre sommetPileArbre(pileArbre p){

	return p->donnee;

}

pileArbre suivantArbre(pileArbre p){

	return p->suivant;

}

/*1) initialiser une pile*/

pileArbre initPileArbre(){

	return NULL;

}

/*2) teste si une pile est vide ou pas */

int videPileArbre(pileArbre p){

	return p == NULL;

}

/* 3) empiler "ajouter une valeur au sommet d'une pile" */

void empileArbre(Arbre X,pileArbre *p){

pileArbre cel;

	//création de la cellule

	cel = (pileArbre) malloc ( sizeof(pileArbre) );

	//remplissage de la cellule

	cel->donnee = X;

	//chainage

	cel->suivant = *p;

	*p = cel;

}

/*4) depiler "retirer la valeur au sommet de la pile */

void depileArbre(pileArbre *p){

pileArbre cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *p;

	//realisation du chainage

	*p = suivantArbre(*p);

	//liberation de la memeoire de la premier cellule

	free(cel);

}

/*	<<<<<<< APPLICATION >>>>>>>	*/

float operand(char car){

	return car - '0';

}

float eval(char car , float OperandG , float OperandD){

	switch( car ){

		case '+' : return (OperandG + OperandD) ;

				break;

		case '-' : return (OperandG - OperandD);

				break;

		case '*' : return (OperandG * OperandD);

				break;

		case '/' : if(OperandG != 0){

				return (OperandG / OperandD);

			   }else{

				printf(" E : on peut pas diviser par ZERO\n");

			   }

				break;

		default : printf("E : aucune operation \n"); 

	}

}


Arbre transformExpArbre(char *exp){

 pileCarac pc;

 pileArbre pa;

 int Erreur,i;

 char car,oper;

 Arbre fg,fd,f,nd;

 pc = initPileCarac();

 pa = initPileArbre();

 i = 0;

 car = exp[i];

 Erreur = 0;

	while( !finChar(car) && !Erreur ){

		if( parenthese(car) ||  separateur(car) ){

				i++;

		}else

			if( chiffre(car) ){


				f = creatFeuille(car);	

	
				empileArbre(f,&pa);

				i++;


			}else

				if( operateur(car) ){

					empileCarac(car,&pc);

					i++;

				}else

					if( parentheseFermente(car) ){

						fd = sommetPileArbre(pa);

						depileArbre(&pa);

						fg = sommetPileArbre(pa);

						depileArbre(&pa);

						oper = sommetPileCarac(pc);

						depileCarac(&pc);

						nd = creatNoeud(oper,fg,fd);

						empileArbre(nd ,&pa);

						i++;

					}else

						Erreur = 1;	

			car  = exp[i];

	}

	return sommetPileArbre(pa);

}

float evalExpPostFixe(Arbre a){

 float vopG,vopD;

 char oper;

	if( estFeuille(a) )

		return operand(donnee(a));	

	else{

		vopG = evalExpPostFixe(filsG(a));

		vopD = evalExpPostFixe(filsD(a));

		oper = donnee(a);

		return eval(oper,vopG,vopD);

	}

}

/*	<<<<<< PROGRAMME PRINCIPALE >>>>>>	*/

int main (void) {

 char exp[MAX_NB] ="(((5*7)+(9*4))/(2-7))";

 Arbre a;			

 a = transformExpArbre(exp);

 printf("parcoursPostFixee = ");

 parcourPostfixe(a);

 printf("\n");

 printf("%s = %f.\n",exp,evalExpPostFixe(a));

return 0;
}
