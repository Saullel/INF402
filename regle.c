#include "regle.h"

int ValeurX(int numCase, int valeurCase, int nombreCasesTotal){
	return ((nombreCasesTotal*(valeurCase-1))+(numCase + 1));		//faites nous confiance, ça marche.
}


void ValeurDonnee(Grille* g, FNC* fnc){
	int i, j;
	int nbCaseGrille=NombreCaseGrille(g);
	int numCaseCourante, valeurCaseCourante;
	Clause* c;
	for(i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			valeurCaseCourante=ValCase(g,i,j);
			if(valeurCaseCourante!=0){		
				numCaseCourante=NumCase(g,i,j);
				c=CreerClause();
				AjoutLiteral(c, ValeurX(numCaseCourante,valeurCaseCourante, nbCaseGrille));
				Vers3SAT(fnc, c);
			}
		}
	}
}


void ValeurPossible(Grille* g, FNC* fnc, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
    int nbCaseGrille=NombreCaseGrille(g);
	int numCaseCourante;
	int valPossibleMax=CaseMaxZone(ZoneTete(g));
	Clause* c,*cbis;
	int i=0,j;
	while(i<nbCaseGrille && ZoneCase(g,i)!=NumZone(zoneCourante)) {		//on cherche la premiere case de la zone
		i++;
	}
	int nbCaseZone=NombreCaseZone(zoneCourante);
	numCaseCourante=i;
	while(numCaseCourante!=-1){		//sur toutes les cases de la zone
		c=CreerClause();
		for (i=1;i<=nbCaseZone;i++){	//c clause qui prend toutes les valeurs possible de la case
			AjoutLiteral(c, ValeurX(numCaseCourante,i, nbCaseGrille));
			
			for(j=i+1;j<=nbCaseZone;j++){	//cbis ne permet pas qu'une case ait plusieurs valeurs
				cbis=CreerClause();
				AjoutLiteral(cbis, -ValeurX(numCaseCourante,i, nbCaseGrille));
				AjoutLiteral(cbis, -ValeurX(numCaseCourante,j, nbCaseGrille));
				Vers3SAT(fnc, cbis);
			}
		}
		Vers3SAT(fnc, c);
		
		for (i=nbCaseZone+1;i<=valPossibleMax;i++){		//on admet que certains litteraux sont toujours faux
			c=CreerClause();
			AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
			Vers3SAT(fnc, c);
		}
		
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurPossible(g,fnc,zoneCourante);		//recursivite
}


void ValeurImpossibleZone(Grille *g, FNC* fnc, Zone* zoneCourante){
	if(zoneCourante==NULL){
		return;
	}
    int nbCaseGrille=NombreCaseGrille(g);
	int numCaseCourante, numCaseSuivante;
	int nbCaseZone=NombreCaseZone(zoneCourante);
	Clause* c;
	int i=0;
	while(i<nbCaseGrille && ZoneCase(g,i)!=NumZone(zoneCourante)) {		//on cherche la premiere case de la zone
		i++;
	}
	numCaseCourante=i;
	numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	
	while(numCaseSuivante!=-1)		//on travaille sur toutes les cases
	{
		while(numCaseSuivante!=-1)		//par rapport aux autres cases de la zone
		{
			
			for(i=1;i<=nbCaseZone;i++){		//sur les valeurs qu'elles peuvent prendre
				c=CreerClause();
				AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
				AjoutLiteral(c, -ValeurX(numCaseSuivante,i, nbCaseGrille));
				Vers3SAT(fnc, c);
			}
			numCaseSuivante=CaseSuivanteZone(g,numCaseSuivante);
			
		}
		numCaseCourante=CaseSuivanteZone(g,numCaseCourante);
		numCaseSuivante=CaseSuivanteZone(g,numCaseCourante);
	}
	zoneCourante=ZoneSuivante(zoneCourante);
	ValeurImpossibleZone(g,fnc,zoneCourante);		//recursivite
}



void ValeurImpossibleCroix(Grille *g, FNC* fnc){
	Zone* zoneCourante = ZoneTete(g);		//premiere zone de la grille
	int nbCaseGrille=NombreCaseGrille(g);
	int valPossibleMax=CaseMaxZone(ZoneTete(g))*nbCaseGrille;
	int caseDessus, caseDessous, caseDroite,caseGauche;
	while (zoneCourante!=NULL){		//on travaille sur toutes les zones
		int numCaseCourante;
		int nbCaseZone=NombreCaseZone(zoneCourante);
		Clause* c;
		int i=0,j=0;
		
		while(i<nbCaseGrille && ZoneCase(g,i)!=NumZone(zoneCourante)) {		//on cherche lapremiere case de la zone
			i++;
		}
		numCaseCourante=i;
		int largeur=LargeurGrille(g);
		while(numCaseCourante!=-1){		//sur toutes les cases de la zone
			for (i=1;i<=nbCaseZone;i++){		// i : valeur possible de la case
				for(j=1;j<=i;j++){		// j : distance par rapport à numCaseCourante 
	    				//case du dessus
						caseDessus=numCaseCourante-largeur*j;
	    				if(caseDessus>=0 && caseDessus<valPossibleMax){ 
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
							AjoutLiteral(c, -ValeurX(caseDessus,i, nbCaseGrille));
							Vers3SAT(fnc, c);
	      				}
	    				//case du dessous
	    				caseDessous=numCaseCourante+largeur*j;
	    				if((caseDessous<nbCaseGrille) && (caseDessous<valPossibleMax)){
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
							AjoutLiteral(c, -ValeurX(caseDessous,i, nbCaseGrille));
							Vers3SAT(fnc, c);
	    				}
	    				//case de droite
	    				caseDroite=numCaseCourante+j;
	    				if(estMemeLigne(numCaseCourante,caseDroite,largeur)&&(caseDroite<nbCaseGrille-1)){
	    					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
							AjoutLiteral(c, -ValeurX(numCaseCourante+j,i, nbCaseGrille));
							Vers3SAT(fnc, c);
	      				}
	    				//case de gauche
	    				caseGauche=numCaseCourante-j;
	    				if(estMemeLigne(numCaseCourante,caseGauche,largeur)&&(caseGauche>=0)){
	      					c=CreerClause();
							AjoutLiteral(c, -ValeurX(numCaseCourante,i, nbCaseGrille));
							AjoutLiteral(c, -ValeurX(numCaseCourante-j,i, nbCaseGrille));
							Vers3SAT(fnc, c);
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