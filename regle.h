#include <stdio.h>
#include "grille.h"
#include "clauses.h"


//traduit un numero de case et sa valeur un un litteral unique pour le fichier DIMACS
int ValeurX(int numCase, int valeurCase, int nombreCasesTotal);

//cree les clauses qui modelise les valeurs pré-remplies de la grille
void ValeurDonnee(Grille *g,FNC* fnc);

//fonction recusrsive sur les zones
//cree les clauses qui modelise la regle n°2
void ValeurPossible(Grille* g, FNC* fnc, Zone* zoneCourante);

// fonction recusrsive sur les zones
//cree les clauses qui modelise la regle n°3
void ValeurImpossibleZone(Grille *g, FNC* fnc, Zone* zoneCourante);

//cree les clauses qui modelise la regle n°4 
void ValeurImpossibleCroix(Grille *g, FNC* fnc);

void EcritureEntete(FILE* f, FNC* fnc);
