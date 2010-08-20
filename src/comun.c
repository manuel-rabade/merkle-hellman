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

/* inverso del modulo */
int moduloInverso (int a, int n) {
  int i = n, v = 0, d = 1;
  while (a>0) {
    int t = i / a, x = a;
    a = i % x;
    i = x;
    x = d;
    d = v - t * x;
    v = x;
  }
  v %= n;
  if (v < 0) v = (v + n) % n;
  return v;
}


/* imprime un vector */
char *imprimeVector (unsigned int vector[], int max, char buffer[]) {
  char tmp[16];
  int i;

  *buffer = '\0';
  for (i = 0; i < (max - 1); i++) {
    sprintf(tmp, "%u,", vector[i]);
    strcat(buffer, tmp);
  }
  sprintf(tmp, "%u", vector[max - 1]);
  strcat(buffer, tmp);
  return buffer;
}

/* identificamos vectores  */
int identificaVector (char str[], unsigned int destino[]) {

  /* desarmamos str en varios */
  char escalaresStr[1024][10];
  char *ptr = str;
  int i,j, len;
  i = 0;
  j = 0;
  while (*ptr != '\0') {
    if (*ptr == ',') {
      escalaresStr[i][j] = '\0';
      j = 0;
      i++;
    } else {
      escalaresStr[i][j] = *ptr;
      j++;
    }
    ptr++;
  }
  /* longitud vector */
  len = i + 1;
  /* los convertimos a numero */
  for (i = 0; i < len; i++) {
    destino[i] = atoi(escalaresStr[i]);
  }
  return len;
}
