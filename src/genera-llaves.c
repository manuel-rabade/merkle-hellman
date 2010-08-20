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
#include "comun.h"
#include "genera-llaves.h"

/* globales */
unsigned int vectorSI[8];  /* vector super incremental */
unsigned int vectorPub[8]; /* vector publico */
unsigned int multip;       /* multiplicador */
unsigned int modulo;       /* modulo */
char buffer[256];          /* buffer */
FILE *urandom;

/* inicio */
int main (int argc, char * argv[]) {
  
  if ((urandom = fopen("/dev/urandom", "r")) == NULL) {
    printf("error: no puedo abrir /dev/urandom!\n");
    return 0;
  }

  if (argv[1] == NULL) {
    printf("error: clave vacia!\n");
    return 0;
  }

  printf("clave: %s\n\n", argv[1]);

  generaVectorSI();
  calculaMM(argv[1]);
  calculaVectorPub();

  printf("llave privada: %s\n", imprimeVector(vectorSI, 8, buffer));
  printf("llave publica: %s\n", imprimeVector(vectorPub, 8, buffer));
  fclose(urandom);
  return 1;
}

/* genera el vector publico */
void calculaVectorPub () {
  int i;
  for (i = 0; i < 8; i++) {
    vectorPub[i] = (vectorSI[i] * multip) % modulo;
  }
}

/* calcula el multiplicador y el modulo */
void calculaMM (char clave[]) {
  char *ptr = clave;
  int i;
  unsigned int a, b, r, sumVectorSI;

  printf("calculando multiplicador:\n");

  /* sumatoria ascii de la contraseña */
  multip = 0;
  while (*ptr != '\0') {
    multip += ((int) *ptr);
    printf("%c, %u (%u)\n", *ptr, (int) *ptr, multip);
    *ptr++;
  }
  printf("multiplicador: %u\n\n", multip);

  printf("calculando modulo:\n");

  /* sumatoria vector super incremental */
  sumVectorSI = 0;
  for (i = 0; i < 8; i++) {
    sumVectorSI += vectorSI[i];
    printf("%i, %u (%u)\n", i, vectorSI[i], sumVectorSI);    
  }

  /* calculamos modulo */
  modulo = sumVectorSI + multip;
  printf("modulo: %u\n\n", modulo);
  
  /* verificamos multiplicador y modulo sean primos entre si */
  a = modulo;
  b = multip;
  r = a % b;
  while (r != 0) {
    a = b;
    b = r;
    r = a % b;
  }
  if (b != 1) {
    printf("error: el multiplicador y modulo no son primos entre si, mcd: %u\n\n", b);
    generaVectorSI();
    calculaMM(clave);
  }
}

/* genera el vector super incremental */
void generaVectorSI (void) {
  unsigned int i, j, sumVectorSI;

  printf("generando vector super incremental:\n");

  /* inicamos con un byte aletorio */
  vectorSI[0] = aleatorio();
  printf("%i, %u (%u)\n", 0, vectorSI[0], 0);

  /* demas bytes */
  for (i = 1; i < 8; i++) {
    sumVectorSI = 0;
    /* calculamos suma de los escalares previos */
    for (j = 0; j < i; j++) {
      sumVectorSI += vectorSI[j];
    }
    /* calculamos nuevo escalar */
    vectorSI[i] = vectorSI[i - 1] + aleatorio();
    while (vectorSI[i] < sumVectorSI) {
      vectorSI[i] = vectorSI[i] + aleatorio();
    }
    printf("%i, %u (%u)\n", i, vectorSI[i], sumVectorSI);
  }
printf("\n");
}

/* byte aleatorio de urandom */
int aleatorio (void) {
  int caracter;
  if ((caracter = fgetc(urandom)) == EOF) {
    printf("error: no hay numeros aleatorios!\n");
    return 0;    
  } 
  return caracter;
}

