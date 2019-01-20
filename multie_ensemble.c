#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

typedef struct {

  int Val;

  int nbOcc;

}TElement;

typedef struct {

  int NbElemMax;

  int NbElem;

  TElement *tab;

}Multiensemble;

/*1*/

int ValElts (TElement X){

   return X.Val;

}

int NbOccElts (TElement X){

   return X.nbOcc;

}

int NbEltsME (Multiensemble ME){

   return ME.NbElem;

}

int NbMaxEltsME (Multiensemble ME){

   return ME.NbElemMax;

}

TElement IemeEltsME(int i, Multiensemble ME){

   return ME.tab[i];

}

void increm(int *X){

  (*X)++;

}


/*2*/

Multiensemble Allouer(int Nmax){

   Multiensemble ME ;

     ME.NbElemMax=Nmax;

     ME.NbElem=0;

     ME.tab=(TElement*)malloc(Nmax*sizeof(TElement));

   return ME;

}

/*5*/

int Multiensemble_vide(Multiensemble ME){

  if(NbEltsME(ME)==0)

       return 1;

  else

       return 0;

}

/*6*/

int Multiensemble_plein(Multiensemble ME){

  if(NbEltsME(ME)==NbMaxEltsME(ME))

       return 1;

  else

       return 0;

}

/*7*/

void Affiche_ME(Multiensemble ME){

  int i;

  for(i=0;i<NbEltsME(ME);i++){

    printf("(%d,%d)\t",ValElts(IemeEltsME(i,ME)),NbOccElts(IemeEltsME(i,ME)));

  }

    printf("\n");

}

/*8*/

TElement PlusOcc_ME(Multiensemble ME){

int i;
TElement E = IemeEltsME(0,ME);

  for(i=1;i<NbEltsME(ME);i++){

      if( NbOccElts(E) < NbOccElts(IemeEltsME(i,ME)) ){

		E=IemeEltsME(i,ME);

      }

  }

		return E;

}

/*9*/

int Existance(Multiensemble ME, TElement X){

int i=0;

 if( ValElts(IemeEltsME(i,ME)) > ValElts(X) )

       return -1;

 else{

    while( (ValElts(IemeEltsME(i,ME)) != ValElts(X)) && (i < ME.NbElem) ){

          i++;
    }

    if( (ValElts(IemeEltsME(i,ME)) == ValElts(X)) )

        return i;

    else

        return -1;
 }

}

/*10*/

void AjouterElt(Multiensemble *ME, TElement V){

int ind,n;

 ind = Existance(*ME,V);

   if(ind == -1){ //Decalage par la fin

 	n = NbEltsME(*ME)-1;

      while( n>=0 && ValElts(V) < ValElts(IemeEltsME(n,*ME)) ){

             ME->tab[n+1] = ME->tab[n];
             n--;
      }

            ME->tab[n+1].Val = ValElts(V);
	        ME->tab[n+1].nbOcc = 1;
            ME->NbElem++;

   }else{ // metre a jour le NbOcc

	    ME->tab[ind].nbOcc = ME->tab[ind].nbOcc + V.nbOcc ;

   }

}

/*11*/

void SuppElt(Multiensemble *ME, TElement V){

int ind,i;

  ind = Existance(*ME,V);

  if(ind >= 0){
  
      if( NbOccElts(IemeEltsME(ind,*ME)) > 1 ){

		ME->tab[ind].nbOcc--;
      }else{

          for(i=ind;i<NbEltsME(*ME);i++){

                ME->tab[i] = ME->tab[i+1];

          }
                ME->NbElem--;
      }
  }

}

/*générer aléatoirement*/

Multiensemble GenererME(int Nmax){

Multiensemble ME=Allouer(Nmax);
int i;
TElement E;

  for(i=0;i<Nmax;i++){

     //E.Val = rand()%20;

     printf("rentrez votre chiffre\n");
     scanf("%d",&E.Val);

     E.nbOcc = 1;

     AjouterElt(&ME,E);

  }

	return ME;

}

/*Copier*/

void Copier(Multiensemble ME1,Multiensemble *ME2){

int i;

ME2->NbElem = NbEltsME(ME1);

 for(i=0;i<NbEltsME(*ME2);i++){

       ME2->tab[i] = ME1.tab[i];
 }

}

/*12*/

void Union (Multiensemble ME1,Multiensemble ME2,Multiensemble *ME3){

int i;

*ME3=Allouer(NbEltsME(ME1) + NbEltsME(ME2));

Copier(ME1,ME3);

 for(i=0;i<NbEltsME(ME2);i++){

 		AjouterElt( ME3,IemeEltsME(i,ME2) );

 }

}

/*minimum des nombres d'elements*/

int minEnt(int a,int b){

int min;

	min = a;

	  if(a > b)

			min = b;

 return min;

}

/*13*/

void intersec(Multiensemble ME1,Multiensemble ME2,Multiensemble *ME3){

int i,j,k;
int min;


i=j=k=0;

min = minEnt(ME1.NbElem,ME2.NbElem);

*ME3 = Allouer(min);


 while( i<NbEltsME(ME1) && j<NbEltsME(ME2) ){

    if( ValElts(IemeEltsME(i,ME1)) == ValElts(IemeEltsME(j,ME2)) ){

            ME3->tab[k].Val = ValElts(IemeEltsME(i,ME1));

            ME3->tab[k].nbOcc = minEnt( NbOccElts(IemeEltsME(i,ME1)) , NbOccElts(IemeEltsME(i,ME2)) );
   
          k++;
          i++;
          j++;

    }else{

		  if( ValElts(IemeEltsME(i,ME1)) > ValElts(IemeEltsME(j,ME2)) ){

                                       j++;
          }else{

				       i++;
          }

    }

 }

 ME3->NbElem = k;
   
}
	
/*Programme Principal*/

int main (){

Multiensemble ME1,ME2,MEu,MEi;
TElement PO;




srand(time(0));

ME1=GenererME(2);

ME2=GenererME(4);

Union(ME1,ME2,&MEu);

intersec(ME1,ME2,&MEi);


Affiche_ME(ME1);

Affiche_ME(ME2);

Affiche_ME(MEu);

Affiche_ME(MEi);


/*PO=PlusOcc_ME(ME1);

printf("le nombre qui a le plus d'occurense est : %d\n",PO.Val);

printf("rentrez le chifre supprimer\n");
scanf("%d",&PO.Val);

SuppElt(&ME1,PO);

Affiche_ME(ME1);

*/


return 0;
}
