#ifndef _GESTIONFEUX_H_
#define _GESTIONFEUX_H_

/* Procédure de gestion des feux du carrefour. filesRequetesBus[direction] 
   est l'identifiant d'une file de messages contenant les demandes de 
   passage au vert des bus de la direction direction. memoireEtatFeu est
   l'identifiant d'une zone de mémoire partagée dans laquelle on indiquera
   les changements d'état des feux. */
void gestionFeux(const int fileRequetesBus, const int memoireEtatFeu,
		 const int semaphoreEtatFeux);

#endif
