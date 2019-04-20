#ifndef _VECINOS
#define _VECINOS

#include "Rii.h"

struct Vecinos {
	u32 nombre_del_vertice;//Nombre real del vertice actual.
	u32 ind_de_inicio_vecinos;//Del vertice actual.
	u32 ind_de_final_vecinos;//Del vertice actual.
	u32 color; //Color con el que esta pintado el vertice actual.
	u32 *array_vecinos;//Arreglos con los indices (indices en el arreglo G->orden) de los vecinos del vertice actual.
};
#endif

