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
void initialiserDirections(int fileRequetesBus, int memoireEtatFeux) {
  const direction directionsSud[3] = {OUEST, NORD, EST};
  const direction directionsNord[3] = {EST|SUD, SUD, OUEST|SUD};
  const direction directionsOuest[3] = {EST, EST|SUD, EST|SUD};
  const direction directionsEst[3] = {OUEST, OUEST|NORD, OUEST|NORD};
  int i;

  if (fork() == 0) {
    gestionDirection(SUD, NULL, memoireEtatFeux, 3, directionsSud, 0);
  } else if (fork() == 0) {
    gestionDirection(NORD, NULL, memoireEtatFeux, 3, directionsNord, 0);
  } else if (fork() == 0) {
    gestionDirection(OUEST, &fileRequetesBus, memoireEtatFeux, 2, directionsOuest, 1);
  } else {
    gestionDirection(EST, &fileRequetesBus, memoireEtatFeux, 2, directionsEst, 1);
    for (i = 1; i <= 3; i++) {
      wait(NULL);
    }
  }
}

/* Initialise les moyens de communications entre les processus
   et le processus eux-mêmes. */
int main(int argc, char **argv) {
  int fileRequetesBus;
  int memoireEtatFeux;
  
  memoireEtatFeux = initialiserMemoireEtatFeux();
  fileRequetesBus = initialiserFileRequetesBus();

  if (fork() == 0) {
    initialiserDirections(fileRequetesBus, memoireEtatFeux);
  } else {
    gestionFeux(&fileRequetesBus, memoireEtatFeux);
    wait(NULL);
    msgctl(fileRequetesBus, IPC_RMID, NULL);
    shmctl(memoireEtatFeux, IPC_RMID, NULL);
  }

  return 0;
}

#endif
