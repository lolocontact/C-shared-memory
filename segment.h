#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>  
#include <errno.h>
#include <signal.h>

#include <pthread.h>

#define SIZE 1000
#define CLE 2

#define CHECK(sts,msg) if ((sts) == -1 )  { perror(msg);_exit(-1);}

/************************************************************************************************/
/*Fonction : creerSegment									*/
/* Description : Créer un segment de mémoire partagée, retourne l'id du segment			*/
/************************************************************************************************/
int creerSegment(int size, char *name);

/************************************************************************************************/
/*Fonction : connecteSegment									*/
/* Description : Même algo que creerSegment, mais permet de distinguer la création et la	*/
/*		connection à un segment								*/
/************************************************************************************************/
int connecteSegment(int size, char *name);

/************************************************************************************************/
/*Fonction : attacheSegment									*/
/* Description : Ici on fait un segment partagée de type char* attacheSegment			*/
/************************************************************************************************/
void attacheSegment(int segmentID, char **p);

/************************************************************************************************/
/*Fonction : detacherSegment									*/
/* Description : on délie le segment de mémoire partagée à la variable p			*/
/************************************************************************************************/
void detacherSegment(char *p);

/**************************************************************************************************/
/*Fonction : ecritureSegment                                                                      */
/* Description : On écrit sur un segment			                                  */
/**************************************************************************************************/
void ecritureSegment(int segmentID, char* message);

/**************************************************************************************************/
/*Fonction : lireSegment                                                                          */
/* Description : Lis un segment					                                  */
/**************************************************************************************************/
char * lireSegment(int shmId);

/************************************************************************************************/
/*Fonction : supprimerSegment									*/
/* Description : Supprimer un segment de mémoire partagée					*/
/************************************************************************************************/
void supprimerSegment(int shmid);

/************************************************************************************************/
/*Fonction : infoSegment									*/
/* Description : Donne des informations sur le segment de mémoire partagée			*/
/************************************************************************************************/
struct shmid_ds infoSegment(int shmid);
