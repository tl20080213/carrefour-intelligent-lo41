/*
  Module principale du programme.
 */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>

#include "gestionFeux.h"
#include "gestionDirection.h"

int main(int argc, char **argv);

#endif
