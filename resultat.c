#include <stdio.h>

int main(){
	int nbTotCases=9;
	int nbValeurPossible=4;
	int nb,numeroCase, valeurCase;
	int i=0;
	scanf("%d",&nb);
	while(nb!=0){	
		if(nb>0 && nb<=nbTotCases*nbValeurPossible){
			numeroCase=i%nbTotCases;
			valeurCase=((nb-numeroCase+1)/nbTotCases)+1;
			printf("x(%d,%d) \n",numeroCase,valeurCase);
		}
		scanf("%d",&nb);
		i++;	
	}
	return 0;
}

// cas limite : 2 cases 1 zone