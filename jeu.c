#include "regle.h"

int main(int argc, char* argv[]){

	// ouverture du fichier grille en parametre et gestion des erreurs
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

	int nbLitteraux=NombreCaseGrille(g)*CaseMaxZone(ZoneTete(g));
	FNC* fnc=CreerFNC(nbLitteraux);

	// determine les clauses et les stock dans une structure FNC  
	ValeurDonnee(g,fnc);
	ValeurPossible(g,fnc, ZoneTete(g));
	ValeurImpossibleZone(g,fnc, ZoneTete(g));
	ValeurImpossibleCroix(g,fnc);

	// ouverture du fichier DIMACS et gestion des erreurs
	FILE* Dimacs=fopen("dimacs.out","w");
	if (Dimacs==NULL){
		fprintf(stderr, "Erreur lors de la création du fichier de sortie DIMACS\n");
		return 1;
	}
	
	// ecriture dans le fichier DIMACS
	EcritureEntete(Dimacs, fnc);
	EcritureClauses(Dimacs, fnc);

	fclose(Dimacs);
return 0;

}
