OBJECTS = main.o
CFLAGS = -Wall -Werror

carrefour : $(OBJECTS)
	cc -o carrefour $(OBJECTS)

main.o : main.h
	cc -c main.c $(CFLAGS)

.PHONY : clean
clean : 
	rm carrefour $(OBJECTS)