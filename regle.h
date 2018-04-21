#include <stdio.h>
#include "grille.h"
#include "clauses.h"



int ValeurX(int numCase, int valeurCase, int nombreCasesTotal);

//ecrit les valeur des cases pre-remplies
void ValeurDonnee(Grille *g,FNC* fnc);

//ecrit dans le fichier DIMACS la valeur que peut prendre une case numCase de z (entre 1 et nbCase(z))
void ValeurPossible(Grille* g, FNC* fnc, Zone* zoneCourante);

//ecirt dans le fichier DIMACS la vleur que ne peut pas prednre la case numCase(i.e les autres valeurs que celles ecrites par la procedure valeurPossible)
void ValeurImpossibleZone(Grille *g, FNC* fnc, Zone* zoneCourante);


void ValeurImpossibleCroix(Grille *g, FNC* fnc);

void EcritureEntete(FILE* f, FNC* fnc);
