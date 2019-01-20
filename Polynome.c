#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

/*1) les structure de données*/

typedef struct {

   int degre;

   float coeff;

}Monome;

typedef struct Cellule{

  Monome donnee;

  struct Cellule *MonSuivant;

}*Polynome;

/*2) les prémitive */

int degMon(Monome mon){

	return mon.degre;

}

float coefMon(Monome mon){

	return mon.coeff;

}

Monome MonCourant(Polynome p){

	return p->donnee;

}

Polynome MonSuivant(Polynome p){

	return p->MonSuivant;

}

/*3) crée un polynome vide */

Polynome creePolynome(){

	return NULL;

}

/*4) teste si un polynome est vide ou pas */

int videPoly(Polynome p){

	return p == NULL ;

}

/*5) ajouter un monome en tete du polynome */

void inserTete(Monome mon , Polynome *p){

  Polynome cel;

  //creation de la cellule

  cel = (Polynome) malloc (sizeof(struct Cellule));

  //remplissage de la cellule

  cel->donnee = mon;

  //chainage 

  cel->MonSuivant = *p;

  *p = cel;

}

/*6) determiner le dernier monome du polynome */

Polynome dernierMonome(Polynome p){

 if( !videPoly(p) ){

   while( !videPoly(p->MonSuivant) ){

	p = MonSuivant(p);

   }

 }
	return p;

}

/*7) ajouter un monome en queue du polynome */

void inserQueue(Monome mon , Polynome *p){


  if( videPoly(*p) )

	inserTete(mon, p);

  else{

  	Polynome cel;

  	Polynome der;

  	der = dernierMonome(*p);

  	//creation de la cellule

  	cel = (Polynome) malloc (sizeof(struct Cellule));

  	//remplissage de la cellule 

  	cel->donnee = mon;

  	//chainege

  	cel->MonSuivant = NULL;

  	der->MonSuivant = cel;

  }

}


/*16) afficher un polynome donneer */

void affichePoly(Polynome p){

 if(!videPoly(p)){

  	printf("P(X) = ");

  	while( !videPoly(p) ){

		if( degMon(MonCourant(p)) != 0 ){

			if(coefMon(MonCourant(p)) > 0)

				printf("+%fX^%d  ",coefMon(MonCourant(p)),degMon(MonCourant(p)));

			else
		
				printf("%fX^%d  ",coefMon(MonCourant(p)),degMon(MonCourant(p)));

      		
		}else

				printf("%f ",coefMon(MonCourant(p)));

		p = MonSuivant(p);

  	}

  	printf("\n");

 }else

	printf("NULL\n");

}


/*8) determinner l'adresse du polynome precedent */

Polynome polyPrecedent(Monome Mon , Polynome p){


    while( !videPoly(p->MonSuivant) && degMon(Mon) >= degMon(MonCourant(p->MonSuivant)) ){


		p = MonSuivant(p);

    }

    return p;

}

/*9) determiner l'adresse du monome s'il existe on fait la recherche par rapport aux degrer */

Polynome appartienMonome(Monome Mon , Polynome p){


   while( (!videPoly(p)) && (degMon(Mon) > degMon(MonCourant(p))) ){


		p = MonSuivant(p);

   }

  return p;

}

/*10) supprimer le monome en tete du polynome */

void suppTete(Polynome *p){

  Polynome cel ;

  //conservation de la premiere cellule

  cel = *p;

  //chainage

  *p = MonSuivant(*p);

  free(cel);

}

/*11) insertion d'un monome donner*/

void inserMonPoly(Monome Mon , Polynome *p){

  int c;

 Polynome PrePoly;


 if( (videPoly(*p)) || (degMon(Mon) < degMon(MonCourant(*p))) ){

		inserTete(Mon,p);

 }else{

	if(degMon(Mon) == degMon(MonCourant(*p)) ){

		c = coefMon(Mon)+coefMon(MonCourant(*p));

		if( c == 0)

			suppTete( p);

		else

			((*p)->donnee).coeff = c;

	}else{

		PrePoly = polyPrecedent(Mon,*p);

		if( degMon(Mon) == degMon(MonCourant(PrePoly)) ){

			c = coefMon(Mon)+coefMon(MonCourant(PrePoly));

			if( c == 0)

				suppTete(&PrePoly);

			else

				(PrePoly->donnee).coeff = c;

		}else

			inserTete(Mon,&(PrePoly->MonSuivant));

	}

 }

}

