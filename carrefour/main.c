#ifndef _MAIN_C_
#define _MAIN_C_

#include "main.h"

/* Initialise la mémoire partagée contenant l'état des feux
   et retourne son identifiant. Initialise l'état à vert Nord-Sud. */
static int initialiserMemoireEtatFeux() {
  int identifiant;
  feu *etat = NULL;

  identifiant =
      shmget(IPC_PRIVATE, sizeof(feu), IPC_CREAT | IPC_EXCL | 0666);
  etat = shmat(identifiant, NULL, 0);
  *etat = VERT_NORD_SUD;
  shmdt(etat);

  return identifiant;
}

/* Initialise la file de messages contenant les requêtes de
   passage au vert par les bus. */
static int initialiserFileRequetesBus() {
  int identifiant;

  identifiant = msgget(IPC_PRIVATE, 0);

  return identifiant;
}

/* Lance les processus de gestion de chaque direction. */
static void initialiserDirections(int fileRequetesBus, int memoireEtatFeux,
				  int semaphoreEtatFeux,
				  int memoireVoiesSortie,
				  int semaphoreVoiesSortie,
				  int semaphoreChangementFeux) {
  const direction directionsSud[3] = { OUEST, NORD, EST };
  const direction directionsNord[3] = { EST | SUD, SUD, OUEST | SUD };
  const direction directionsOuest[3] = { EST, EST | SUD, EST | SUD };
  const direction directionsEst[3] = { OUEST, OUEST | NORD, OUEST | NORD };
  int i;

  if (fork() == 0) {
    gestionDirection(SUD, NULL, memoireEtatFeux, semaphoreEtatFeux, 3,
		     directionsSud, 0, memoireVoiesSortie,
		     semaphoreVoiesSortie, semaphoreChangementFeux);
  } else if (fork() == 0) {
    gestionDirection(NORD, NULL, memoireEtatFeux, semaphoreEtatFeux, 3,
		     directionsNord, 0, memoireVoiesSortie,
		     semaphoreVoiesSortie, semaphoreChangementFeux);
  } else if (fork() == 0) {
    gestionDirection(OUEST, &fileRequetesBus, memoireEtatFeux,
		     semaphoreEtatFeux, 2, directionsOuest, 1,
		     memoireVoiesSortie, semaphoreVoiesSortie,
		     semaphoreChangementFeux);
  } else {
    gestionDirection(EST, &fileRequetesBus, memoireEtatFeux,
		     semaphoreEtatFeux, 2, directionsEst, 1,
		     memoireVoiesSortie, semaphoreVoiesSortie,
		     semaphoreChangementFeux);
    for (i = 1; i <= 3; i++) {
      wait(NULL);
    }
  }
}

static int initialiserMemoireVoiesSortie() {
  int identifiant;
  voiesSortie *etat = NULL;

  identifiant =
      shmget(IPC_PRIVATE, sizeof(voiesSortie),
	     IPC_CREAT | IPC_EXCL | 0666);
  etat = shmat(identifiant, NULL, 0);
  etat->nombreVehiculesOuest = 0;
  etat->nombreVehiculesEst = 0;
  etat->nombreVehiculesSud = 0;
  etat->nombreVehiculesNord = 0;
  shmdt(etat);

  return identifiant;
}

static void initialiserSemaphores(char *argv0, int *sem1, int *sem2, int *sem3) {
  int init[] = {1, 1, 0};

  initSem(3, argv0, init);
  *sem1 = 0;
  *sem2 = 1;
  *sem3 = 2;
}

/* Initialise les moyens de communications entre les processus
   et le processus eux-mêmes. */
int main(int argc, char **argv) {
  int fileRequetesBus;
  int memoireEtatFeux;
  int memoireVoiesSortie;
  int semaphoreEtatFeux;
  int semaphoreChangementFeux;
  int semaphoreVoiesSortie;

  memoireEtatFeux = initialiserMemoireEtatFeux();
  memoireVoiesSortie = initialiserMemoireVoiesSortie();
  fileRequetesBus = initialiserFileRequetesBus();
  initialiserSemaphores(argv[0], &semaphoreEtatFeux,
			&semaphoreVoiesSortie,
			&semaphoreChangementFeux);

  if (fork() == 0) {
    initialiserDirections(fileRequetesBus, memoireEtatFeux,
			  semaphoreEtatFeux, memoireVoiesSortie,
			  semaphoreVoiesSortie, 
			  semaphoreChangementFeux);
  } else {
    gestionFeux(fileRequetesBus, memoireEtatFeux, semaphoreEtatFeux,
		memoireVoiesSortie, semaphoreVoiesSortie,
		semaphoreChangementFeux);
    wait(NULL);
    msgctl(fileRequetesBus, IPC_RMID, NULL);
    shmctl(memoireEtatFeux, IPC_RMID, NULL);
    shmctl(memoireVoiesSortie, IPC_RMID, NULL);
    libereSem();
  }

  return 0;
}

#endif
