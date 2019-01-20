#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;

typedef struct Cellule{

	TElement donnee;

	struct Cellule *suivant;

}*liste;

/*(1)premitive*/

TElement valCellule(liste l){

	return l->donnee;

}

liste suivCellule(liste l){

	return l->suivant;

}

/*(2)initialise une liste*/

liste initListe(){

	return NULL;

}

/*(3) teste si une liste est vide ou non*/

int videListe(liste l){

	return l == NULL;

}

/*(4) afficher les valeurs des differentes cellules de la liste*/

void affListe(liste l){


	while(!videListe(l)){

		printf("%d\t",valCellule(l));
	
		l = suivCellule(l);

	}

	printf("\n");

}

/*(5) determine la longueur d'une liste*/

int longListe(liste l){

  int lg = 0;

	while(!videListe(l)){

		lg = lg+1;

		l = suivCellule(l);

	}

	return lg;

}

/*(6) determminer la plus grand valeur d'une liste*/

TElement valMax(liste l){

TElement vmax;

  vmax = valCellule(l);

  l = suivCellule(l);

	while(!videListe(l)){

		if(vmax < valCellule(l))

			   vmax = valCellule(l);

		l = suivCellule(l);
	}

	return vmax;

}

/*(7) determiner l'adresse de la plus grande valeur d'une liste*/

liste adresseValMax(liste l){

liste admax;

  admax = l;

  l = suivCellule(l);

	while(!videListe(l)){

		if(valCellule(admax) < valCellule(l))

				admax = l;

				l = suivCellule(l);

	}

	return admax;

}

/* Determiner l'adresse de cellule précedente par rapport a une position donnée */

liste celPre(int pos , liste l){

	while(!videListe(l) && pos > 0){


		l = suivCellule(l);

		pos--;

	}

	return l;

} 

/*(8) ajoute d'une valeur en tete de la liste*/

liste inserTete(TElement X,liste *l){

liste cel;

	//création de la cellule

	cel = (liste) malloc (sizeof(struct Cellule));

	//remplissage de la cellule

	cel->donnee = X;

	//chainage

	cel->suivant = *l;

	*l = cel ;

}

/*(11) retourne l'adresse de la derniere cellule*/

liste dernierCel(liste l){


	while(!videListe(l->suivant)){

		l = suivCellule(l);

	}

	return l;


}

/*(12) retourne la valeur de la derniere cellule */

TElement dernierVal(liste l){


	while(!videListe(l->suivant)){


		l = suivCellule(l);

	}

	return valCellule(l);

}

/*(9) ajoute d'une valeur en queue de la liste*/

void inserQueue(TElement X,liste *l){

liste cel;

liste der;

	der = dernierCel(*l);

	//creation de la cellule

	cel = (liste) malloc (sizeof(struct Cellule));

	//remplissage de la cellule

	cel->donnee = X;

	//chainage

	cel->suivant = NULL;

	der->suivant = cel;

}

/*(10) insertion dans une liste d'une valeur a une position donnée*/

void inserPos(int pos,TElement X,liste *l){

 liste celpre;

   if(pos<=longListe(*l)){

	celpre = celPre(pos-1,*l);

	inserTete(X,&(celpre->suivant));
	
   }else{

	printf("Erreur\n");

   }

}
/*(13) supprime la premiere cellule*/

void suppTete(liste *l){

liste cel ;

  if(!videListe(*l)){

	//préservation de la premier cellule de la liste 
	
	cel = *l;

	//realisation du chainage

	*l = suivCellule(*l);

	//liberation de la memeoire de la premier cellule

	free(cel);
  }

}

/*(14) supprime la liste*/

void suppListe(liste *l){

  if(!videListe(*l)){

	while(!videListe(*l)){

		suppTete(l);

 	}
  }

}

/*(15) suppression d'une cellule par sa position*/

void suppPos(int pos,liste *l){

 liste celpre;

   if(pos<=longListe(*l)){

	celpre = celPre(pos-1,*l);

	suppTete(&(celpre->suivant));
	
   }else{

	printf("Erreur\n");

   }

}
/*(16) verifier l'existence d'une valeur par raport a une liste*/

int existVal(TElement X,liste l){

   if(!videListe(l)){

	while( !videListe(l) && valCellule(l) != X){


		l = suivCellule(l);

	}

   }

	return !videListe(l);

}

/*(17) retourne l'adresse de la premier occurrence d'une valeur par raport a une liste donnée*/

liste adresseVal(TElement X,liste l){


	if(existVal(X,l)){

		while( !videListe(l) && valCellule(l) != X){


			l = suivCellule(l);
		}

		return l;

	}else

		return NULL;

}

/*(18) génération aléatoire d'une liste*/

liste generListe(){

liste l;

TElement elt;

int nbCel;

  printf("rentrez le nombre de cellule \n");
  scanf("%d",&nbCel);

  l=initListe();

	for(int i=0;i<nbCel;i++){

		elt = rand()%15;

		inserTete(elt,&l);

        }

   return l;

}

/*(19) Concatenation avec destruction des listes initiale*/

void concatListe(liste *l1,liste *l2){

liste der;

	if(videListe(*l1))

		*l1 = *l2;

	else{

		der = dernierCel(*l1);

		der->suivant = *l2;
        }

	*l2 = initListe();
}


/*programme principale*/

int main (void) {

liste l1,l2;
int i,elt;

srand(time(0));

	l1 = generListe();

	affListe(l1);

	l2 = generListe();

	affListe(l2);

	inserPos(2,4,&l1);

	affListe(l1);

	suppPos(1,&l1);

	affListe(l1);

	concatListe(&l1,&l2);

	affListe(l1);

	affListe(adresseVal(4,l1));

return 0; 

}