/*12)suppression d'un monome donne*/

void delMon(Monome Mon , Polynome *p){

 Polynome iMon;

 iMon = appartienMonome(Mon,*p);

 if( !videPoly(iMon) && coefMon(Mon) == coefMon(MonCourant(iMon)) )

		suppTete(&iMon);


}

/*13) supprime un polynome */

void delPolynome(Polynome *p){


  while( !videPoly(*p) ){

	suppTete(p);

  }

}

/*14) determiner le plus grand coefficient du polynome */

float maxCoef(Polynome p){

 float maxCoef;

 maxCoef = coefMon(MonCourant(p));

 while( !videPoly(p) ){

    p = MonSuivant(p);

	if( maxCoef < coefMon(MonCourant(p)) )

		maxCoef = coefMon(MonCourant(p));

 }

 return maxCoef; 

}

/*15) determiner la somme des coefficient d'un polynome donne */

float sommeCoef(Polynome p){

 float som;

 som =0;

 while( !videPoly(p) ){

     som += coefMon(MonCourant(p));

     p = MonSuivant(p);

 }

 return som;

}

/*17) genere un polynome aleatoirement ou bien avec un dialogue interactife */

Polynome generPolynome(){

 Polynome p;

 Monome Mon;

 int nbMon;

  printf("rentrez le nombre de Monome \n");
  scanf("%d",&nbMon);

  p = creePolynome();

	for(int i=0;i<nbMon;i++){

		Mon.degre = rand()%5;

		Mon.coeff = -5+rand()%11;

	    if(Mon.coeff != 0)

		inserMonPoly(Mon,&p);

        }

   return p;

}

/*18) derivee d'un polynome donnee*/

Polynome derivPoly(Polynome p){

 Polynome dp;

 Monome Mon;

 dp = creePolynome();

	if( degMon(MonCourant(p)) == 0 )

		p = MonSuivant(p);

	while( !videPoly(p) ){

		Mon.coeff = coefMon(MonCourant(p)) * degMon(MonCourant(p));

		Mon.degre = degMon(MonCourant(p))-1;

		inserQueue(Mon,&dp);

		p = MonSuivant(p);
	}

 return dp;

}

/*19) la somme de deux polunome donnee*/

Polynome sommePoly(Polynome p1 , Polynome p2){

  Polynome p3 ;

  Monome Mon;

  float c;

  p3 = creePolynome();


	while( !videPoly(p1) && !videPoly(p2) ){

		if( degMon(MonCourant(p1)) == degMon(MonCourant(p2)) ){

			c = coefMon(MonCourant(p1)) + coefMon(MonCourant(p2)) ;

			if( c != 0 ){

				Mon.coeff = c;

				Mon.degre = degMon(MonCourant(p1));
				
				inserQueue(Mon,&p3);
			}

			p1 = MonSuivant(p1);

			p2 = MonSuivant(p2);

		}else{

			if( degMon(MonCourant(p1)) < degMon(MonCourant(p2)) ){

				inserQueue(MonCourant(p1),&p3);

				p1 = MonSuivant(p1);

			}else{

				inserQueue(MonCourant(p2),&p3);

				p2 = MonSuivant(p2);

			}
		}

	}

	while( !videPoly(p1) ){

		inserQueue(MonCourant(p1),&p3);

		p1 = MonSuivant(p1);
	
	}

	while( !videPoly(p2) ){

		inserQueue(MonCourant(p1),&p3);

		p2 = MonSuivant(p2);

	}

  return p3;
}

/*programme principale */

int main (void) {

  srand(time(0));

  Polynome p1,p2,dp,sp;

  p1 = generPolynome();

  p2 = generPolynome();

  sp = sommePoly(p1,p2);

  dp = derivPoly(p1);

  affichePoly(p1);

  affichePoly(p2);

  affichePoly(dp);

  affichePoly(sp);

  

return 0;

}
