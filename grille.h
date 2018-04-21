#define LMAX 15
#define CMAX 15
#include <stdio.h>
#include <stdlib.h>
typedef int bool;

typedef struct zone
{
	int numeroZone;
	int nbCase;
	struct zone *zSuivant;

}Zone;


typedef struct grille
{
	int hauteur;
	int largeur;
	int valeurCase[LMAX][CMAX];
	int zoneCase[LMAX*CMAX];
	int nbZones;
	Zone* tete; //Liste des ZONES

}Grille;

/* ------------------------------------------------------------------------ */
//renvois le maximum entre 2 entiers
int max(int a, int b);

// Recuperer la longueur de la grille
int HauteurGrille(Grille *g);

// Recuperer la largeur de la grille
int LargeurGrille(Grille *g);

// Recuperer le nombre de zones de la grille 
int NombreZone(Grille *g);

// Recuperer le nb de cases par zone
int NombreCaseZone(Zone *z);

//Recuperer le nombre de cases dans la grille
int NombreCaseGrille(Grille *g);

//Recuperer la valeur d'une case dans la grille
int ValCase(Grille *g, int hauteurCase, int largeurCase);

//Recuperer le numero de zone d'une case donnee (calculée avec NumCase)
int ZoneCase(Grille *g, int numCase);

//Calculer le numero d'une case a partir de ses coordonnées
int NumCase(Grille *g, int hauteurCase, int largeurCase);

//Recuperer la tete de la file de zones de la grille
Zone* ZoneTete(Grille *g);

//Recuperer le numero de la prochaine case d'une zone
int CaseSuivanteZone(Grille *g, int numCase);

int estMemeLigne(int numCase1,int numCase2, int largeur);

//Recuperer le numero d'une zone donnee
int NumZone(Zone* z);

//Recuperer la zone suivante d'une zone
Zone* ZoneSuivante(Zone *z);

//Affecter un numero de zone à une zone
void AffecterNumZone(Zone *z, int num);

//Incrementer le nombre de case d'une zone
void IncrNbCaseZone(Zone *z);

//Incrementer le nombre de zone total
void IncrNbZones(Grille *g);

//Renvois le nombre de case de la zone la plus grande
int CaseMaxZone(Zone* z);

/* ------------------------------------------------------------------------ */
//Initialise une nouvelle zone vide
Zone* InitZone();

//Initialise une nouvelle grille de dimensions données vide
Grille* InitGrille(int hauteur, int largeur);

//Rempli une grille à partir d'un descripteur de fichier fourni en parametre
// Pré-condition 1 : le descripteur pointe sur le debut d'un fichier grille
// Pré-condition 2 : le fichier fourni est correct.
Grille* LireGrille(FILE* fichier);

//Affiche la grille donnée en parametre 
void AfficherGrille(Grille *g);

