#include "clauses.h"


Clause* CreerClause(){
	Clause* c=malloc(sizeof(Clause));
	c->nbLit=0;
	c->cSuivant=NULL;
	return c;
}

int NbLitClause(Clause *c){
	return c->nbLit;
}

void AjoutLiteral(Clause *c, int valeur){
	c->litteral[c->nbLit]=valeur;
	c->nbLit++;
}

void AfficherClause(Clause* c, FILE* f){
	fprintf(f,"%d %d %d 0\n",c->litteral[0],c->litteral[1],c->litteral[2]);
}

void AfficherClause2(Clause* c){
	int i;
	for(i=0;i<c->nbLit;i++){
		printf("%d ",c->litteral[i]);
	}
	printf("0\n");
}

FNC* CreerFNC(int nbLitteraux){
	FNC* fnc=malloc(sizeof(FNC));
	fnc->nbClauses=0;
	fnc->nbLit=nbLitteraux;	
	fnc->c=NULL;
	return fnc;
}

int NbClauses(FNC* fnc){
	return fnc->nbClauses;
}

int NbLit(FNC* fnc){
	return fnc->nbLit;
}


void AjoutClause(FNC* fnc, Clause *clause, int nbLitUtilises){
	clause->cSuivant=fnc->c;
	fnc->c=clause;
	fnc->nbClauses++;
	fnc->nbLit=nbLitUtilises;
	
}


void Vers3SAT(FNC* fnc, Clause* c){
	int nbLit=NbLitClause(c);
	int i;
	int varTot=NbLit(fnc);
	int varAdd1=varTot+1;
	int varAdd2=varAdd1+1;
	
	//printf("%d\n",nbLit );
	if(nbLit==1){
		varTot=varTot+2;
		Clause *nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,varAdd1);
		AjoutLiteral(nvellClause,varAdd2);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);

		nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,-varAdd1);
		AjoutLiteral(nvellClause,varAdd2);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);

		nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,varAdd1);
		AjoutLiteral(nvellClause,-varAdd2);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);

		nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,-varAdd1);
		AjoutLiteral(nvellClause,-varAdd2);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);
	}
	else if(nbLit==2){
		varTot++;
		Clause *nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,c->litteral[1]);
		AjoutLiteral(nvellClause,varAdd1);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);

		nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,c->litteral[1]);
		AjoutLiteral(nvellClause,-varAdd1);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);
	}
	else if(nbLit==3){
		AjoutClause(fnc,c,varTot);
		//AfficherClause(c);
	}
	else if(nbLit>3){
		Clause *nvellClause=CreerClause();
		AjoutLiteral(nvellClause,c->litteral[0]);
		AjoutLiteral(nvellClause,c->litteral[1]);
		AjoutLiteral(nvellClause,varAdd1);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);

		for(i=2;i<nbLit-2;i++){
			nvellClause=CreerClause();
			AjoutLiteral(nvellClause,-varAdd1);
			AjoutLiteral(nvellClause,c->litteral[i]);
			AjoutLiteral(nvellClause,varAdd2);
			AjoutClause(fnc,nvellClause,varTot);
			//AfficherClause(nvellClause);

			varAdd1++;
			varAdd2++;
		}
		varTot=varAdd1;
		nvellClause=CreerClause();
		AjoutLiteral(nvellClause,-varAdd1);
		AjoutLiteral(nvellClause,c->litteral[i]);
		AjoutLiteral(nvellClause,c->litteral[i+1]);
		AjoutClause(fnc,nvellClause,varTot);
		//AfficherClause(nvellClause);
	}

	else{
		AfficherClause2(c);
	}
	
}


void EcritureClauses(FILE* f, FNC* fnc){
	Clause *closeCourante=fnc->c;
	while(closeCourante!=NULL){
		AfficherClause(closeCourante, f);
		closeCourante=closeCourante->cSuivant;
	}
}