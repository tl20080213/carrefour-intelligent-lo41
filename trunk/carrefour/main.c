#ifndef _MAIN_C_
#define _MAIN_C_

#include "main.h"

/* Initialise la mémoire partagée contenant l'état des feux
   et retourne son identifiant. Initialise l'état à vert Nord-Sud. */
int initialiserMemoireEtatFeux() {
  int identifiant;
  feu *etat = NULL;

  identifiant = shmget(IPC_PRIVATE, sizeof(feu), IPC_CREAT|IPC_EXCL|0666);
  etat = shmat(identifiant, NULL, 0);
  *etat = VERT_NORD_SUD;
  shmdt(etat);

  return identifiant;
}

/* Initialise la file de messages contenant les requêtes de
   passage au vert par les bus. */
int initialiserFileRequetesBus() {
  int identifiant;

  identifiant = msgget(IPC_PRIVATE, 0);

  return identifiant;
}

/* Lance les processus de gestion de chaque direction. */
void initialiserDirections(int fileRequetesBus, int memoireEtatFeux, int semaphoreEtatFeux,
			   int memoireVoiesSortie, int semaphoreVoiesSortie) {
  const direction directionsSud[3] = {OUEST, NORD, EST};
  const direction directionsNord[3] = {EST|SUD, SUD, OUEST|SUD};
  const direction directionsOuest[3] = {EST, EST|SUD, EST|SUD};
  const direction directionsEst[3] = {OUEST, OUEST|NORD, OUEST|NORD};
  int i;

  if (fork() == 0) {
    gestionDirection(SUD, NULL, memoireEtatFeux, semaphoreEtatFeux, 3, directionsSud, 0,
		     memoireVoiesSortie, semaphoreVoiesSortie);
  } else if (fork() == 0) {
    gestionDirection(NORD, NULL, memoireEtatFeux, semaphoreEtatFeux, 3, directionsNord, 0,
		     memoireVoiesSortie, semaphoreVoiesSortie);
  } else if (fork() == 0) {
    gestionDirection(OUEST, &fileRequetesBus, memoireEtatFeux, semaphoreEtatFeux, 2, 
		     directionsOuest, 1, memoireVoiesSortie, semaphoreVoiesSortie);
  } else {
    gestionDirection(EST, &fileRequetesBus, memoireEtatFeux, semaphoreEtatFeux, 2, 
		     directionsEst, 1, memoireVoiesSortie, semaphoreVoiesSortie);
    for (i = 1; i <= 3; i++) {
      wait(NULL);
    }
  }
}

/* Initialise le sémaphore qui protège les accès à l'état des feux.
   Cela pourra être un mutex. */
int initialiserSemaphoreEtatFeux() {
  return semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0666);
}

int initialiserMemoireVoiesSortie() {
  int identifiant;
  voiesSortie *etat = NULL;

  identifiant = shmget(IPC_PRIVATE, sizeof(voiesSortie), IPC_CREAT|IPC_EXCL|0666);
  etat = shmat(identifiant, NULL, 0);
  etat->nombreVehiculesOuest = 0;
  etat->nombreVehiculesEst = 0;
  etat->nombreVehiculesSud = 0;
  etat->nombreVehiculesNord = 0;
  shmdt(etat);

  return identifiant;
}

int initialiserSemaphoreVoiesSortie() {
  return semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0666);
}

/* Initialise les moyens de communications entre les processus
   et le processus eux-mêmes. */
int main(int argc, char **argv) {
  int fileRequetesBus;
  int memoireEtatFeux;
  int memoireVoiesSortie;
  int semaphoreEtatFeux;
  int semaphoreVoiesSortie;
  
  memoireEtatFeux = initialiserMemoireEtatFeux();
  memoireVoiesSortie = initialiserMemoireVoiesSortie();
  fileRequetesBus = initialiserFileRequetesBus();
  semaphoreEtatFeux = initialiserSemaphoreEtatFeux();
  semaphoreVoiesSortie = initialiserSemaphoreVoiesSortie();

  if (fork() == 0) {
    initialiserDirections(fileRequetesBus, memoireEtatFeux, semaphoreEtatFeux, 
			  memoireVoiesSortie, semaphoreVoiesSortie);
  } else {
    gestionFeux(fileRequetesBus, memoireEtatFeux, semaphoreEtatFeux);
    wait(NULL);
    msgctl(fileRequetesBus, IPC_RMID, NULL);
    shmctl(memoireEtatFeux, IPC_RMID, NULL);
    shmctl(memoireVoiesSortie, IPC_RMID, NULL);
    semctl(semaphoreEtatFeux, 1, IPC_RMID);
  }

  return 0;
}

#endif
