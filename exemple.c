#include "segment.h"

/************************************************************************************************/
/* Description : Exemple d'utilisation de mémoire partagée côté serveur	/ client		*/
/************************************************************************************************/
int main(int argc, char *argv[]){

	char string[SIZE]; 
	int sh_id;
	struct shmid_ds buf;
	
	printf("Voulez-vous :\n");
	printf("1) Créer le segment de mémoire partagée\n");
	printf("2) Utiliser un segment de mémoire partagée déjà existant\n");
	scanf("%d",&sh_id);
	
	if(sh_id==1){
		sh_id = creerSegment(SIZE, argv[0]);
		printf("----id du segment : %d \n",sh_id);
	}else{
		printf("saisir votre id :\n");
		scanf("%d",&sh_id);
	}
	
	//attacheSegment(sh_id, &string);
	
	printf("Ecrivez dans la mémoire partagée :\n");
	scanf("%s",string);
	ecritureSegment( sh_id, string);
	
	printf("mémoire partagée : %s\n",lireSegment(sh_id));
	getchar();
	getchar();
	
	printf("mémoire partagée : %s\n",lireSegment(sh_id));
	getchar();
	getchar();
	
	buf = infoSegment(sh_id);
	// affichage des informations du segment
		printf("Informations du segments :\n") ;
		printf("\tUID : %d\n",buf.shm_perm.uid) ;
		printf("\tIUD : %d\n",buf.shm_perm.gid) ;
		printf("\tCUID : %d\n",buf.shm_perm.cuid) ;
		printf("\tCGID : %d\n",buf.shm_perm.cgid) ;
		printf("\tmode d'accès : %d\n",buf.shm_perm.mode) ;
		printf("\ttaille du segment : %d\n",(int) buf.shm_segsz) ;
	
	//printf("On détache la mémoire partagée :\n");
	//detacherSegment(string);
	
	//getchar();
	//printf("mémoire partagée : %s\n",lireSegment(sh_id));
	//getchar();
	
	printf("On supprime la mémoire partagée\n");
	supprimerSegment(sh_id);
	
	return 0;
}
