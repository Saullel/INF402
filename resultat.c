#include <stdio.h>

#include "grille.h"

int main(int argc, char* argv[]){
	
	if (argc!=3){
		fprintf(stderr, "Usage : ./resultat fichier_grille fichier_resultat\n");
		return 1;
	}

	FILE* fichier_grille=fopen(argv[1],"r");
	if (!fichier_grille){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier grille.\n");
		return 1;
	}
	
	FILE* fichier_resultat=fopen(argv[2],"r");
	if (!fichier_resultat){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier resultat.\n");
		return 1;
	}

	Grille *g=LireGrille(fichier_grille);
	fclose(fichier_grille);

	int nbTotCases=NombreCaseGrille(g);
	int nbValeurPossible=CaseMaxZone(ZoneTete(g));
	int largeur=LargeurGrille(g);
	int nb,numeroCase, hauteurCase, largeurCase, valeurCase;
	int i=0;
	char c='a';

	while(c!='\n'){
		fscanf(fichier_resultat,"%c",&c);	// c recupere "SAT"
	}
	AfficherGrille(g);
	fscanf(fichier_resultat,"%d",&nb);
	while(nb!=0){	
		if(nb>0 && nb<=nbTotCases*nbValeurPossible){
			numeroCase=i%nbTotCases;
			hauteurCase=numeroCase/largeur;
			largeurCase=numeroCase%largeur;
			valeurCase=((nb-numeroCase+1)/nbTotCases)+1;
			ChangerValCase(g,hauteurCase,largeurCase,valeurCase);
		}
		fscanf(fichier_resultat,"%d",&nb);
		i++;	
	}
	AfficherGrille(g);

	return 0;
}

// cas limite : 2 cases 1 zone