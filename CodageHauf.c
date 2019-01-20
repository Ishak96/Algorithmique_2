#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

int indefinie;

/*	<<<<<<<Structure des TasMin>>>>>>>	*/

typedef int TElement;

typedef struct {

		int tailleMax;

		int taille;

		TElement *tab;

	}TasMin;

int tailleMaxTasMin(TasMin t){

	return t.tailleMax;

}

int tailleTasMin(TasMin t){

	return t.taille;

}

/*	<<<<<<<<<Primetives syr les TasMin>>>>>>>>>	*/

/*0)allocation memeoir d'un tableau d'entier */

int *allocTab(int nMax){

int *tab;

	tab = (int *) malloc (nMax*sizeof(int));

	if(tab==NULL){

		printf("\n pb alloc Mem 1 \n");
		exit(1);
	}

	return tab;

}

void affTab(int n, int *tab){
int i;

	for(i=0; i<n; i++)
		printf("%d ", tab[i]);
	printf("\n");
}

/*1)initialise un TasMin*/

void initTasMin(TasMin *t){

	(*t).taille = 0;

}

/*2)allocation de memoir */


TasMin allocMemTasMin(int tMax){

TasMin t;

	t.tailleMax = tMax;

	t.tab = (TElement*) malloc (tMax*sizeof(TElement));

	if(t.tab==NULL){

		printf("\n pb alloc Mem 1 \n");
		exit(1);
	}

	return t;

}

/*5)liberation de la memeoire allouer */

void libMemTasMin( TasMin *tm){

	free(tm->tab);

	tm->tab=NULL;
}

/*3)tester si un TasMin est vide ou pas */

int videTasMin(TasMin t){

	return (t.taille == 0);

}

/*4)tester si un TasMin est plein ou pas */

int pleinTasMin(TasMin t){

	return( tailleTasMin(t) >= tailleMaxTasMin(t) );

}

/*6)tester si un noeud nd est vide ou pas */

int videNoeud(int nd,TasMin t){

	return( nd >= tailleTasMin(t) );

}

/*7)tester l'existance d'un noeud nd dans TasMin*/

int existNoeud(int nd,TasMin t){

	return ( nd < tailleTasMin(t) );

}

/*8)retourne la donne associée a un noeud nd*/

/* !!!!!!! PréCondition : existNoeud(n,a); !!!!!!!!!!*/

TElement donneeNoeud(int nd,TasMin t){

	return( t.tab[nd] );

}

/*9)retourn le fils gauche d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsG(int n,TasMin t){

	return ( 2*n+1 );

}

/*10)retourn le fils droit d'un noeud donnee */

/* !!!!!!!! PréCondition : n >0 !!!!!!!!!! */

int filsD(int n,TasMin t){

	return ( 2*n+2 );

}

/*11)retourn le pére d'un noeud donnee */

/* !!!!!!!!! PréCondition : n >0 !!!!!!!!! */

int pere(int n,TasMin t){

	return ( (n-1)/2 );

}

/*12)effectue un parcour en profondeur dans l'ordre préfixe */

/*	parourPréfixe	*/

void parcourPrefixe(int r,TasMin t){

	if( !videNoeud(r,t) ){	

		printf("%d ",donneeNoeud(r,t));

		parcourPrefixe( filsG(r,t) , t);

		parcourPrefixe( filsD(r,t) , t);

	}

}

/*13)effectue un parcour en profondeur dans l'ordre infixe */

/*	parourInfixe	*/

void parcourInfixe(int r,TasMin t){

	if( !videNoeud(r,t) ){	

		parcourPrefixe( filsG(r,t) , t);

		printf("%d ",donneeNoeud(r,t));

		parcourPrefixe( filsD(r,t) , t);

	}

}

/*14)effectue un parcour en profondeur dans l'ordre postfixe */

/*	parourPostfixe	*/

void parcourPostfixe(int r,TasMin t){

	if( !videNoeud(r,t) ){	

		parcourPrefixe( filsG(r,t) , t);

		parcourPrefixe( filsD(r,t) , t);

		printf("%d ",donneeNoeud(r,t));

	}

}

/*15)parcour en largeur et chaque niveau de l'TasMin doit etre affich sur une ligne differente */

