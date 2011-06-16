#ifndef _TYPES_H_
#define _TYPES_H_

/* Une direction du carrefour */
typedef enum direction {NORD = 1, SUD = 2, EST = 4, OUEST = 8} direction;

typedef struct vehicule {
  direction directionDepart;
  direction directionArrivee;
} vehicule;

typedef struct vehicule voiture;
typedef struct vehicule bus;

typedef enum feu { VERT_NORD_SUD, VERT_EST_OUEST } feu;

#define CAPACITE_VOIE_SORTIE 20

typedef struct voiesSortie {
  int nombreVehiculesOuest;
  int nombreVehiculesEst;
  int nombreVehiculesNord;
  int nombreVehiculesSud;
} voiesSortie;


typedef struct requeteBus {
  long type;
  direction contenantLeBus;
} requeteBus;

#endif
