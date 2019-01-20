#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define MAX_NB 100

typedef int TElement;

/*	<<<<<<< STRUCTURE DES ARBRES BINAIRES >>>>>>>		*/

typedef struct noeud{

	TElement donnee;

	struct noeud * filsG;

	struct noeud * filsD;

}*ArbreOrdonne;

/*1)primetive des ARBRES BINAIRE */

TElement donnee(ArbreOrdonne a){

	return a->donnee;

}

ArbreOrdonne filsG(ArbreOrdonne a){

	return a->filsG;

}

ArbreOrdonne filsD(ArbreOrdonne a){

	return a->filsD;

}

/* 		<<<<<<<	LES FILES >>>>>>>			*/

/*		{ représentation Chaînées }		*/

typedef struct Cellule{

	ArbreOrdonne donnee;

	struct Cellule *suivant;

}*liste;

/* primitives pour les liste chaînées */

ArbreOrdonne valCellule(liste l){

	return l->donnee;

}

liste suivCellule(liste l){

	return l->suivant;

}

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

ArbreOrdonne sommetFile(file f){

	return valCellule(teteFile(f));

}

/*4) emfiler "ajouter une valeur donnée en queue de la file" */

void emfile(ArbreOrdonne X,file *f){

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

/*	<<<<< FIN FILE ARBREORDONNEE >>>>>	*/ 


/*2)les differents fonction utiles vu en CM */

/*a)initialiser un Arbre */

ArbreOrdonne initArbre(){

	return NULL;

}

/*b)teste si un Arbre Binaire est vide ou pas */

int videArbre(ArbreOrdonne a){

	return (a == NULL);

}

/*c)creation d'une feuille */

ArbreOrdonne creatFeuille(TElement X){

 ArbreOrdonne f;

 f = (ArbreOrdonne) malloc (sizeof(struct noeud));

 f->donnee = X;

 f->filsG = f->filsD = NULL;

 return f;

}

/*d)creation d'un noeud */

ArbreOrdonne creatNoeud(TElement X, ArbreOrdonne fG, ArbreOrdonne fD){

 ArbreOrdonne nd;

 nd = (ArbreOrdonne) malloc (sizeof(struct noeud));

 nd->donnee = X;

 nd->filsG = fG;

 nd->filsD = fD;

 return nd;

}

/*e)les parcours en profondeur*/

/*Parcour Préfixe*/	/*(RGD)*/

void parcourPrefixe(ArbreOrdonne a){

	if(!videArbre(a)){

		printf("%d ",donnee(a));

		parcourPrefixe(a->filsG);

		parcourPrefixe(a->filsD);

	}

}

/*Parcour Infixe*/	/*(GRD)*/

void parcourInfixeTrie(ArbreOrdonne a,int *i,TElement *tab){

	if(!videArbre(a)){

		parcourInfixeTrie((a->filsG),i,tab);

		tab[*i] = donnee(a);

		*i = *i+1;

		parcourInfixeTrie((a->filsD),i,tab);

	}

}

void parcourInfixe(ArbreOrdonne a){

	if(!videArbre(a)){

		parcourInfixe((a->filsG));

		printf("%d ",donnee(a));

		parcourInfixe((a->filsD));

	}

}

/*Parcour Postfixe*/	/*(GDR)*/

void parcourPostfixe(ArbreOrdonne a){

	if(!videArbre(a)){

		parcourPostfixe(a->filsG);

		parcourPostfixe(a->filsD);

		printf("%d ",donnee(a));

	}

}

/*f) Determiner la taille d'un arbre binaire*/

int tailleArbre(ArbreOrdonne a){

	if(videArbre(a)){

		return 0;

	}else{

		return 1 + tailleArbre(filsG(a)) + tailleArbre(filsD(a)) ;

	}

}

/*g) Determiner le nombre de feuilles dans un arbre binaire*/

/*la fonction est feuille qui teste si un noeud est une feuille ou pas */

int estFeuille(ArbreOrdonne a){

	return videArbre(filsG(a)) && videArbre(filsD(a));

}

int nbFeuille(ArbreOrdonne a){

	if(videArbre(a))

		return 0;

	else{

		if(estFeuille(a))

			return 1;

		else 

			return nbFeuille(filsG(a)) + nbFeuille(filsD(a));


	}

}

/*3)recherche d'un element donnee dans un arbre donnee */

int rechercheEltArbreOrdonne(ArbreOrdonne a ,TElement X){

	if(videArbre(a))

		return 0;

	else

		if(donnee(a) == X)

			return 1;

		else
		
			if(donnee(a) < X)
			
				return rechercheEltArbreOrdonne(filsD(a),X);

			else

				return rechercheEltArbreOrdonne(filsG(a),X);

}

/*4)insrtion d'un element donnee dans un arbre donnee */

void inserEltArbreOrdonne(ArbreOrdonne *a,TElement X){


	if(videArbre(*a))

		*a = creatFeuille(X);

	else

		if( donnee(*a) > X)

			inserEltArbreOrdonne( (&((*a)->filsG)),X );

		else

			inserEltArbreOrdonne( (&((*a)->filsD)),X );

}

/*5)determiner le minimum dans un arbre binaire de recherche ordonnee */

TElement minArbreOrdonnee(ArbreOrdonne a){

 ArbreOrdonne fg;

 fg = filsG(a);

	if(videArbre(fg))

		return donnee(a);

	else

		return minArbreOrdonnee(fg);

}

TElement maxArbreOrdonnee(ArbreOrdonne a){

 ArbreOrdonne fd;

 fd = filsD(a);

	if(videArbre(fd))

		return donnee(a);

	else

		return maxArbreOrdonnee(fd);

}

/*6)determiner l'adresse du noeud qui contient le minimum dans un arbre binaire de recherche */

ArbreOrdonne adresseminArbreOrdonnee(ArbreOrdonne a){


 ArbreOrdonne fg;

 fg = filsG(a);

	if(videArbre(fg))

		return a;

	else

		return adresseminArbreOrdonnee(fg);

}

/*7)supprimer le noeud racine dans un arbre binaire ordonner */

void spprimerRacineArbreOrdonnee(ArbreOrdonne *a){

 ArbreOrdonne plusPetiteNdFD,fd,fg,aa;

	if(estFeuille(*a)){

		free(*a);

		*a = NULL;

	}else{

		aa = *a;

		fg = filsG(*a);

		fd = filsD(*a);

		if(!videArbre(fd)){

			plusPetiteNdFD = adresseminArbreOrdonnee(fd);

			plusPetiteNdFD->filsG = fg;

			*a = fd;

		}else

			*a = fg;

		free(aa);

	}

}

void suppArbre(ArbreOrdonne *a){

	if(!videArbre(*a)){

		suppArbre(& ((*a)->filsG) );

		suppArbre(& ((*a)->filsD) );

		free(*a);

		*a=NULL;

	}

}

/*8)supprimer un element donnee d'un arbre binaire de recherche donnee */

/*******************	preCondition rechercheEltArbreOrdonne(a,elt) = vrai	*******************/

void spprimerEltArbreOrdonnee(ArbreOrdonne *a,TElement X){

	if(!videArbre(*a))

		if(donnee(*a) == X)

			spprimerRacineArbreOrdonnee(a);

		else

			if(donnee(*a) > X)

				spprimerEltArbreOrdonnee( (&((*a)->filsG)),X);

			else

				spprimerEltArbreOrdonnee( (&((*a)->filsD)),X);

}

/* parcour en largeur */

void parcourLanrgeur(ArbreOrdonne a){

 file f;

 f = initFile();

 ArbreOrdonne fg,fd,sf;

 emfile(a,&f);

	while(!videFile(f)){

		sf = sommetFile(f);

		defile(&f);

		fg = filsG(sf);

		fd = filsD(sf);

		printf("%d ",donnee(sf));

		if(!videArbre(fg))

			emfile(fg,&f);

		if(!videArbre(fd))

			emfile(fd,&f);


	}

	printf("\n");

}

/************ generation d'un arbre binaire ordonnee ***********/

ArbreOrdonne generArbreBinaireOrdonnee(int nbFeuille){

 TElement X;

 ArbreOrdonne a; 

 a = initArbre();

	for(int i=0 ; i < nbFeuille ; i++){

		X = rand()%10;

		inserEltArbreOrdonne(&a,X);

	}

 return a;

}

/*9)trier un tableau composé de n elements (entier) en utilisant un arbre binaire Ordonnee */

void trieTableauArbreOrdonnee(int n,TElement *tab){

 ArbreOrdonne a;

 a = initArbre();

	for(int i=0 ; i<n ; i++){

		inserEltArbreOrdonne(&a,tab[i]);	

	}

	n = 0;

	parcourInfixeTrie(a,&n,tab);

	suppArbre(&a);

}

/*10)l'intersection de deux arbre binaire ordonne donnee*/

void fusionArbreOrdonne(ArbreOrdonne *a1 , ArbreOrdonne *a2){

 file f;

 f = initFile();

 ArbreOrdonne fg,fd,sf;

 emfile(*a2,&f);

	while(!videFile(f)){

		sf = sommetFile(f);

		defile(&f);

		fg = filsG(sf);

		fd = filsD(sf);

		inserEltArbreOrdonne(a1 , donnee(sf));

		if(!videArbre(fg))

			emfile(fg,&f);

		if(!videArbre(fd))

			emfile(fd,&f);


	}

	suppArbre(a2);

}

/*	<<<<<<< PROGRAMME PRINCIPALE >>>>>>> */

int main (void) {

 ArbreOrdonne a,a1,a2;

 srand(time(NULL));

 a1 = generArbreBinaireOrdonnee(3);

 a2 = generArbreBinaireOrdonnee(3);

 parcourLanrgeur(a1);

 parcourLanrgeur(a2);

 printf("l'intersection des deux arbre : \n");

 fusionArbreOrdonne(&a1,&a2);

 parcourLanrgeur(a1);

 printf("\n");

 printf("---------------------------------------------------------------\n");

 TElement tab[MAX_NB] = {17,7,19,5,2,8,13,20,29,11,4,33,9,6,12,16,4,3,18}; 

 TElement tab1[MAX_NB] = {5,13,2,7,0,3};

 a = initArbre();

 for(int i=0 ; i<6 ; i++){

	inserEltArbreOrdonne(&a,tab1[i]);

 }

 parcourLanrgeur(a);

 printf("le minimum dans l'arbre est : %d\n",minArbreOrdonnee(a));

 printf("le maximum dans l'arbre es : %d\n",maxArbreOrdonnee(a));

 spprimerRacineArbreOrdonnee(&a);

 printf("suppresion du noeud racine\n");

 parcourLanrgeur(a);

 spprimerEltArbreOrdonnee(&a,0);

 printf("suppresion du 0 : \n");

 parcourLanrgeur(a);

 parcourInfixe(a);

 printf("\n");

 printf("---------------------------------------------------------------\n");

 trieTableauArbreOrdonnee(19,tab);

 for(int i=0 ; i<19 ; i++){

	printf("%d ",tab[i]); 

 }

 printf("\n");

return 0;
}
