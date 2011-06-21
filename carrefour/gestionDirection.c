#ifndef _GESTIONDIRECTION_C_
#define _GESTIONDIRECTION_C_

#include "gestionDirection.h"

/* Le nombre maximale de voiture qui peuvent arriver dans le carrfour
   par itération. */
#define NOMBRE_ARRIVEE_VOITURE_MAX 10
/* Le nombre maximale de bus qui peuvent arriver dans le carrfour
   par itération. */
#define NOMBRE_ARRIVEE_BUS_MAX 3
/* La probabilité qu'une voiture arrive dans une direction donnée. */
#define PROBA_ARRIVEE_VOITURE 0.75
/* La probabilité qu'un bus arrive dans une directions donnée. */
#define PROBA_ARRIVEE_BUS     0.25
/* La probabilité qu'un véhicule puisse sortir de sa voie de sortie. */
#define PROBA_SORTIE_VEHICULE 0.5
/* La capacité des voies d'entrée. */
#define CAPACITE_VOIE_ENTREE  20

/* Retourne un nouveau véhicule avec la direction de départ et la
   direction d'arrivée donnée en argument. */
vehicule nouveauVehicule(direction directionDepart,
			 direction directionArrivee) {
  vehicule resultat;

  resultat.directionDepart = directionDepart;
  resultat.directionArrivee = directionArrivee;

  return resultat;
}

/* Initialise les voies d'entrée à vide. */
fileVehicules **initialiserVoiesEntree(const int nombreDeVoies) {
  int i;
  fileVehicules **voiesEntree = NULL;

  voiesEntree = malloc(nombreDeVoies * sizeof(fileVehicules *));

  if (voiesEntree == NULL) {
    fprintf(stderr,
	    "gestionDirection.c : initialiserVoiesEntree : erreur d'initialisation.\n");
  }

  for (i = 0; i < nombreDeVoies; i++) {
    voiesEntree[i] = fileVide(CAPACITE_VOIE_ENTREE);
  }

  return voiesEntree;
}

/* Libère les ressources allouées au voies d'entrée. */
void libererVoiesEntree(fileVehicules ** voiesEntree, int nombreDeVoies) {
  int i;

  for (i = 0; i < nombreDeVoies; i++) {
    freeFileVehicules(voiesEntree[i]);
  }
  free(voiesEntree);
}

/* Retourne l'état du feu contenu dans la mémoire memoire et en protégeant la lecture par
   le sémaphore semaphore. */
feu lireEtatFeux(int memoire, int semaphore) {
  feu *etat = NULL;
  feu resultat;

  etat = shmat(memoire, NULL, 0);

  P(semaphore);
  resultat = *etat;
  V(semaphore);

  shmdt(etat);

  return resultat;
}

/* Attend le passage au vert du feu dans la direction dir, avec son état contenu 
   dans memoireEtatFeux et protégé par semaphoreEtatFeux. */
void attendrePassageAuVert(direction dir, int memoireEtatFeux,
			   int semaphoreEtatFeux) {
  int vert = 0;
  feu etatAttendu;

  if (dir == OUEST || dir == EST) {
    etatAttendu = VERT_EST_OUEST;
  } else {
    etatAttendu = VERT_NORD_SUD;
  }

  while (!vert) {
    sleep(1000);
    vert = lireEtatFeux(memoireEtatFeux, semaphoreEtatFeux) == etatAttendu;
  }
}

/* TODO */
void ajouterVehicules(const direction * tableDirections,
		      int nombreVoiesVoiture, int nombreVoiesBus,
		      fileVehicules ** voiesEntree) {
  return;
}

/* Gère la direction dir, avec nombreVoiesVoiture voies de voitures et nombreVoiesBus
   voies de bus. Les directions de la voie de voiture numero i est donnée dans
   tableDirections[i], et les direction de la voie de bus numero j est donnée dans
   tableDirections[nombreVoiesVoiture + j], où i et j commencent à zero.        
*/
void gestionDirection(const direction dir, const int *fileRequetesBus,
		      const int memoireEtatFeu,
		      const int semaphoreEtatFeux,
		      const int nombreVoiesVoiture,
		      const direction * tableDirections,
		      const int nombreVoiesBus,
		      const int memoireVoiesSortie,
		      const int semaphoreVoiesSortie,
		      const int semaphoreChangementFeux) {
  fileVehicules **voiesEntree =
      initialiserVoiesEntree(nombreVoiesVoiture + nombreVoiesBus);

  while (1) {
    ajouterVehicules(tableDirections, nombreVoiesVoiture, nombreVoiesBus,
		     voiesEntree);
    attendrePassageAuVert(dir, memoireEtatFeu, semaphoreEtatFeux);
  }

  libererVoiesEntree(voiesEntree, nombreVoiesVoiture + nombreVoiesBus);
}

#endif
