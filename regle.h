#include <stdio.h>
#include "grille.h"


//ecrit les valeur des cases pre-remplies
void ValeurDonnee(FILE* f, Grille *g);

//ecrit dans le fichier DIMACS la valeur que peut prendre une case numCase de z (entre 1 et nbCase(z))
void ValeurPossible(FILE* f, Grille* g, Zone* zoneCourante);

//ecirt dans le fichier DIMACS la vleur que ne peut pas prednre la case numCase(i.e les autres valeurs que celles ecrites par la procedure valeurPossible)
void ValeurImpossibleZone(FILE* f, Grille *g, Zone* zoneCourante);


/*void ValeurImpossibleCroix(FILE* f, Grille *g, Zone* zoneCourante);*/
