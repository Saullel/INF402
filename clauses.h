#include <stdio.h>
#include <stdlib.h>

#define LIT_MAX 10


typedef struct clause {
	int nbLit; 
	int litteral[LIT_MAX];
	struct clause *cSuivant;
}Clause;


typedef struct {
	int nbClauses;
	int nbLit;
	Clause *c;
}FNC;



Clause* CreerClause();

int NbLitClause(Clause *c);

void AjoutLiteral(Clause *c, int valeur);

void AfficherClause(Clause* c, FILE* f);

void AfficherClause2(Clause* c);

FNC* CreerFNC(int nbLitteraux);

int NbClauses(FNC* fnc);

int NbLit(FNC* fnc);

int NbLitTotal(FNC* fnc);

void AjoutClause(FNC *fnc, Clause *clause, int nbLitUtilises);

void Vers3SAT(FNC* fnc, Clause* c);

void EcritureClauses(FILE* f, FNC* fnc);