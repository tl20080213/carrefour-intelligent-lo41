OBJECTS = main.o gestionFeux.o gestionDirection.o fileVehicules.o
CFLAGS = -Wall -Werror -std=c89 -D_XOPEN_SOURCE=600 -ggdb

carrefour : $(OBJECTS)
	cc -o carrefour $(OBJECTS)

main.o : main.h
	cc -c main.c $(CFLAGS)

gestionFeux.o : gestionFeux.h
	cc -c gestionFeux.c $(CFLAGS)

gestionDirection.o : gestionDirection.h
	cc -c gestionDirection.c $(CFLAGS)

fileVehicules.o : fileVehicules.h
	cc -c fileVehicules.c $(CFLAGS)

.PHONY : clean
clean : 
	rm carrefour $(OBJECTS) *.gch