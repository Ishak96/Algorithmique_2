#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;

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

/*d)creation d'un noeud */

Arbre creatNoeud(TElement X, Arbre fG, Arbre fD){

 Arbre nd;

 nd = (Arbre) malloc (sizeof(struct noeud));

 nd->donnee = X;

 nd->filsG = fG;

 nd->filsD = fD;

 return nd;
}

/*e)les parcours en profondeur*/

/*Parcour Préfixe*/	/*(RGD)*/

void parcourPrefixe(Arbre a){

	if(!videArbre(a)){

		printf("%d\t",donnee(a));

		parcourPrefixe(a->filsG);

		parcourPrefixe(a->filsD);

	}

}

/*Parcour Infixe*/	/*(GRD)*/

void parcourInfixe(Arbre a){

	if(!videArbre(a)){

		parcourInfixe(a->filsG);

		printf("%d\t",donnee(a));

		parcourInfixe(a->filsD);

	}

}

/*Parcour Postfixe*/	/*(GDR)*/

void parcourPostfixe(Arbre a){

	if(!videArbre(a)){

		parcourPostfixe(a->filsG);

		parcourPostfixe(a->filsD);

		printf("%d\t",donnee(a));

	}

}

/*f) Determiner la taille d'un arbre binaire*/

int tailleArbre(Arbre a){

	if(videArbre(a)){

		return 0;

	}else{

		return 1 + tailleArbre(filsG(a)) + tailleArbre(filsD(a)) ;

	}

}

/*g) Determiner le nombre de feuilles dans un arbre binaire*/

/*la fonction est feuille qui teste si un noeud est une feuille ou pas */

int estFeuille(Arbre a){

	return videArbre(filsG(a)) && videArbre(filsD(a));

}

int nbFeuille(Arbre a){

	if(videArbre(a))

		return 0;

	else{

		if(estFeuille(a))

			return 1;

		else 

			return nbFeuille(filsG(a)) + nbFeuille(filsD(a));


	}

}

/*h)recherche d'un element dans un arbre binaire */

int rechercheArbre(TElement X, Arbre a){

	if(videArbre(a))

		return 0;

	else{

		if(donnee(a) == X)

			return 1;

		else

			return rechercheArbre(X,filsG(a)) || rechercheArbre(X,filsD(a)) ;

	}

}

/*i)hauteur d'un arbre binaire donnee */

/*on a besoin de la fonction qui compare deux entier */

int Max(int a, int b){

 int max = a;

	if(a<b)

		max = b;

	return max;
}

int hauteurArbre(Arbre a){

 int HfG,HfD;

	if(videArbre(a) || estFeuille(a))

		return 0;

	else{

		HfG = 1+hauteurArbre(filsG(a));	
	
		HfD = 1+hauteurArbre(filsD(a));

		return Max(HfG,HfD);
	}
}

/*j)suppression d'un Arbre Binaire*/

void suppArbre(Arbre *a){

	if(!videArbre(*a)){

		suppArbre(& ((*a)->filsG) );

		suppArbre(& ((*a)->filsD) );

		free(*a);

		*a=NULL;

	}

}

/*3) Determiner le plus petit elements dans un arbre binaire*/

TElement plusPetit(Arbre a){

 Arbre fG,fD;

 TElement min,minD,minG;

	if(estFeuille(a))

		return donnee(a);

	else{

		min = donnee(a);

		fG = filsG(a);

		if(!videArbre(fG)){

			minG = plusPetit(fG);

			if(min>minG)

				min = minG;

		}

		fD = filsD(a);

		if(!videArbre(fD)){

			minD = plusPetit(fD);

			if(min>minD)

				min = minD;

		}

	}

	return min;

}

/*4) Determiner la somme des donnees attaches au différents noeuds d'un arbre binaire donne */

TElement somme(Arbre a){

	if(videArbre(a))

		return 0;

	else

		return ( donnee(a) + somme(filsG(a)) + somme(filsD(a)) );

}

/* 		<<<<<<<	LES FILES >>>>>>>			*/

/*		{ représentation Chaînées }		*/

typedef struct Cellule1{

	Arbre donnee1;

	struct Cellule1 *suivant1;

}*liste1;

/* primitives pour les liste chaînées */

Arbre valCellule1(liste1 l){

	return l->donnee1;

}

liste1 suivCellule1(liste1 l){

	return l->suivant1;

}

typedef struct {


  liste1 tete;

  liste1 queue;


}file;

/* premitives pour les Files */

liste1 teteFile(file f){

	return f.tete;

}

