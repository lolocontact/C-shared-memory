#include "segment.h"
/************************************************************************************************/
/*Fonction : creerSegment									*/
/* Description : Créer un segment de mémoire partagée, retourne l'id du segment			*/
/************************************************************************************************/
//name = argv[0] (nom de l'executable)
int creerSegment(int size, char *name)
{
	//on génère une clé unique avec la fonction unix ftok, qui utilise le système de fichier unix.
	//ici notre proj_id = 2 (cette valeur doit être différent de zéro : on utilise les 8 bits de poids faibles)
	key_t clef = ftok(name,(key_t) CLE) ;
	// On récupère l'ID de notre segment de mémoire partagée, 
	//on donne les droits d'écriture et de lecture à l'utilisateur
	int shmid = shmget( clef, size*sizeof(char), IPC_CREAT | SHM_R | SHM_W) ;
  	
	if ( shmid== -1 ) {
		printf("Erreur de création%s\n",strerror(errno)) ;
		exit(EXIT_FAILURE) ;  //on sort du programme
	}
	return shmid ;
}

/************************************************************************************************/
/*Fonction : connecteSegment									*/
/* Description : Même algo que creerSegment, mais permet de distinguer la création et la	*/
/*		connection à un segment								*/
/************************************************************************************************/
int connecteSegment(int size, char *name){
	key_t cleSegment = ftok(name, CLE); /* Clef du segment de mémoire partagée */
	if (cleSegment == - 1)
	{
		printf("CLIENT - Erreur de création de clef %s\n",strerror(errno));
	}
	int shmId = shmget(cleSegment, size, 0666 );
	if (shmId == -1)
	{
		printf("CLIENT - Erreur de création du segment de mémoire partagée %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	return shmId ;
}

/************************************************************************************************/
/*Fonction : attacheSegment									*/
/* Description : Ici on fait un segment partagée de type char* attacheSegment			*/
/************************************************************************************************/
//attacheSegment(id, &p)
void attacheSegment(int segmentID, char **p){
	*p = shmat(segmentID, "NULL", 0); //0=accès écriture et lecture, SHM_RDONLY = read only ...
	if (!*p)
	{
		printf("Impossible de s'attacher au segment de mémoire %d : %s\n",segmentID, strerror(errno));
		exit(EXIT_FAILURE) ;  /*on sort du programme */
	}
}

/************************************************************************************************/
/*Fonction : detacherSegment									*/
/* Description : on délie le segment de mémoire partagée à la variable p			*/
/************************************************************************************************/
void detacherSegment(char *p){
	int del = shmdt(p);
	
	if( del == -1){
		printf("Erreur de supression : %s\n",strerror(errno)) ;
		//exit(EXIT_FAILURE) ;  /*on sort du programme */
	}
}


/**************************************************************************************************/
/*Fonction : ecritureSegment                                                                      */
/* Description : On écrit sur un segment			                                  */
/**************************************************************************************************/
void ecritureSegment(int segmentID, char* message){
	char * zoneEcriture = shmat(segmentID,NULL,0);
	if (zoneEcriture == (char *)-1)
	{
		printf("SERVEUR - Impossible de s'attacher au segment de mémoire %d \n",segmentID);
		exit(EXIT_FAILURE);
	}
	sprintf(zoneEcriture,"%s",message);
}

/**************************************************************************************************/
/*Fonction : lireSegment                                                                          */
/* Description : Lis un segment					                                  */
/**************************************************************************************************/
char * lireSegment(int shmId){
	char * message = shmat(shmId,NULL,0);
	if (message == (char *)-1)
	{
		printf("CLIENT - Impossible de s'attacher au segment de mémoire : %d \n",shmId);
		exit(EXIT_FAILURE);
	}
	return message;
}
/************************************************************************************************/
/*Fonction : supprimerSegment									*/
/* Description : Supprimer un segment de mémoire partagée					*/
/************************************************************************************************/
void supprimerSegment(int shmid){
	if (shmctl(shmid,IPC_RMID,NULL) == -1){
  		printf("Erreur de supression : %s\n",strerror(errno)) ;
  	}
}

/************************************************************************************************/
/*Fonction : infoSegment									*/
/* Description : Donne des informations sur le segment de mémoire partagée			*/
/************************************************************************************************/
struct shmid_ds infoSegment(int shmid){
	struct shmid_ds buf;
	//IPC_SET IPC_RMID
	if(shmctl(shmid,IPC_STAT,&buf)==-1) {
		// vérification affichage des informations pour le segment
		perror("Erreur d'affichage");
		exit(1);
    	}
	else {
		// affichage des informations du segment
		/*printf("Informations du segments :\n") ;
		printf("\tUID : %d\n",buf.shm_perm.uid) ;
		printf("\tIUD : %d\n",buf.shm_perm.gid) ;
		printf("\tCUID : %d\n",buf.shm_perm.cuid) ;
		printf("\tCGID : %d\n",buf.shm_perm.cgid) ;
		printf("\tmode d'accès : %d\n",buf.shm_perm.mode) ;
		printf("\ttaille du segment : %d\n",(int) buf.shm_segsz) ;*/
		
	}
	return buf;
}
