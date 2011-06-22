#ifndef _FILE_VEHICULES_C_
#define _FILE_VEHICULES_C_

#include "fileVehicules.h"

fileVehicules *fileVide(size_t capacite) {
  fileVehicules *resultat = NULL;

  resultat = malloc(sizeof(fileVehicules));
  if (resultat == NULL) {
    fprintf(stderr,
	    "fileVehicules.c : fileVide : malloc : erreur d'allocation.");
    exit(EXIT_FAILURE);
  }
  resultat->vehicules = malloc(capacite * sizeof(vehicule));
  if (resultat->vehicules == NULL) {
    fprintf(stderr,
	    "fileVehicules.c : fileVide : malloc : erreur d'allocation.");
    exit(EXIT_FAILURE);
  }
  resultat->capacite = capacite;
  resultat->taille = 0;

  return resultat;
}

void freeFileVehicules(fileVehicules * file) {
  free(file->vehicules);
  free(file);
}

size_t capaciteFile(fileVehicules file) {
  return file.capacite;
}

size_t tailleFile(fileVehicules file) {
  return file.taille;
}

int estVide(fileVehicules file) {
  return tailleFile(file) == 0;
}

int estPleine(fileVehicules file) {
  return tailleFile(file) == capaciteFile(file);
}

static void decalerFileADroite(fileVehicules * file) {
  int i = 0;

  file->taille++;
  for (i = tailleFile(*file) - 1; i >= 1; i--) {
    file->vehicules[i] = file->vehicules[i - 1];
  }
}

int ajouterVehiculeQueue(fileVehicules * file, vehicule aAjouter) {
  if (file == NULL || estPleine(*file)) {
    return 0;
  } else {
    decalerFileADroite(file);
    file->vehicules[0] = aAjouter;
    return 1;
  }
}

vehicule vehiculeTete(fileVehicules file) {
  if (estVide(file)) {
    fprintf(stderr,
	    "fileVehicules.c : vehiculeTete : la file en argument est vide.\n");
    exit(EXIT_FAILURE);
  } else {
    return file.vehicules[tailleFile(file) - 1];
  }
}

vehicule retirerVehiculeTete(fileVehicules * file) {
  vehicule resultat;

  if (file == NULL) {
    fprintf(stderr,
	    "fileVehicules.c : retirerVehiculeTete : la file en argument est NULL.\n");
    exit(EXIT_FAILURE);
  } else {
    resultat = vehiculeTete(*file);
    file->capacite--;
    return resultat;
  }
}

static char *directionToString(direction dir) {
  char *resultat;

  resultat = malloc(7*sizeof(char));
  if (dir == NORD) {
    strcpy(resultat, "nord");
  } else if (dir == SUD) {
    strcpy(resultat, "sud");
  } else if (dir == OUEST) {
    strcpy(resultat, "ouest");
  } else if (dir == EST) {
    strcpy(resultat, "est");
  }

  return resultat;
}

char *vehiculeToString(vehicule v, int bus) {
  char *resultat;
  char *directionDepart;
  char *directionArrivee;

  resultat = malloc(50 * sizeof(char));
  directionDepart = directionToString(v.directionDepart);
  directionArrivee = directionToString(v.directionArrivee);

  if (bus) {
    sprintf(resultat, "Bus : { directionDepart = %s, directionArrivee = %s }", 
	    directionDepart, directionArrivee);
  } else {
    sprintf(resultat, "Voiture : { directionDepart = %s, directionArrivee = %s }",
	    directionDepart, directionArrivee);
  }
  free(directionDepart);
  free(directionArrivee);

  return resultat;
}

char *fileVehiculesToString(fileVehicules file, int bus) {
  int i;
  int taille = 0;
  char **vehiculesStrings;
  char *resultat;

  vehiculesStrings = malloc(tailleFile(file) * sizeof(char*));

  for (i = 0; i < tailleFile(file); i++) {
    vehiculesStrings[i] = vehiculeToString(file.vehicules[i], bus);
    taille += strlen(vehiculesStrings[i]);
  }

  resultat = malloc(taille * sizeof(char));
  if (bus) {
    strcpy(resultat, "File de bus : [");
  } else {
    strcpy(resultat,"File de voitures : [");
  }

  for (i = 0; i < tailleFile(file); i++) {
    strcat(resultat, vehiculesStrings[i]);
    if (i < tailleFile(file) - 1) {
      strcat(resultat, ", ");
    }
    free(vehiculesStrings[i]);
  }
  strcat(resultat, "]");
  free(vehiculesStrings);

  return resultat;
}

#endif
