Sistema de cifrado Merkle–Hellman
=================================

Proyecto final del curso **Estructuras discretas** impartido en la
[Facultad de Ingeniería](http://ingenieria.unam.mx) de la [Universidad
Nacional Autónoma de México](http://unam.mx).

El objetivo de este proyecto es implementar en [lenguaje
C](http://es.wikipedia.org/wiki/C_(lenguaje_de_programaci%C3%B3n)) el
[sistema de cifrado
Merkle-Hellman](http://es.wikipedia.org/wiki/Criptosistema_de_Merkle-Hellman)
con fines didacticos.

Para más información consulta el documento [Implementación del sistema
de cifrado Merkle-Hellman](doc/implementacion_merkle-hellman.pdf) que
acompaña a este proyecto.

Compilación
-----------

```shell
src $ make
cc -lm -pedantic -ansi   -c -o comun.o comun.c
cc -lm -pedantic -ansi    genera-llaves.c comun.o genera-llaves.h   -o genera-llaves
cc -lm -pedantic -ansi    cifra.c comun.o cifra.h   -o cifra
cc -lm -pedantic -ansi    descifra.c comun.o descifra.h   -o descifra
```

Ejecución
---------

**Generacion de llaves**

```bash
src $ ./genera-llaves hola123
clave: hola123

generando vector super incremental:
0, 20 (0)
1, 45 (20)
2, 150 (65)
3, 369 (215)
4, 656 (584)
5, 1390 (1240)
6, 2637 (2630)
7, 5384 (5267)

calculando multiplicador:
h, 104 (104)
o, 111 (215)
l, 108 (323)
a, 97 (420)
1, 49 (469)
2, 50 (519)
3, 51 (570)
multiplicador: 570

calculando modulo:
0, 20 (20)
1, 45 (65)
2, 150 (215)
3, 369 (584)
4, 656 (1240)
5, 1390 (2630)
6, 2637 (5267)
7, 5384 (10651)
modulo: 11221

llave privada: 20,45,150,369,656,1390,2637,5384
llave publica: 179,3208,6953,8352,3627,6830,10697,554
```

**Cifrado**

```shell
src $ ./cifra "hola mundo" 1319,15715,24232,1512,24326,24712,4149,21832
mensaje: hola mundo
llave publica: 1319,15715,24232,1512,24326,24712,4149,21832

calculando mensaje cifrado:
0: h -> 104 = 00010110 -> 64273
1: o -> 111 = 11110110 -> 114966
2: l -> 108 = 00110110 -> 88985
3: a -> 97 = 10000110 -> 61779
4:   -> 32 = 00000100 -> 24232
5: m -> 109 = 10110110 -> 110817
6: u -> 117 = 10101110 -> 88003
7: n -> 110 = 01110110 -> 93134
8: d -> 100 = 00100110 -> 64659
9: o -> 111 = 11110110 -> 114966

mensaje cifrado: 64273,114966,88985,61779,24232,110817,88003,93134,64659,114966

**Descifrado**

```shell
src $ ./descifra hola123 48,256,408,825,1596,3150,6449,12739 64273,114966,88985,61779,24232,110817,88003,93134,64659,114966
Clave: hola123
Llave privada: 48,256,408,825,1596,3150,6449,12739
Mensaje cifrado: 64273,114966,88985,61779,24232,110817,88003,93134,64659,114966

Calculando multiplicador:
h, 104 (104)
o, 111 (215)
l, 108 (323)
a, 97 (420)
1, 49 (469)
2, 50 (519)
3, 51 (570)
Multiplicador: 570

Calculando modulo:
0, 48 (48)
1, 256 (304)
2, 408 (712)
3, 825 (1537)
4, 1596 (3133)
5, 3150 (6283)
6, 6449 (12732)
7, 12739 (25471)
Modulo: 26041

Multiplicador inverso: 20513

Calculando mensaje:
0: 64273 -> 2260 = 00010110 -> 104 -> h
1: 114966 -> 24598 = 11110110 -> 111 -> o
2: 88985 -> 5410 = 00110110 -> 108 -> l
3: 61779 -> 13403 = 10000110 -> 97 -> a
4: 24232 -> 408 = 00000100 -> 32 ->  
5: 110817 -> 18149 = 10110110 -> 109 -> m
6: 88003 -> 17378 = 10101110 -> 117 -> u
7: 93134 -> 11859 = 01110110 -> 110 -> n
8: 64659 -> 3814 = 00100110 -> 100 -> d
9: 114966 -> 24598 = 11110110 -> 111 -> o

Mensaje: hola mundo
```

Autor
-----

Manuel Rábade <[manuel@rabade.net](mailto:manuel@rabade.net)>

Licencia
--------

Esta obra está bajo una [Licencia Pública General de GNU](LICENSE.txt).
