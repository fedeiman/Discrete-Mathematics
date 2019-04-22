#ifndef _ORDEN
#define _ORDEN

#include "Rii.h"

struct Ordenes {
  u32 nombre;//Nombre real del vertice actual.
  u32 color_actual; //Color del vertice. 
  u32 cant_vecinos;//cantidad de vecinos del arreglo.
  u32 *array_vecinos; //arreglo con los indices de los vecinos.
};
#endif