#include "regle.h"

int ValeurX(int numCase, int valeurCase, int nombreCasesTotal){
	return ((nombreCasesTotal*(valeurCase-1))+(numCase + 1));
}


void ValeurDonnee(Grille* g, FNC* fnc){
	int i, j;
	int gn=NombreCaseGrille(g);
	int numCaseCourante, valeurCaseCourante;
	Clause* c;
	for(i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			valeurCaseCourante=ValCase(g,i,j);
			if(valeurCaseCourante!=0){
				numCaseCourante=NumCase(g,i,j);
				c=CreerClause();
				AjoutLiteral(c, ValeurX(numCaseCourante,valeurCaseCourante, gn));
				//AfficherClause2(c);
				Vers3SAT(fnc, c);
				//fprintf(f,"%d 0\n",ValeurX(numCaseCourante,valeurCaseCourante, gn));
			}
		}
	}
}


void ValeurPossible(Grille* g, FNC* fnc, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
    int gn=NombreCaseGrille(g);
	int numCaseCourante;
	int valPossibleMax=CaseMaxZone(ZoneTete(g));
	Clause* c,*cbis;
	int i=0,j;
	while(i<gn && ZoneCase(g,i)!=NumZone(zoneCourante)) {
		i++;
	}
	int nbCaseZone=NombreCaseZone(zoneCourante);
	numCaseCourante=i;
	while(numCaseCourante!=-1){
		c=CreerClause();
		for (i=1;i<=nbCaseZone;i++){
			AjoutLiteral(c, ValeurX(numCaseCourante,i, gn));
			//fprintf(stderr,"%d ",ValeurX(numCaseCourante,i, gn));
			
			for(j=i+1;j<=nbCaseZone;j++){
				cbis=CreerClause();
				AjoutLiteral(cbis, -ValeurX(numCaseCourante,i, gn));
				AjoutLiteral(cbis, -ValeurX(numCaseCourante,j, gn));
				//AfficherClause(cbis, stderr);
				//AfficherClause2(cbis);
				Vers3SAT(fnc, cbis);
				//fprintf(stderr,"%d ",ValeurX(numCaseCourante,i, gn));
				//fprintf(stderr,"%d 0\n",ValeurX(numCaseCourante,j, gn));
			}
		}
		//AfficherClause(c, stderr);
		//AfficherClause2(c);
		Vers3SAT(fnc, c);
		//fprintf(stderr, "0\n");
		
		for (i=nbCaseZone+1;i<=valPossibleMax;i++)
		{
			c=CreerClause();
			AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
			//AfficherClause2(c);
			Vers3SAT(fnc, c);
			//fprintf(stderr,"-%d 0\n",ValeurX(numCaseCourante,i, gn));
		}
		
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurPossible(g,fnc,zoneCourante);
}


void ValeurImpossibleZone(Grille *g, FNC* fnc, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
    int gn=NombreCaseGrille(g);
	int numCaseCourante, numCaseSuivante;
	int nbCaseZone=NombreCaseZone(zoneCourante);
	Clause* c;
	int i=0;
	while(i<gn && ZoneCase(g,i)!=NumZone(zoneCourante)) {
		i++;
	}
	numCaseCourante=i;
	numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	
	while(numCaseSuivante!=-1)
	{
		while(numCaseSuivante!=-1)
		{
			
			for(i=1;i<=nbCaseZone;i++){
				c=CreerClause();
				AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
				AjoutLiteral(c, -ValeurX(numCaseSuivante,i, gn));
				//AfficherClause2(c);
				Vers3SAT(fnc, c);
				//fprintf(f,"-%d -%d 0\n",ValeurX(numCaseCourante,i, gn),ValeurX(numCaseSuivante,i, gn));
			}
			numCaseSuivante=CaseSuivanteZone(g,numCaseSuivante);
			
		}
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
		numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurImpossibleZone(g,fnc,zoneCourante);
}



void ValeurImpossibleCroix(Grille *g, FNC* fnc){
	Zone* zoneCourante = ZoneTete(g);
	int gn=NombreCaseGrille(g);
	int valPossibleMax=CaseMaxZone(ZoneTete(g))*gn;
	int caseDessus, caseDessous, caseDroite,caseGauche;
	//printf("%d\n",valPossibleMax );
	while (zoneCourante!=NULL){
		int numCaseCourante;
		int nbCaseZone=NombreCaseZone(zoneCourante);
		Clause* c;
		int i=0,j=0;
		
		while(i<gn && ZoneCase(g,i)!=NumZone(zoneCourante)) {
			i++;
		}
		numCaseCourante=i;
		int largeur=LargeurGrille(g);
		while(numCaseCourante!=-1){
			//i correspond aux valeurs possibles de la case courante
			for (i=1;i<=nbCaseZone;i++){
				//
				for(j=1;j<=i;j++){
	    				//case du dessus
						caseDessus=numCaseCourante-largeur*j;
	    				if(caseDessus>=0 && caseDessus<valPossibleMax){ 
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
							AjoutLiteral(c, -ValeurX(caseDessus,i, gn));
							
							//printf("\nA \ni=%d j=%d\n",i,j );
							//AfficherClause2(c);
							Vers3SAT(fnc, c);
	      					//fprintf(f,"-%d -%d 0\n",ValeurX(numCaseCourante,i, gn),ValeurX(numCaseCourante-largeur,i, gn));
	      					//fprintf(f,"-x(%d,%d) -x(%d,%d) B 0\n",numCaseCourante,i,numCaseCourante-largeur,i);
	      				}
	    				//case du dessous
	    				caseDessous=numCaseCourante+largeur*j;
	    				if((caseDessous<gn) && (caseDessous<valPossibleMax)){
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
							AjoutLiteral(c, -ValeurX(caseDessous,i, gn));
							
							//printf("\nB \ni=%d j=%d\n",i,j );
							//AfficherClause2(c);
							Vers3SAT(fnc, c);
	    					//fprintf(f,"-%d -%d 0\n",ValeurX(numCaseCourante,i, gn),ValeurX(numCaseCourante+largeur,i, gn));
	    					//fprintf(f,"-x(%d,%d) -x(%d,%d) B 0\n",numCaseCourante,i,numCaseCourante+largeur,i);
	    				}
	    				//case de droite
	    				caseDroite=numCaseCourante+j;
	    				if(estMemeLigne(numCaseCourante,caseDroite,largeur)&&(caseDroite<gn-1)){
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
							AjoutLiteral(c, -ValeurX(numCaseCourante+j,i, gn));
							
							//printf("\nC \ni=%d j=%d\n",i,j );
							//AfficherClause2(c);
							Vers3SAT(fnc, c);
	    					//fprintf(f,"-%d -%d 0\n",ValeurX(numCaseCourante,i, gn),ValeurX(numCaseCourante+j,i, gn));
	    					//fprintf(f,"-x(%d,%d) -x(%d,%d) C 0\n",numCaseCourante,i,numCaseCourante+j,i);
	      				}
	    				//case de gauche
	    				caseGauche=numCaseCourante-j;
	    				if(estMemeLigne(numCaseCourante,caseGauche,largeur)&&(caseGauche>=0)){
	      					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, gn));
							AjoutLiteral(c, -ValeurX(numCaseCourante-j,i, gn));
							
							//printf("\nD \ni=%d j=%d\n",i,j );
							//AfficherClause2(c);
							Vers3SAT(fnc, c);
	      					//fprintf(f,"-%d -%d 0\n",ValeurX(numCaseCourante,i, gn),ValeurX(numCaseCourante-j,i, gn));
	      					//fprintf(f,"-x(%d,%d) -x(%d,%d) D 0\n",numCaseCourante,i,numCaseCourante-j,i);
	  					}
	  			}
			}
			numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
		}
		zoneCourante=ZoneSuivante(zoneCourante);
	}
}




void EcritureEntete(FILE* f, FNC* fnc){
	fprintf(f,"p cnf %d %d\n",NbLit(fnc),NbClauses(fnc));
}