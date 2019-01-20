#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define ZERO '0'

#define NEUF '9'

#define MAX_NB 1000

/*		<<<<<<< STRUCTURE POUR LES EXPRESSION DE REELS>>>>>>>		*/

typedef float TElement1;

typedef enum{OPERATEUR,OPERANDE}natureElt;

typedef union {

	char Oper;

	TElement1 Opnd;

}valeurElt;

typedef struct {

	natureElt nElt;

	valeurElt vElt;

}TElement2;

/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/

typedef char TElement;

typedef struct Cellule{

	TElement donnee;

	struct Cellule *suivant;

}*liste;

typedef struct Cellule1{

	TElement1 donnee1;

	struct Cellule1 *suivant1;

}*liste1;

typedef struct Cellule2{

	TElement2 donnee2;

	struct Cellule2 *suivant2;

}*liste2;

/* primitives pour les liste chaînées */

TElement valCellule(liste l){

	return l->donnee;

}

liste suivCellule(liste l){

	return l->suivant;

}

TElement1 valCellule1(liste1 l){

	return l->donnee1;

}

liste1 suivCellule1(liste1 l){

	return l->suivant1;

}

TElement2 valCellule2(liste2 l){

	return l->donnee2;

}

liste2 suivCellule2(liste2 l){

	return l->suivant2;

}

/* 		<<<<<<<	LES PILE >>>>>>>			*/

/*		{ représentation Chaînées }		*/


typedef liste pile;

typedef liste1 pileEntier;

typedef liste2 pileCarSpe;

/* primitives pour les piles */

TElement sommetPile(pile p){

	return p->donnee;

}

pile suivant(pile p){

	return p->suivant;

}

TElement1 sommetPileEntier(pileEntier pe){

	return pe->donnee1;

}

pileEntier suivantEntier(pileEntier pe){

	return pe->suivant1;

}

TElement2 sommetPileCarSpe(pileCarSpe pe){

	return pe->donnee2;

}

pileCarSpe suivantCarSpe(pileCarSpe pe){

	return pe->suivant2;

}

/*1) initialiser une pile*/

pile initPile(){

	return NULL;

}

pileEntier initPileEntier(){

	return NULL;

}

pileCarSpe initPileCarSpe(){

	return NULL;

}

/*2) teste si une pile est vide ou pas */

int videPile(pile p){

	return p == NULL;

}

int videPileEntier(pileEntier pe){

	return pe == NULL;

}

int videPileCarSpe(pileCarSpe pe){

	return pe == NULL;

}
/*3) afficher une pile */

void affPile(pile p){


	while(!videPile(p)){

		printf("%c\t",sommetPile(p));
	
		p = suivant(p);

	}

	printf("\n");

}

void affPileEntier(pileEntier pe){


	while(!videPileEntier(pe)){

		printf("%f\t",sommetPileEntier(pe));

		pe = suivantEntier(pe);

	}

	printf("\n");

}

void affPileCarSpe(pileCarSpe pe){


	while(!videPileCarSpe(pe)){

		if(sommetPileCarSpe(pe).nElt == OPERANDE ){

			printf("%lf\t",sommetPileCarSpe(pe));

		}else{

			printf("%c\t",sommetPileCarSpe(pe));
	
		}

		pe = suivantCarSpe(pe);

	}

	printf("\n");

}

/*4) determiner la hauteur d'une pile */

int hauteurPile(pile p){

  int lg = 0;

	while(!videPile(p)){

		lg = lg+1;

		p = suivant(p);

	}

	return lg;

}

