/*----------------------------------------------------------

             semaphores de Dijkstra
             
 Attention : ne pas affecter les semaphores a SEM_UNDO
             car il y a risque que des operations soient defaites
             alors qu'il y a encore un processus utilisateur
---------------------------------------------------------*/
#ifndef _SEMAPHORE_C_
#define _SEMAPHORE_C_

#include "semaphore.h"
#define MAX_SEM 10

/*================= LOCAL */

static int tabSemId;

static void erreurFin(const char *msg) {
  perror(msg);
  exit(1);
}

static void appelSem(int numSem, int op) {
  struct sembuf sempar;
  const int nbop = 1;

  sempar.sem_num = numSem;
  sempar.sem_op = op;
  sempar.sem_flg = 0;		/* ne pas mettre a SEM_UNDO !! */
  if (semop(tabSemId, &sempar, nbop) == -1)
    erreurFin("appelSem");
}

/*================= EXPORTE */

/*----------------- primitives ---------------------------*/

void P(int numSem) {
  appelSem(numSem, -1);
}

void V(int numSem) {
  appelSem(numSem, 1);
}

/*----------------- creation -------------------------------
             pvinit : tableau d'entiers contenant les valeurs
                      initiales, init a 0 si NULL          */

void initSem(int nbSem, char *argv0, int *pvinit) {
  int i;
  key_t cle = ftok(argv0, '0');

  /* creation du tableau de semaphores */
  if ((tabSemId = semget(cle, nbSem, IPC_CREAT | 0600)) == -1) {
    erreurFin("initSem : semget");
  }

  /* initialisation du tableau de semaphores */
  for (i = 0; i < nbSem; i++) {
    if (pvinit == NULL) {
      if (semctl(tabSemId, i, SETVAL, NULL) == -1) {
	erreurFin("initSem : semctl 1");
      }
    } else {
      if (semctl(tabSemId, i, SETVAL, pvinit[i]) == -1) {
	erreurFin("initSem : semctl 2");
      }
    }
  }
}

/*-------------- destruction (car objets globaux persistents) */
void libereSem() {
  if (semctl(tabSemId, 0, IPC_RMID, 0))
    erreurFin("libereSem");
}

#endif
