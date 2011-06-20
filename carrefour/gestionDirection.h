#ifndef _GESTIONDIRECTION_H_
#define _GESTIONDIRECTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"
#include "fileVehicules.h"

/* Procédure de gestion d'une direction dir. Gère nombreVoiesVoiture
   voies de voitures et nombreVoiesBus voies de bus. 
   fileRequetesBus est un pointeur optionnel vers l'identifiant d'une
   file de messages qui sera remplie lorsqu'un bus veut passer. NULL
   si pas de files de bus. memoireEtatFeu est l'identifiant d'une zone
   de mémoire partagée dans laquelle sera indiqué le changement d'état
   des feux. tableDirections est un tableau de taille nombreVoiesVoiture
   + nombreVoiesBus tel que pour la voie numéro i, tableDirections[i]
   donne les directions possibles en sortant de cette voie. */
void gestionDirection(const direction dir, const int *fileRequetesBus,
		      const int memoireEtatFeu,
		      const int semaphoreEtatFeux,
		      const int nombreVoiesVoiture,
		      const direction * tableDirections,
		      const int nombreVoiesBus,
		      const int memoireVoiesSortie,
		      const int semaphoreVoiesSortie);

#endif
