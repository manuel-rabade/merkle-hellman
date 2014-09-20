/*
  Copyright 2008-2010 Manuel Rodrigo Rábade García <manuel@rabade.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "comun.h"
#include "descifra.h"

/* globales */
unsigned int vectorSI[8];      /* vector privado */
unsigned int cifrado[1024];    /* mensaje cifrado */

unsigned int multip;           /* multiplicador */
unsigned int multipI;          /* multiplicador inverso */
unsigned int modulo;           /* modulo */
char mensaje[1024];            /* mensaje */
char buffer[256];              /* buffer */

/* inicio */
int main (int argc, char * argv[]) {
  int tam;

  if (argc != 4) {
    printf("Error: argumentos incorrectos!\n");
    return 0;
  }

  tam = identificaVector(argv[3], cifrado);  
  identificaVector(argv[2], vectorSI);

  printf("Clave: %s\n", argv[1]);
  printf("Llave privada: %s\n", imprimeVector(vectorSI, 8, buffer));
  printf("Mensaje cifrado: %s\n\n", imprimeVector(cifrado, tam, buffer));

  calculaMMMI(argv[1]);
  descifra(argv[2], tam);
  
  printf("\nMensaje: %s\n", mensaje);

  return 1;
}

/* determina el multiplicador, modulo y multiplicador inverso */
void calculaMMMI (char clave[]) {
  char *ptr = clave;
  int i;
  unsigned int sumVectorSI;

  printf("Calculando multiplicador:\n");
  
  /* sumatoria ascii de la contraseña */
  multip = 0;
  while (*ptr != '\0') {
    multip += ((int) *ptr);
    printf("%c, %u (%u)\n", *ptr, (int) *ptr, multip);
    *ptr++;
  }
  printf("Multiplicador: %u\n\n", multip);

  printf("Calculando modulo:\n");
  
  /* sumatoria vector super incremental */
  sumVectorSI = 0;
  for (i = 0; i < 8; i++) {
    sumVectorSI += vectorSI[i];
    printf("%i, %u (%u)\n", i, vectorSI[i], sumVectorSI);
  }

  /* calculamos modulo */
  modulo = sumVectorSI + multip;
  printf("Modulo: %u\n\n", modulo);

  /* multiplicador inverso */
  multipI = moduloInverso(multip, modulo);
  printf("Multiplicador inverso: %u\n\n", multipI);
}

/* desciframos el mensaje */
void descifra (char str[], int tam) {
  int i, j;
  unsigned int tmp, ascii;
  printf("Calculando mensaje:\n");

  /* calculamos cada byte */
  for (i = 0; i < tam; i++) {
    printf("%u: %u -> ", i, cifrado[i]);

    /* regresamos el caracter */
    tmp = (cifrado[i] * multipI) % modulo;
    printf("%u = ", tmp);
    ascii = 0;
    /* sumamos bits activos */
    for (j=7; j >= 0; j--) {
      if (tmp >= vectorSI[j]) {
        tmp -= vectorSI[j];
        ascii = ascii + (int) pow(2,7 -j) ;
        printf("1");
      } else {
        printf("0");
      }
    }
    /* convertimos a caracter */
    mensaje[i] = (char) ascii;
    printf(" -> %u -> %c\n", ascii, mensaje[i]);
  }
}
