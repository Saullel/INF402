#include "regle.h"

int main(int argc, char* argv[]){
	FILE* fichier_grille=fopen(argv[1],"r");
	if (!fichier_grille){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier grille.\n");
	}
	if (argc!=2){
		fprintf(stderr, "Usage : ./jeu fichier_grille\n");
		return 1;
	}
	Grille *g=LireGrille(fichier_grille);
	fclose(fichier_grille);
	AfficherGrille(g);
	FILE* Dimacs=fopen("dimacs.out","w");
	if (Dimacs==NULL){
		fprintf(stderr, "Erreur lors de la création du fichier de sortie DIMACS\n");
		return 1;
	}
	ValeurDonnee(Dimacs,g);
	ValeurPossible(Dimacs, g, ZoneTete(g));
	fclose(Dimacs);
return 0;

}
