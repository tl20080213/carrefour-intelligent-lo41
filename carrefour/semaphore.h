#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* Cree et initialise nbSem sémaphores au valeur contenu dans le tableau 
   pvinit, 0 si pvinit est NULL. Initialise la cle avec argv0. */
void initSem(int nbSem, char *argv0, int *pvinit);

/* Libere les sémaphores. */
void libereSem();

/* Primitive P de Dijkstra */
void P(int numSem);

/* Primitive V de Dijkstra */
void V(int numSem);

#endif
