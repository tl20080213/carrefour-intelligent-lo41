OBJECTS = main.o gestionFeux.o gestionDirection.o
CFLAGS = -Wall -Werror

carrefour : $(OBJECTS)
	cc -o carrefour $(OBJECTS)

main.o : main.h
	cc -c main.c $(CFLAGS)

gestionFeux.o : gestionFeux.h
	cc -c gestionFeux.c $(CFLAGS)

gestionDirection.o : gestionDirection.h
	cc -c gestionDirection.c $(CFLAGS)

.PHONY : clean
clean : 
	rm carrefour $(OBJECTS) *.gch