void parcourLargeur(TasMin t){

int n,nbNoeud,nbNoeudParNiveau,nd;

 	n = tailleTasMin(t);

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

/*16)insertion d'un element dans TasMin */

void inserEltTasMin(TElement X, TasMin *t, int *freq){

int n,p,dp;


	n =tailleTasMin(*t); 

	p = pere(n,*t); 

	dp = donneeNoeud(p,*t);

	while( n > 0 && freq[dp] > freq[X]){

		(*t).tab[n] = dp ;

		n = p;

		p = pere(n,*t);

		dp = donneeNoeud(p,*t);

	}

	(*t).tab[n] = X;

	(*t).taille = tailleTasMin(*t)+1;

}

/*18)determiner l'element maximal dans un TasMin */

TElement minTasMin(TasMin t){

	return ( donneeNoeud(0,t) );

}

/*19)Supprimer un element dans un TasMin donnee */

void suppTasMin(TasMin *t, int *freq){

int dn, n,fg,fd,echange,fMin;
TElement elt;

 //placer le dernier noeud a la racine et suppression du dernier noeud

	dn = tailleTasMin(*t)-1;
	(*t).tab[0] = donneeNoeud(dn, *t);	//(*t).tab[dn];
	(*t).taille = dn;

 //echange avec le plus grand fils jusqu'a l'obtention d'un TasMin 

	n = 0; 

	elt = donneeNoeud(n,*t);

	fg = filsG(n,*t);

	echange = 1;	

	while( echange && existNoeud(fg,*t) ){

		fd = filsD(n,*t);

		fMin = fg;

		//verification de l'existance du 

		if(existNoeud(fd,*t) &&  freq[donneeNoeud(fd,*t)] < freq[donneeNoeud(fMin,*t)] ){

			fMin = fd;
		}
		if( freq[elt] <= freq[donneeNoeud(fMin,*t)] ){

			echange = 0;

		}else{

			(*t).tab[n] = donneeNoeud(fMin,*t);

			n = fMin;

			fg = filsG(n,*t);
		}
	}

	(*t).tab[n] = elt;

}

int creatArbreHuff(int nbCarAlph, int nbCarFreq, int *freq,  int *pere, int *filsG, int *filsD){

TasMin tm;
int racine;
int c, c1,c2, m;


    //construction du TasMin
	
	tm = allocMemTasMin(nbCarFreq);
	initTasMin(&tm);

    //les caractére freq son insere dans le Tas

	for(c = 0 ; c < nbCarAlph ; c++){

		if(freq[c] > 0 ){

			inserEltTasMin(c, &tm, freq);
			filsG[c]=indefinie;
			filsD[c]=indefinie;
		}

	}


    //Construction de l'arbre = construction des noeuds interne

    //on extrais du TasMin les caractere de freq Minimale une nouvelle noeud dont la freq est la somme des freq est insere dans le Tas

	m = nbCarAlph+(nbCarFreq-1);

	for(c = nbCarAlph ; c <m  ; c++ ){

		c1 = minTasMin(tm);

		suppTasMin(&tm,freq);

		c2 = minTasMin(tm);

		suppTasMin(&tm, freq);

		//creation du nouvelle noeud

		freq[c] = freq[c1] + freq[c2];

		pere[c2] = c;

		pere[c1] = -c;

		filsG[c] = c1;

		filsD[c] = c2;

		inserEltTasMin(c, &tm, freq);	

	}

	racine = minTasMin(tm);

	suppTasMin(&tm,freq);

	libMemTasMin(&tm);

	pere[racine] = indefinie;
	
	return racine;
}


int calculFreq(int nbCarAlph, char *msg, int *freq){

int nbCarFreq;

	//Init

	//Calcul de la fréquence de chaque caractere

	freq[0]=20;
	freq[1]=10;
	freq[2]=5;
	freq[3]=40;
	freq[4]=25;
	nbCarFreq=5;
	return nbCarFreq;

}

void main(void){
int nbCarAlph, nbCarFreq, taille;
int *freq, *pere, *filsG, *filsD;
int racine;
char *msg; // A définir

	nbCarAlph=5;


	freq = allocTab(2*nbCarAlph-1);

	nbCarFreq=calculFreq(nbCarAlph, msg, freq);

	taille = 2*nbCarFreq-1;
	indefinie = taille;

	pere = allocTab(taille);

	filsG = allocTab(taille);

	filsD = allocTab(taille);

	racine = creatArbreHuff(nbCarAlph, nbCarFreq, freq, pere, filsG, filsD);

	printf("\nracine =%d\n", racine);


	printf("\nPere= ");
	affTab(taille, pere);

	printf("\nfilsG= ");
	affTab(taille, filsG);

	printf("\nfilsD= ");
	affTab(taille, filsD);

}
