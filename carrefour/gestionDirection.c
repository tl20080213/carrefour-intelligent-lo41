#ifndef _GESTIONDIRECTION_C_
#define _GESTIONDIRECTION_C_

#include "gestionDirection.h"

/* La probabilité qu'une voiture arrive dans une direction donnée. */
#define PROBA_ARRIVEE_VOITURE 0.75
/* La probabilité qu'un bus arrive dans une directions donnée. */
#define PROBA_ARRIVEE_BUS     0.25
/* La probabilité qu'un véhicule puisse sortir de sa voie de sortie. */
#define PROBA_SORTIE_VEHICULE 0.5

#define CAPACITE_VOIE_ENTREE  20

/* Gère la direction dir, avec nombreVoiesVoiture voies de voitures et nombreVoiesBus
   voies de bus. Les directions de la voie de voiture numero i est donnée dans
   tableDirections[i], et les direction de la voie de bus numero j est donnée dans
   tableDirections[nombreVoiesVoiture + j], où i et j commencent à zero. */
void gestionDirection(const direction dir, const int *fileRequetesBus, 
		      const int memoireEtatFeu,	const int semaphoreEtatFeux,
		      const int nombreVoiesVoiture, const direction *tableDirections,
		      const int nombreVoiesBus, const int memoireVoiesSortie,
		      const int semaphoreVoiesSortie) {
  
}

#endif
