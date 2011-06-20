#ifndef _GESTIONFEUX_H_
#define _GESTIONFEUX_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include "types.h"
#include <time.h>
#include "semaphore.h"

/* Procédure de gestion des feux du carrefour. filesRequetesBus[direction] 
   est l'identifiant d'une file de messages contenant les demandes de 
   passage au vert des bus de la direction direction. memoireEtatFeu est
   l'identifiant d'une zone de mémoire partagée dans laquelle on indiquera
   les changements d'état des feux. */
void gestionFeux(const int fileRequetesBus, const int memoireEtatFeu,
		 const int semaphoreEtatFeux, const int memoireVoiesSortie,
		 const int semaphoreVoiesSortie);

#endif
