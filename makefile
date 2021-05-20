###
## Makefile
## INFO0030: Projet 3
###

#A SUPP
#--std=c99 --pedantic -Wall -W -Wmissing-prototypes			QUELQUECHOSE A RAJOUTER POUR GTK (premier podcast)
#
#gcc -o main main.c
#
#

# Tools & flags
CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN_CONFIG=Doxyfile

#variables
all : clean five

#advanced & basic

#a enlever apres
five : main.o controleur.o vue.o modele.o utils.o
	$(LD) -o five main.o controleur.o vue.o modele.o utils.o $(LDFLAGS) $(GTKFLAGS)
#enlever jusqu'ici

main.o: source/main.c source/vue.h source/controleur.h source/modele.h source/utils.h
	$(CC) -c source/main.c -o main.o $(CFLAGS) $(GTKFLAGS)

controleur.o: source/controleur.h source/controleur.c source/vue.h source/modele.h source/utils.h
	$(CC) -c source/controleur.c -o controleur.o $(CFLAGS) $(GTKFLAGS)

vue.o: source/vue.h source/vue.c source/controleur.h source/modele.h source/utils.h
	$(CC) -c source/vue.c -o vue.o $(CFLAGS) $(GTKFLAGS)

modele.o: source/modele.h source/modele.c source/utils.h
	$(CC) -c source/modele.c -o modele.o $(CFLAGS) $(GTKFLAGS)

utils.o: source/utils.h source/utils.c
	$(CC) -c source/utils.c -o utils.o $(CFLAGS) $(GTKFLAGS)

#documentation
doc:
		doxygen $(DOXYGEN_CONFIG)

rapport:
	pdflatex rapport/rapport_projet4_24.tex

.PHONY: doc

#clean
clean:
	rm -f *.o
	rm -f five
	clear

archive: doc
	tar -zcvf five_24.tar.gz makefile source doc Doxyfile rapport
