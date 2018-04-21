#include "grille.h"

int max(int a, int b){
	if (a>b){
		return a;
	}
	else return b;
}
// Recuperer la longueur de la grille
int HauteurGrille(Grille *g){
	return g->hauteur;
}

// Recuperer la largeur de la grille
int LargeurGrille(Grille *g){
	return g->largeur;
}

	
// Recuperer le nombre de zones de la grille 
int NombreZone(Grille *g){
	return g->nbZones;
}

// Recuperer le nb de cases par zone
int NombreCaseZone(Zone *z){
		return z->nbCase;
}

int NombreCaseGrille(Grille *g){
	return LargeurGrille(g)*HauteurGrille(g);
}
int ValCase(Grille *g, int hauteurCase, int largeurCase){
	return g->valeurCase[hauteurCase][largeurCase];
}

int ZoneCase(Grille *g, int numCase){
	return g->zoneCase[numCase];
}

int NumCase(Grille *g, int hauteurCase, int largeurCase){
	return hauteurCase*HauteurGrille(g)+largeurCase;
}

int CaseSuivanteZone(Grille *g, int numCase){
	int i=numCase+1;
	int numZone=ZoneCase(g,numCase);
	int nbCase=NombreCaseGrille(g);
	while(i<nbCase && ZoneCase(g,i)!=numZone) 
	{
		i++;
	}
	if (i==nbCase){
		return -1;
	}
	else return i;
}

int estMemeLigne(int numCase1,int numCase2, int largeur){
	return ((numCase1/largeur)==(numCase2/largeur));
}

Zone* ZoneTete(Grille *g){
	return g->tete;
}

int NumZone(Zone* z){
	return z->numeroZone;
}

Zone* ZoneSuivante(Zone *z){
	return z->zSuivant;
}

void AffecterNumZone(Zone *z, int num){
	z->numeroZone=num;
}
void IncrNbCaseZone(Zone *z){
	z->nbCase++;
}

void IncrNbZones(Grille *g){
	g->nbZones++;
}

void AffecterValeur (Grille *g, int val, int hauteurCase, int largeurCase){
	g->valeurCase[hauteurCase][largeurCase]=val;
}

int CaseMaxZone(Zone* z){
		if (z==NULL){
			return 0;
		}
		return max(NombreCaseZone(z),CaseMaxZone(ZoneSuivante(z)));
}

/* ------------------------------------------------------------------------ */


Zone* InitZone(){
	Zone* z=malloc(sizeof(Zone));
	z->numeroZone=0;
	z->nbCase=0;
	z->zSuivant=NULL;
	return z;
}

Grille* InitGrille(int hauteur, int largeur){
	Grille* g=malloc(sizeof(Grille));
	int i,j;
	if (!g)
		return NULL;
	g->largeur=largeur;
	g->hauteur=hauteur;
	g->nbZones=0;
	g->tete=NULL;
	for (i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			g->valeurCase[i][j]=0;
		}

	}
	return g;
}

Grille* LireGrille(FILE* f){
	Grille* g;
	int hauteur,largeur;
	fscanf(f,"%d",&hauteur);
	fscanf(f,"%d",&largeur); //lecture des parametres
	g=InitGrille(hauteur,largeur); //initiallisaion de la grille
	if(!g){
		fprintf(stderr, "Erreur initialisation\n");
		return NULL;
	}	

	int i,j;
	//lecture des valeurs des cases
	int val=0;
	for (i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			fscanf(f,"%d",&val);
			AffecterValeur(g,val,i,j);
		}
	}
	//lecture de la zone pour chaque case
	for(i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			fscanf(f,"%d",&val);
			g->zoneCase[NumCase(g,i,j)]=val;
		}
	}
	int zoneCaseCourante=ZoneCase(g,0);
	Zone* zNouveau;
	zNouveau=InitZone();
	AffecterNumZone(zNouveau,zoneCaseCourante);
	IncrNbCaseZone(zNouveau);
	g->tete=zNouveau;
	Zone* temp=g->tete;
	for(i=1;i<NombreCaseGrille(g);i++){
		zoneCaseCourante=ZoneCase(g,i);
		while(temp->zSuivant!=NULL && NumZone(temp)!=zoneCaseCourante){
			temp=ZoneSuivante(temp);
		}
		if(NumZone(temp)==zoneCaseCourante){
			IncrNbCaseZone(temp);
		}
		else {
			zNouveau=InitZone();
			AffecterNumZone(zNouveau,zoneCaseCourante);
			IncrNbCaseZone(zNouveau);
			temp->zSuivant=zNouveau;
		}
		temp=g->tete;
		
	}
	return g;
}

void AfficherGrilleBrute(Grille *g){
	int i,j;
	for (i=0;i<HauteurGrille(g);i++){
		for(j=0;j<LargeurGrille(g);j++){
			printf("%d(%d) ",ValCase(g,i,j),ZoneCase(g,NumCase(g,i,j)));
		}
		printf("\n");
	}
}

void AfficherGrille(Grille *g){
	int nbCaseGrille=NombreCaseGrille(g);
	int zonePrecedente,zoneCourante;
	int numCase=0,i,val=0;
	int positionCase=0;
	for(i=0;i<HauteurGrille(g);i++){
		printf("\n");
	}
	printf("\t\t\t\t-");
	for(i=0;i<LargeurGrille(g);i++){
		printf("~~~~");
	}
	printf("\n");
	zonePrecedente=-1;
	zoneCourante=-1;
	while (numCase<nbCaseGrille){
		zonePrecedente=zoneCourante;
		zoneCourante=ZoneCase(g,numCase);
		positionCase=numCase%LargeurGrille(g);
		val=ValCase(g,(numCase-positionCase)/HauteurGrille(g),positionCase);
		if(positionCase==0){
			printf("\t\t\t\t|");
			if (val==0)
				printf(" . ");
			else
				printf(" %d ",val );
		}
		else {
			if(zonePrecedente==zoneCourante){
				printf(" ");
			}
			else{
				printf("|");
			}
			if (val==0)
				printf(" . ");
			else
				printf(" %d ",val );			
			if (positionCase==LargeurGrille(g)-1){//gestion fin de ligne
				printf("|\n\t\t\t\t");
				for(i=1;i<=LargeurGrille(g);i++){
					if(ZoneCase(g,numCase-LargeurGrille(g)+i)==ZoneCase(g,numCase+i)){
						printf("    ");
					}
					else {
						printf("~~~~");
					}
				}
				printf("\n");
			}
		}
		numCase++;
	}
	for(i=0;i<HauteurGrille(g);i++){
		printf("\n");
	}
	
}