int hauterPileEntier(pileEntier pe){

 int lg = 0;

	while(!videPileEntier(pe)){

		lg = lg+1;

		pe = suivantEntier(pe);

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

void empileEntier(TElement1 X,pileEntier *pe){

pileEntier cel;

	//création de la cellule

	cel = (pileEntier) malloc (sizeof(struct Cellule1));

	//remplissage de la cellule

	cel->donnee1 = X;

	//chainage

	cel->suivant1 = *pe;

	*pe = cel ;

}

void empileCarSpe(TElement2 X,pileCarSpe *pe){

pileCarSpe cel;

	//création de la cellule

	cel = (pileCarSpe) malloc (sizeof(struct Cellule2));

	//remplissage de la cellule

	cel->donnee2 = X;

	//chainage

	cel->suivant2 = *pe;

	*pe = cel ;

}
/*6) depiler "retirer la valeur au sommet de la pile */

void depileEntier(pileEntier *pe){

pileEntier cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *pe;

	//realisation du chainage

	*pe = suivantEntier(*pe);

	//liberation de la memeoire de la premier cellule

	free(cel);

}

void depile(pile *p){

pile cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *p;

	//realisation du chainage

	*p = suivant(*p);

	//liberation de la memeoire de la premier cellule

	free(cel);

}

void depileCarSpe(pileCarSpe *p){

pileCarSpe cel ;

	//préservation de la premier cellule de la liste 
	
	cel = *p;

	//realisation du chainage

	*p = suivantCarSpe(*p);

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

		X = 'p';

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

typedef struct {


  liste2 teteReel;

  liste2 queueReel;


}fileReel;

/* premitives pour les Files */

liste teteFile(file f){

	return f.tete;

}

liste queueFile(file f){

	return f.queue;

}

liste2 teteFileReel(fileReel f){

	return f.teteReel;

}

liste2 queueFileReel(fileReel f){

	return f.queueReel;

}

int finChar(char car){

	return (car == '\0');

}

/*1) initialiser une file */

file initFile(){

 file f;

 f.tete = f.queue = NULL;

	return f;

}

fileReel initFileReel(){

 fileReel f;

 f.teteReel = f.queueReel = NULL;

	return f;

}

/*2) teste si une file est vide ou pas */

int videFile(file f){

	return ( f.tete == NULL );

}

int videFileReel(fileReel f){

	return ( f.teteReel == NULL );

}

/*3) determoner la valeur du sommet de la file*/

TElement sommetFile(file f){

	return valCellule(teteFile(f));

}

TElement2 sommetFileReel(fileReel f){

	return valCellule2(teteFileReel(f));

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

void emfileReel(TElement2 X,fileReel *f){

 liste2 cel;

 cel = (liste2) malloc (sizeof(struct Cellule2));

 cel->donnee2 = X;

 cel->suivant2 = NULL;

	if( videFileReel(*f) )

		f->teteReel = f->queueReel = cel ;

	else{

		(f->queueReel)->suivant2 = cel;

		f->queueReel = cel;

	}

//affFileReel(*f);

}

/*5) defiler "retire la valeur en tete de la file" */

void defile(file *f){

 liste ff;

 ff = f->tete;

 f->tete = suivCellule(f->tete);

 free(ff);

}

void defileReel(fileReel *f){

 liste2 ff;

 ff = f->teteReel;

 f->teteReel = suivCellule2(f->teteReel);

 free(ff);

}

/*6) afficher les element de la file */

void affFile(file f){


	while( !videFile(f) ){

		printf("%c\t",sommetFile(f));
	
		(f.tete) = (suivCellule(f.tete));

	}

	printf("\n");

}

void affFileReel(fileReel f){


	while( !videFileReel(f) ){

		if(sommetFileReel(f).nElt == OPERANDE ){

			printf("%.3lf\t",sommetFileReel(f).vElt);

		}else{

			printf("%c\t",sommetFileReel(f).vElt);
	
		}

		(f.teteReel) = (suivCellule2(f.teteReel));
		
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

		X = 'f';

		emfile(X,&f);

        }

	return f;

}

/*		<<<<<<< APPLICATION >>>>>>>>>>				*/

int Point(char car){

	return car == '.';

}

int parenthese(char car){

	return car == '(';

}

int separateur(char car){

	return car == ' ' || ',' ;

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

double evalNbre(int *i,char *exp){

 double pe ,pd ,div10;

 char car;

 int n;

 pe = pd = 0;

 car = exp[*i];

	if(!Point(car)){

		do{

			n = car - '0';

			pe = pe*10+n;

			(*i)++;

			car = exp[*i];

		}while(chiffre(car));

	}

	if(Point(car)){

		(*i)++;

		car = exp[*i];

		div10 = 0.1;

		while(chiffre(car)){

			n = car - '0';

			pd = pd + n * div10;

			div10 = div10*0.1;

			(*i)++;

			car = exp[*i];

		}

	}

	return (pe+pd);
}


file transformeEXP(char *exp){


 int Erreur = 0;

 int i = 0;

 char car,oper;

 file f,f0;

 pile p;

 car = exp[i];

 f = f0 = initFile();

 p = initPile();


	while( !finChar(exp[i]) && !Erreur ){

		if( parenthese(car)  ){

				i++;

				car = exp[i];

		}else{

			if( chiffre(car) ){

				emfile(car,&f);
	
				i++;

				car = exp[i];

			}

			if( operateur(car) ){

				empile(car,&p);

				i++;

				car = exp[i];

			}else{

				if( parentheseFermente(car) ){

					oper = sommetPile(p);

					depile(&p);

					emfile(oper,&f);

					i++;

					car = exp[i];

				}else

					Erreur = 1;	

			}


		}

	}

	if( videPile(p) && !Erreur)

		return f;

	else

		return f0;

}

fileReel transformeEXPReel(char *exp){


 int Erreur = 0;

 int i = 0;

 double nb ;

 TElement2 ef,ep ,oper;

 char car;

 fileReel f,f0;

 pileCarSpe p;

 car = exp[i];

 f = f0 = initFileReel();

 p = initPileCarSpe();


	while( !finChar(exp[i]) && !Erreur ){

		if( parenthese(car)  ){

				i++;

				car = exp[i];

		}else{

			if( chiffre(car) || Point(car) ){

				nb = evalNbre(&i,exp);

				ef.nElt = OPERANDE;

				ef.vElt.Opnd = nb;

				emfileReel(ef,&f);

				car = exp[i];

			}

			if( operateur(car) ){

				ep.nElt = OPERATEUR;

				ep.vElt.Oper = car;

				empileCarSpe(ep,&p);

				i++;

				car = exp[i];

			}else{

				if( parentheseFermente(car) ){

					oper = sommetPileCarSpe(p);

					depileCarSpe(&p);

					emfileReel(oper,&f);

					i++;

					car = exp[i];

				}else

					Erreur = 1;	

			}


		}

	}

	if( videPileCarSpe(p) && !Erreur)

		return f;

	else

		return f0;

}


float evalExpPostFixe(file f){

 float OperandG,OperandD,res;

 int car1;

 pileEntier pe ;

 pe = initPileEntier();

 char car;


	while( !videFile(f) ){

		car = sommetFile(f);

		defile(&f);

		if( chiffre(car) ){

			car1 = car - '0';

			empileEntier(car1,&pe);

		}else{

			OperandG = sommetPileEntier(pe);

			depileEntier(&pe);

			OperandD = sommetPileEntier(pe);

			depileEntier(&pe);

			res = eval(car,OperandD,OperandG);

			empileEntier(res,&pe);
		}

	}

  return sommetPileEntier(pe);

}

float evalExpPostFixeReel(fileReel f){

 float OperandG,OperandD,res;

 float car1;

 pileEntier pe ;

 pe = initPileEntier();

 TElement2 car;


	while( !videFileReel(f) ){

		car = sommetFileReel(f);

		defileReel(&f);

		if( car.nElt == OPERANDE ){

			empileEntier(car.vElt.Opnd,&pe);

		}else{

			OperandG = sommetPileEntier(pe);

			depileEntier(&pe);

			OperandD = sommetPileEntier(pe);

			depileEntier(&pe);

			res = eval(car.vElt.Oper,OperandD,OperandG);

			empileEntier(res,&pe);
		}

	}

  return sommetPileEntier(pe);

}

void affExp(char *exp ){

 int i;

 float res;

 file expPostFixe;

 i=0;

 expPostFixe = transformeEXP(exp);

 res = evalExpPostFixe(expPostFixe);

	while( !finChar(exp[i]) ){


		printf("%c",exp[i]);

		i++;

	}

	printf(" = %f.",res);

	printf("\n");

}

void affExpReel(char *exp ){

 int i;

 float res;

 fileReel expPostFixe;

 i=0;

 expPostFixe = transformeEXPReel(exp);

 res = evalExpPostFixeReel(expPostFixe);

	while( !finChar(exp[i]) ){


		printf("%c",exp[i]);

		i++;

	}

	printf(" = %f.",res);

	printf("\n");

}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/

int main (void) {

char exp[MAX_NB] ="(((5*7)+(9*4))/(2-7))";

char expReel[MAX_NB] = "((23.51-20.054)*(.313+41))";

affExpReel(expReel);

affExp(exp);

}
