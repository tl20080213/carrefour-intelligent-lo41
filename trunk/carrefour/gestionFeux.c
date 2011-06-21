#ifndef _GESTIONFEUX_C_
#define _GESTIONFEUX_C_


#include "gestionFeux.h"

void gestionFeux(const int fileRequetesBus, const int memoireEtatFeu, int semaphoreEtatFeux, const int memoireVoiesSortie, int semaphoreVoiesSortie, int semaphoreChangementFeux) {
		 
  requeteBus requete;
  requete.type=42;
  
  feu *etatFeu = NULL;
  etatFeu = shmat(memoireEtatFeu, NULL, 0);
  
  voiesSortie *etatVoiesSortie = NULL;
  etatVoiesSortie = shmat(memoireVoiesSortie, NULL, 0);
  
  int ok;
  ok=0;
  int modulo;
  
  struct timespec tempsDebut;
  clock_gettime(CLOCK_REALTIME,&tempsDebut);
  
  while (1) {
    while(msgrcv(fileRequetesBus, &requete, 5, requete.type, IPC_NOWAIT)==-1) {
      struct timespec tempsFin;
      clock_gettime(CLOCK_REALTIME,&tempsFin);
      
      modulo=(int) (tempsFin.tv_sec-tempsDebut.tv_sec);
      modulo=modulo%7;
     
      if(modulo==6) {
        ok=1;
      }
      if(modulo==0) {
        if(ok==1) {
            ok=0;
            printf("AVANT semaphore SemaphoreEtatFeu = %d \n",semaphoreEtatFeux);
            P(semaphoreEtatFeux);
            printf("APRES semaphore SemaphoreEtatFeu = %d \n",semaphoreEtatFeux);
            if(*etatFeu==VERT_EST_OUEST) {
              *etatFeu=VERT_NORD_SUD;
              printf("Vert au FEU NORD SUD\n");
              V(semaphoreChangementFeux);
            }
            else if(*etatFeu==VERT_NORD_SUD) {
              *etatFeu=VERT_EST_OUEST;
              printf("Vert au FEU EST OUEST\n");
              V(semaphoreChangementFeux);
            }
            P(semaphoreVoiesSortie);
            etatVoiesSortie->nombreVehiculesOuest = 0;
            etatVoiesSortie->nombreVehiculesEst = 0;
            etatVoiesSortie->nombreVehiculesSud = 0;
            etatVoiesSortie->nombreVehiculesNord = 0;
            printf("Capacités sortie mises à 0\n");
            V(semaphoreVoiesSortie);
            V(semaphoreEtatFeux);
        }
      }
    }
    printf("Demande d'un bus\n");
    P(semaphoreEtatFeux);
    if(requete.contenantLeBus==1) {
      if(*etatFeu==VERT_EST_OUEST) {
       *etatFeu=VERT_NORD_SUD;
       printf("Changement Feu VERT_NORD_SUD suite à une demande de bus\n");
       V(semaphoreChangementFeux);
      }
    }
    else if(requete.contenantLeBus==2) {
      if(*etatFeu==VERT_EST_OUEST) {
        *etatFeu=VERT_NORD_SUD;
        printf("Changement Feu VERT_NORD_SUD suite à une demande de bus\n");
        V(semaphoreChangementFeux);
      }
    }
    else if(requete.contenantLeBus==4) {
      if(*etatFeu==VERT_NORD_SUD) {
        *etatFeu=VERT_EST_OUEST;
        printf("Changement Feu VERT_EST_OUEST suite à une demande de bus\n");
        V(semaphoreChangementFeux);
      }
    }
    else if(requete.contenantLeBus==8) {
      if(*etatFeu==VERT_NORD_SUD) {
        *etatFeu=VERT_EST_OUEST;
        printf("Changement Feu VERT_EST_OUEST suite à une demande de bus\n");
        V(semaphoreChangementFeux);
      }
    }
    P(semaphoreVoiesSortie);
    etatVoiesSortie->nombreVehiculesOuest = 0;
    etatVoiesSortie->nombreVehiculesEst = 0;
    etatVoiesSortie->nombreVehiculesSud = 0;
    etatVoiesSortie->nombreVehiculesNord = 0;
    printf("Capacités sortie mises à 0\n");
    V(semaphoreVoiesSortie);
    V(semaphoreEtatFeux);
  }
		 
  return;
}


#endif
