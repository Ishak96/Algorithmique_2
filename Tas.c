#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define MAXT 100

/*	<<<<<<<Structure des Tas>>>>>>>	*/

typedef int TElement;

typedef struct {

	int tailleMax;

	int taille;

	TElement *tab;

}Tas;

int tailleMaxTas(Tas t){

	return t.tailleMax;

}

int tailleTas(Tas t){

	return t.taille;

}

/*	<<<<<<<<<Primetives syr les Tas>>>>>>>>>	*/

/*1)initialise un Tas*/

void initTas(Tas *t){

	(*t).taille = 0;

}

/*2)allocation de memoir */

Tas allocMemTas(int tMax){

Tas t;

	t.tailleMax = tMax;

	initTas(&t);

	t.tab = (TElement*) malloc (tMax*sizeof(TElement));

	return t;

}


/*3)tester si un Tas est vide ou pas */

int videTas(Tas t){

	return (t.taille == 0);

}

/*4)tester si un Tas est plein ou pas */

int pleinTas(Tas t){

	return( tailleTas(t) >= tailleMaxTas(t) );

}

/*5)liberation de la memeoire allouer */

void libMemTas(Tas *t){

	free((*t).tab);

}

/*6)tester si un noeud est vide ou pas */

int videNoeud(int n,Tas t){

	return( n >= tailleTas(t) );

}

/*7)tester l'existance d'un noeud dans Tas*/

int existNoeud(int n,Tas t){

	return ( n < tailleTas(t) );

}

/*8)retourne la donne associée a un noeud*/

/* !!!!!!! PréCondition : existNoeud(n,a); !!!!!!!!!!*/

TElement donneeNoeud(int n,Tas t){

	return( t.tab[n] );

}

/*9)retourn le fils gauche d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsG(int n,Tas t){

	return ( 2*n+1 );

}

/*10)retourn le fils droit d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsD(int n,Tas t){

	return ( 2*n+2 );

}

/*11)retourn le pére d'un noeud donnee */

/* !!!!!!!!! PréCondition : n >0 !!!!!!!!! */

int pere(int n,Tas t){

	return ( (n-1)/2 );

}

/*12)effectue un parcour en profondeur dans l'ordre préfixe */

/*	parourPréfixe	*/

void parcourPrefixe(int r,Tas t){

	if( !videNoeud(r,t) ){	

		printf("%d ",donneeNoeud(r,t));

		parcourPrefixe( filsG(r,t) , t);

		parcourPrefixe( filsD(r,t) , t);

	}

}

/*13)effectue un parcour en profondeur dans l'ordre infixe */

/*	parourInfixe	*/

void parcourInfixe(int r,Tas t){

	if( !videNoeud(r,t) ){	

		parcourPrefixe( filsG(r,t) , t);

		printf("%d ",donneeNoeud(r,t));

		parcourPrefixe( filsD(r,t) , t);

	}

}

/*14)effectue un parcour en profondeur dans l'ordre postfixe */

/*	parourPostfixe	*/

void parcourPostfixe(int r,Tas t){

	if( !videNoeud(r,t) ){	

		parcourPrefixe( filsG(r,t) , t);

		parcourPrefixe( filsD(r,t) , t);

		printf("%d ",donneeNoeud(r,t));

	}

}

/*15)parcour en largeur et chaque niveau de l'Tas doit etre affich sur une ligne differente */

void parcourLargeur(Tas t){

int n,nbNoeud,nbNoeudParNiveau,nd;

 	n = tailleTas(t);

 	nbNoeud = 0;

 	nbNoeudParNiveau = 1;

	for(nd = 0 ; nd < n ; nd++){

		printf("%d	",donneeNoeud(nd,t));

		nbNoeud++;

		if( nbNoeud == nbNoeudParNiveau){

			printf("\n");

			nbNoeudParNiveau *= 2;

			nbNoeud = 0;


		}

	}


}

/*16)insertion d'un element dans Tas */

void inserEltTas(TElement X, Tas *t){

int n,p,dp;

 n =tailleTas(*t); 

 p = pere(n,*t); 

 dp = donneeNoeud(p,*t);

	while( n > 0 && dp < X){

		(*t).tab[n] = dp ;

		n = p;

		p = pere(n,*t);

		dp = donneeNoeud(p,*t);

	}

	(*t).tab[n] = X;

	(*t).taille = tailleTas(*t)+1;

}


/*17)generation d'un Tas */

Tas generTas(int n){

Tas t;
TElement elt;

	t = allocMemTas(n);

	for( int i = 0 ; i < n ; i++){

		printf("rentrez l'element a insere\n");

		scanf("%d",&elt);

		inserEltTas(elt,&t);
	}

	return t;

}

/*18)determiner l'element maximal dans un tas */

TElement maxTas(Tas t){

	return ( donneeNoeud(0,t) );

}

/*19)Supprimer un element dans un Tas donnee */

void suppTas(Tas *t){

int n,fg,fd,echange,fMax;
TElement elt;

 //placer le dernier noeud a la racine et suppression du dernier noeud

	(*t).tab[0] = (*t).tab[tailleTas(*t)-1];

	(*t).taille = tailleTas(*t)-1;

 //echange avec le plus grand fils jusqu'a l'obtention d'un Tas 

	n = 0; 

	elt = donneeNoeud(n,*t);

	fg = filsG(n,*t);

	echange = 1;	

	while( echange && existNoeud(fg,*t) ){

		fd = filsD(n,*t);

		fMax = fg;

		//verification de l'existance du 

			if(existNoeud(fd,*t) &&  donneeNoeud(fd,*t) > donneeNoeud(fMax,*t) ){

				fMax = fd;
			}
			if( elt >= donneeNoeud(fMax,*t) ){

				echange = 0;

			}else{

				(*t).tab[n] = donneeNoeud(fMax,*t);

				n = fMax;

				fg = filsG(n,*t);
			}


	}

	(*t).tab[n] = elt;

}

/*20) verifier si un tableux donne est un tas */

int estTas(int n, TElement *tab){

Tas t;
int dn;

	dn = n-1;

	while( dn > 0 && tab[dn] > tab[pere(dn,t)] ){

		dn = dn-1;

	}

	return ( dn == 0);

}

/*	application : tri d'un tableux par un Tas */

/*1)transformation d'un tableux en tas */

void trieTabTas(int n, TElement *tab){

Tas t;

	//allocation memoire 

	t = allocMemTas(n);

	//construction du TasMax

	for(int i = 0 ; i < n ; i++){


		inserEltTas(tab[i],&t);		


	}

	//retirer les elements un a un esl les placer dans le tableau en commençant par la fi


	for(int i = n-1 ; i >= 0 ; i--){

		tab[i] =  maxTas(t);

		suppTas(&t);
		
	}

	free(t.tab);

} 

/*	<<<<<<PROGRAMME PRINCIPALE>>>>>>	*/

int main (void) {

Tas a,a1;
int tab[MAXT] = {0,3,8,4,7,3,1,12};

 a = generTas(7);

 printf("\n\n\n");

 parcourLargeur(a);

 printf("parcour Préfixe : \n");

 parcourPrefixe(0,a);

 printf("\n\n");

 printf("\ntrie du tableu : \n");

 trieTabTas(8,tab);

 for(int i = 0 ; i < 8 ; i++){

	printf("%d ",tab[i]);

 }

 printf("\n");

return 0;
}
