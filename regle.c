#include "regle.h"




void ValeurDonnee(FILE* f, Grille* g){
	int i, j;
	int numCaseCourante, valeurCaseCourante;
	for(i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			valeurCaseCourante=ValCase(g,i,j);
			if(valeurCaseCourante!=0){
				numCaseCourante=NumCase(g,i,j);
				fprintf(f,"x(%d, %d) 0\n",numCaseCourante,valeurCaseCourante);
			}
		}
	}
}


void ValeurPossible(FILE* f, Grille* g, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
	int numCaseCourante;
	int valPossibleMax=CaseMaxZone(ZoneTete(g));
	int i=0;
	while(i<NombreCaseGrille(g) && ZoneCase(g,i)!=NumZone(zoneCourante)) {
		i++;
	}
	int nbCaseZone=NombreCaseZone(zoneCourante);
	numCaseCourante=i;
	while(numCaseCourante!=-1){
		for (i=1;i<=nbCaseZone;i++)
		{
			fprintf(f,"x(%d, %d) ",numCaseCourante,i);
		}
		fprintf(f, "0\n");
		
		for (i=nbCaseZone+1;i<=valPossibleMax;i++)
		{
			fprintf(f,"-x(%d, %d) 0\n",numCaseCourante,i);
		}
		
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurPossible(f,g,zoneCourante);
}


void ValeurImpossibleZone(FILE* f, Grille *g, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
	int numCaseCourante, numCaseSuivante;
	int nbCaseZone=NombreCaseZone(zoneCourante);
	int i=0;
	while(i<NombreCaseGrille(g) && ZoneCase(g,i)!=NumZone(zoneCourante)) {
		i++;
	}
	numCaseCourante=i;
	numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	
	while(numCaseSuivante!=-1)
	{
		while(numCaseSuivante!=-1)
		{
			for(i=1;i<=nbCaseZone;i++){
				fprintf(f,"-x(%d, %d) -x(%d,%d) 0\n",numCaseCourante,i,numCaseSuivante,i);
			}
			numCaseSuivante=CaseSuivanteZone(g,numCaseSuivante);
		}
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
		numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurImpossibleZone(f,g,zoneCourante);
}



/*void ValeurImpossibleCroix(FILE* f, Grille *g, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
	int numCaseCourante, numCaseSuivante;
	int nbCaseZone=NombreCaseZone(zoneCourante);
	int i=0;
	while(i<NombreCaseGrille(g) && ZoneCase(g,i)!=NumZone(zoneCourante)) {
		i++;
	}
	numCaseCourante=i;
	int hauteur=HauteurGrille(g);
	int largeur=LargeurGrille(g);
	while(numCaseCourante!=-1){
		
		for (i=1;i<=nbCaseZone;i++)
		{
			  int numCase =2;
  			  int i=0 ;//iterateur
			  for(i=1,i<=valeur, i++)
  			  {
    				//case du dessus
    				if(!(numCase-longueur*i<0)) //if 0 is the minimal case.adr
      				printf("-x(%d,%d) -x(%d,%d) 0\n",numCase,valeur,numCase-longueur,valeur);
    				//case du dessous
    				if(!(numcase+longueur*i>hauteur*longueur))
      				printf("-x(%d,%d) -x(%d,%d) 0\n",numCase,valeur,numCase+longueur,valeur);
    				//case de droite
    				if((estMemeLigne(numcase,numCase+1))&&numCase+1<=hauteur*longueur)
      				printf("-x(%d,%d) -x(%d,%d) 0\n",numCase,valeur,numCase+1,valeur);
    				//case de gauche
    				if(estMemeLigne(numCase,numCase-1))&&numCase-1>=0)
      				printf("-x(%d,%d) -x(%d,%d) 0\n",numCase,valeur,numCase-1,valeur);
  		}
	}
	
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurImpossibleCroix(f,g,zoneCourante);
	}
}
*/

























