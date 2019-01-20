#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

/*	<<<<<<<Structure des Arbre Parfait>>>>>>>	*/

typedef int TElement;

typedef struct {

	int tailleMax;

	int taille;

	TElement *tab;

}ArbreParfait;

int tailleMaxArbreParfait(ArbreParfait a){

	return a.tailleMax;

}

int tailleArbreParfait(ArbreParfait a){

	return a.taille;

}

/*	<<<<<<<<<Primetives syr les Arbre Parfait>>>>>>>>>	*/

/*1)initialise un arbre parfait*/

void initArbreParfait(ArbreParfait *a){

	(*a).taille = 0;

}

/*2)allocation de memoir */

ArbreParfait allocMemArbreParfait(int tMax){

	ArbreParfait a;

	a.tailleMax = tMax;

	initArbreParfait(&a);

	a.tab = (TElement*) malloc (tMax*sizeof(TElement));

	return a;

}

/*3)tester si un ArbreParfait est vide ou pas */

int videArbreParfait(ArbreParfait a){

	return (a.taille == 0);

}

/*4)tester si un ArbreParfait est plein ou pas */

int pleinArbreParfait(ArbreParfait a){

	return( tailleArbreParfait(a) >= tailleMaxArbreParfait(a) );

}

/*5)liberation de la memeoire allouer */

void libMemArbreParfait(ArbreParfait *a){

	free((*a).tab);

}

/*6)tester si un noeud est vide ou pas */

int videNoeud(int n,ArbreParfait a){

	return( n >= tailleArbreParfait(a) );

}

/*7)tester l'existance d'un noeud dans ArbreParfait*/

int existNoeud(int n,ArbreParfait a){

	return ( n < tailleArbreParfait(a) );

}

/*8)retourne la donne associée a un noeud*/

/* !!!!!!! PréCondition : existNoeud(n,a); !!!!!!!!!!*/

TElement donneeNoeud(int n,ArbreParfait a){

	return( a.tab[n] );

}

/*9)retourn le fils gauche d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsG(int n,ArbreParfait a){

	return ( 2*n+1 );

}

/*10)retourn le fils droit d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsD(int n,ArbreParfait  a){

	return ( 2*n+2 );

}

/*11)retourn le pére d'un noeud donnee */

/* !!!!!!!!! PréCondition : n >0 !!!!!!!!! */

TElement pere(int n,ArbreParfait a){

	return ( (n-1)/2 );

}

/*12)effectue un parcour en profondeur dans l'ordre préfixe */

/*	parourPréfixe	*/

void parcourPrefixe(int r,ArbreParfait a){

	if( !videNoeud(r,a) ){	

		printf("%d ",donneeNoeud(r,a));

		parcourPrefixe( filsG(r,a) , a );

		parcourPrefixe( filsD(r,a) , a);

	}

}

/*13)effectue un parcour en profondeur dans l'ordre infixe */

/*	parourInfixe	*/

void parcourInfixe(int r,ArbreParfait a){

	if( !videNoeud(r,a) ){	

		parcourInfixe( filsG(r,a) , a );

		printf("%d ",donneeNoeud(r,a));

		parcourInfixe( filsD(r,a) , a);

	}

}

/*14)effectue un parcour en profondeur dans l'ordre postfixe */

/*	parourPostfixe	*/

void parcourPostfixe(int r,ArbreParfait a){

	if( !videNoeud(r,a) ){	

		parcourPostfixe( filsG(r,a) , a );

		parcourPostfixe( filsD(r,a) , a);

		printf("%d ",donneeNoeud(r,a));

	}

}

/*15)parcour en largeur et chaque niveau de l'arbre parfait doit etre affich sur une ligne differente */

void parcourLargeur(ArbreParfait a ){

int n,NbNd,nbNdParNiv;

 n = tailleArbreParfait(a);

 NbNd = 0;

 nbNdParNiv = 1;


	for(int nd = 0 ; nd < n ; nd++){ 

		printf("%d ",donneeNoeud(nd,a));

		NbNd += 1;

		if( nbNdParNiv == NbNd ){

			printf("\n");

			nbNdParNiv *= 2;

			NbNd = 0;

		}
	}

	printf("\n");

}

/*16)insertion d'un element donnee dans un arbre parfait */

/*!!!!!!!!!!! precondition !pleinArbreParfait(a) !!!!!!!!!!!!*/

void inserEltArbreParfait(TElement X ,ArbreParfait *a){

	(*a).tab[tailleArbreParfait(*a)] = X;

	(*a).taille = tailleArbreParfait(*a)+1;

}

/*17)generation d'un arbre parfait */

ArbreParfait generArbreParfait(int tMax){

ArbreParfait a;

TElement X;

 a = allocMemArbreParfait(tMax);

	for(int i = 0 ; i<tMax ; i++){

		printf("rentrez le %d-iéme Noeud : \n",i);

		scanf("%d",&X);

		inserEltArbreParfait(X,&a);

	}

	return a;
}

/*	<<<<<<PROGRAMME PRINCIPALE>>>>>>	*/

int main (void) {

ArbreParfait a;

 a = generArbreParfait(6);

 printf("\n\n\n\n");

 printf("parcour en largeur : \n");

 parcourLargeur(a);

 printf("parcourPrefixe : \n");

 parcourPrefixe(0,a);

 printf("\nparcourInfixe : \n");

 parcourInfixe(0,a);

 printf("\nparcourPostfixe : \n");

 parcourPostfixe(0,a);

 printf("\n");

return 0;
}
