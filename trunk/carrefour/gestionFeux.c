#ifndef _GESTIONFEUX_C_
#define _GESTIONFEUX_C_


#include "gestionFeux.h"

void gestionFeux(const int fileRequetesBus, const int memoireEtatFeu, const int semaphoreEtatFeux, const int memoireVoiesSortie, const int semaphoreVoiesSortie) {
		 
  requeteBus requete;
  requete.type=42;
  
  feu *etatFeu = NULL;
  etatFeu = shmat(memoireEtatFeu, NULL, 0);
  
  voiesSortie *etatVoiesSortie = NULL;
  etatVoiesSortie = shmat(memoireVoiesSortie, NULL, 0);
  
  
  /*int modulo;
  
  struct timespec tempsDebut;
  clock_gettime(CLOCK_REALTIME,&tempsDebut);*/
  
  while (1) {
    while(msgrcv(fileRequetesBus, &requete, 5, requete.type, IPC_NOWAIT)==-1) {
      
      /*struct timespec tempsFin;
      clock_gettime(CLOCK_REALTIME,&tempsFin);
      
      modulo=tempsFin.tv_sec-tempsDebut.tv_sec;
      printf("temps = %f sec \n", temps);
      printf("tempsDebut = %f sec \n", tempsDebut);
      printf("tempsFin = %f sec \n", tempsFin);
      printf("modulo =  %d \n", modulo);*/
      if(0) {
        P(semaphoreEtatFeux);
        if(*etatFeu==VERT_EST_OUEST) {
          *etatFeu=VERT_NORD_SUD;
          printf("Vert au FEU NORD SUD");
        }
        else if(*etatFeu==VERT_NORD_SUD) {
          *etatFeu=VERT_EST_OUEST;
          printf("Vert au FEU EST OUEST");
        }
        P(semaphoreVoiesSortie);
        etatVoiesSortie->nombreVehiculesOuest = 0;
        etatVoiesSortie->nombreVehiculesEst = 0;
        etatVoiesSortie->nombreVehiculesSud = 0;
        etatVoiesSortie->nombreVehiculesNord = 0;
        printf("Capacités sortie mises à 0");
        V(semaphoreVoiesSortie);
        V(semaphoreEtatFeux);
      }
    }
    P(semaphoreEtatFeux);
    if(requete.contenantLeBus==1) {
      if(*etatFeu==VERT_EST_OUEST) {
       *etatFeu=VERT_NORD_SUD;
       printf("Changement Feu VERT_NORD_SUD suite à une demande de bus");
      }
    }
    else if(requete.contenantLeBus==2) {
      if(*etatFeu==VERT_EST_OUEST) {
        *etatFeu=VERT_NORD_SUD;
        printf("Changement Feu VERT_NORD_SUD suite à une demande de bus");
      }
    }
    else if(requete.contenantLeBus==4) {
      if(*etatFeu==VERT_NORD_SUD) {
        *etatFeu=VERT_EST_OUEST;
        printf("Changement Feu VERT_EST_OUEST suite à une demande de bus");
      }
    }
    else if(requete.contenantLeBus==8) {
      if(*etatFeu==VERT_NORD_SUD) {
        *etatFeu=VERT_EST_OUEST;
        printf("Changement Feu VERT_EST_OUEST suite à une demande de bus");
      }
    }
    P(semaphoreVoiesSortie);
    etatVoiesSortie->nombreVehiculesOuest = 0;
    etatVoiesSortie->nombreVehiculesEst = 0;
    etatVoiesSortie->nombreVehiculesSud = 0;
    etatVoiesSortie->nombreVehiculesNord = 0;
    printf("Capacités sortie mises à 0");
    V(semaphoreVoiesSortie);
    V(semaphoreEtatFeux);
  }
		 
  return;
}


#endif
