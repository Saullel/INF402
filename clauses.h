#include <stdio.h>
#include <stdlib.h>

#define LIT_MAX 10	//une zone n'aura que tres rarement 10 litteraux ou plus


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


//initialise une nouvelle clause vide
Clause* CreerClause();

//renvoie le nombre de litteraux dans une clause
int NbLitClause(Clause *c);

//ajoute en fin un literal dans une clause
void AjoutLiteral(Clause *c, int valeur);

//affiche une clause de 3 litteraux
void AfficherClause(Clause* c, FILE* f);

//affiche une clause de n litteraux
void AfficherClause2(Clause* c);

//initialise une FNC de nbLitteraux 
FNC* CreerFNC(int nbLitteraux);

//renvoie le nombre de clause d'une FNC
int NbClauses(FNC* fnc);

//renvoie le nombre de litteraux total d'une FNC
int NbLit(FNC* fnc);

//ajoute une clause en tete dans une FNC
void AjoutClause(FNC *fnc, Clause *clause, int nbLitUtilises);

//transforme une clause une ou plusieurs clauses de 3 litteraux
//ajoutee(s) en debut d'une FNC
void Vers3SAT(FNC* fnc, Clause* c);

//ecriture dans un fichier l'ensemble des clauses d'une FNC
void EcritureClauses(FILE* f, FNC* fnc);