/*
  Copyright 2008-2010 Manuel Rábade <manuel@rabade.net>

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
#include "cifra.h"

/* globales */
unsigned int vectorPub[8];  /* vector publico */
unsigned int cifrado[1024]; /* mensaje cifrado */
char buffer[256];           /* buffer */

/* inicio */
int main (int argc, char * argv[]) {
  int tam;
  
  if (argc != 3) {
    printf("error: argumentos incorrectos!\n");
  }

  tam = strlen(argv[1]);
  identificaVector(argv[2], vectorPub);

  printf("mensaje: %s\n", argv[1]);
  printf("llave publica: %s\n\n", imprimeVector(vectorPub, 8, buffer));

  cifra(argv[1], tam);
  
  printf("\nmensaje cifrado: %s\n", imprimeVector(cifrado, tam, buffer));

  return 1;
}

/* ciframos el mensaje */
void cifra (char str[], int tam) {
  int i, j;

  printf("calculando mensaje cifrado:\n");

  /* examinamos toda la cadena */
  for (i = 0; i < tam; i++) {
    printf("%u: %c -> %u = ", i, str[i], (int) str[i]);
    /* checamos todos los bits */
    for (j = 0; j < 8; j++) {
      int bit;
      bit = (int) pow(2,j);
      /* sumamos bits activos */
      if ((str[i] & bit) == bit) {
        cifrado[i] += vectorPub[7-j];
        printf("1");
      } else {
        printf("0");
      }
    }
    printf(" -> %u\n", cifrado[i]);
  }
}