liste1 queueFile(file f){

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

Arbre sommetFile(file f){

	return valCellule1(teteFile(f));

}

/*4) emfiler "ajouter une valeur donnée en queue de la file" */

void emfile(Arbre X,file *f){

 liste1 cel;

 cel = (liste1) malloc (sizeof(struct Cellule1));

 cel->donnee1 = X;

 cel->suivant1 = NULL;

	if( videFile(*f) )

		f->tete = f->queue = cel ;

	else{

		(f->queue)->suivant1 = cel;

		f->queue = cel;

	}

}

/*5) defiler "retire la valeur en tete de la file" */

void defile(file *f){

 liste1 ff;

 ff = f->tete;

 f->tete = suivCellule1(f->tete);

 free(ff);

}

/*	<<<<< FIN FILE ARBRE >>>>>	*/ 

/* 		<<<<<<<	LES PILE >>>>>>>			*/

/*		{ représentation Chaînées }		*/

typedef struct Cellule{

	Arbre donnee;

	struct Cellule *suivant;

}*liste;

/* primitives pour les liste chaînées */

Arbre valCellule(liste l){

	return l->donnee;

}

liste suivCellule(liste l){

	return l->suivant;

}

typedef liste pile;

/* primitives pour les piles */

Arbre sommetPile(pile p){

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

int videPile(pile p){

	return p == NULL;

}

/* 5) empiler "ajouter une valeur au sommet d'une pile" */

void empile(Arbre X,pile *p){

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

/*	<<<<<< FIN PILE ARBRE >>>>>>	*/

/*5)creation de l'arbre binaire*/

Arbre creatArbre(){

 Arbre f0,nd13,f3,f4,f1,nd6,f2,f7,nd9,nd8,nd5;

 f0 = creatFeuille(0);

 nd13 = creatNoeud(13,NULL,f0);

 f3 = creatFeuille(3);

 f4 = creatFeuille(4);

 f1 = creatFeuille(1);

 nd6 = creatNoeud(6,nd13,f3);

 f2 = creatFeuille(2);

 f7 = creatFeuille(7);

 nd9 = creatNoeud(9,f4,f1);

 nd8 = creatNoeud(8,nd6,f2);

 nd5 = creatNoeud(5,f7,nd9);

	return creatNoeud(10,nd8,nd5);

}

void parcourLanrgeur(Arbre a){

 file f;

 f = initFile();

 Arbre fg,fd,sf;

 emfile(a,&f);

	while(!videFile(f)){

		sf = sommetFile(f);

		defile(&f);

		fg = filsG(sf);

		fd = filsD(sf);

		printf("%d\t",donnee(sf));

		if(!videArbre(fg))

			emfile(fg,&f);

		if(!videArbre(fd))

			emfile(fd,&f);


	}

	printf("\n");

}

void parcourPrefixeIt(Arbre a){

 pile p;

 p = initPile();

 Arbre fg,fd,sp;

 empile(a,&p);


	while(!videPile(p)){

		sp = sommetPile(p);

		depile(&p);

		fg = filsG(sp);

		fd = filsD(sp);

		printf("%d\t",donnee(sp));

		if(!videArbre(fd))

			empile(fd,&p);

		if(!videArbre(fg))

			empile(fg,&p);


	}

	printf("\n");

}

/*	<<<<<<PROGRAMME PRINCIPALE>>>>>>	*/

int main (void) {

 Arbre a ;

 int r;

 a = creatArbre();

 printf("parcourPrefixe : \n");

 parcourPrefixe(a);

 printf("\n");

 printf("parcourInfixe : \n");

 parcourInfixe(a);

 printf("\n");

 printf("parcourPostfixe : \n");

 parcourPostfixe(a);

 printf("\n");

 printf("le plus petit elements de l'arbre est : %d\n",plusPetit(a));

 printf("la somme des elemeents present dans l'arbre est : %d\n",somme(a));

 printf("la taille de l'arbre est : %d\n",tailleArbre(a));

 printf("la hauteur de l'arbre est : %d\n",hauteurArbre(a));

 printf("le nombres de feuilles dans l'arbre est : %d\n",nbFeuille(a));

 r = rechercheArbre(3,a);

 if( r == 1 )

 	printf("le 3 ce trouve dans l'arbre \n");

 else

	printf("le 3 ne ce trouve pas dans l'arbre\n");


    printf("Parcours Largeur : \n");
	parcourLanrgeur(a);


	printf("Parcours parcourPrefixeIt : \n");
 	parcourPrefixeIt(a);
	
	suppArbre(&a);

	if(!videArbre(a)){

	 	printf("Parcours parcourInfixer : \n");
	 	parcourInfixe(a);

	}else

		printf("l'arbre est vide\n");

return 0;
}
