OBJECTS = main.o gestionFeux.o gestionDirection.o fileVehicules.o semaphore.o
CFLAGS = -Wall -Werror -std=c89 -D_XOPEN_SOURCE=600 -ggdb
LDFLAGS = -lrt

carrefour : $(OBJECTS)
	cc -o carrefour $(LDFLAGS) $(OBJECTS)

main.o : main.h
	cc -c main.c $(CFLAGS)

gestionFeux.o : gestionFeux.h
	cc -c gestionFeux.c $(CFLAGS)

gestionDirection.o : gestionDirection.h
	cc -c gestionDirection.c $(CFLAGS)

fileVehicules.o : fileVehicules.h
	cc -c fileVehicules.c $(CFLAGS)

semaphore.o : semaphore.h
	cc -c semaphore.c $(CFLAGS)

.PHONY : clean
clean : 
	rm carrefour $(OBJECTS) *.gch

.PHONY : indent
indent:
	indent -kr -br -brf -i2 *.c *.h
