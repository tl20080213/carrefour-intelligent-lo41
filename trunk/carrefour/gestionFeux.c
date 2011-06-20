#ifndef _GESTIONFEUX_C_
#define _GESTIONFEUX_C_


#include "gestionFeux.h"

void gestionFeux(const int fileRequetesBus, const int memoireEtatFeu, const int semaphoreEtatFeux, const int memoireVoiesSortie, const int semaphoreVoiesSortie) {
		 
  requeteBus requete;
  requete.type=42;
  feu *etat = NULL;
  etat = shmat(memoireEtatFeu, NULL, 0);
  clock_t tempsDebut;
  
  while (1) {
     tempsDebut=clock();
    
    while(msgrcv(fileRequetesBus, &requete, 5, requete.type, IPC_NOWAIT)==-1) {
      if(((clock()-tempsDebut)/CLOCKS_PER_SEC)%7==0) {
        if(*etat==VERT_EST_OUEST) {
          *etat=VERT_NORD_SUD;
        }
        else if(*etat==VERT_NORD_SUD) {
          *etat=VERT_EST_OUEST;
        }
      }
    }
    
    if(requete.contenantLeBus==1) {
      if(*etat==VERT_EST_OUEST) {
       *etat=VERT_NORD_SUD;
      }
    }
    else if(requete.contenantLeBus==2) {
      if(*etat==VERT_EST_OUEST) {
        *etat=VERT_NORD_SUD;
      }
    }
    else if(requete.contenantLeBus==4) {
      if(*etat==VERT_NORD_SUD) {
        *etat=VERT_EST_OUEST;
      }
    }
    else if(requete.contenantLeBus==8) {
      if(*etat==VERT_NORD_SUD) {
        *etat=VERT_EST_OUEST;
      }
    }
    
  }
		 
  return;
}


#endif
