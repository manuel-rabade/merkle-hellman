CFLAGS = -lm -pedantic -ansi

all: genera-llaves cifra descifra

genera-llaves: comun.o genera-llaves.c genera-llaves.h

cifra: comun.o cifra.c cifra.h

descifra: comun.o descifra.c descifra.h

comun: comun.c comun.h

clean: rm -f *.o genera-llaves cifra descifra
