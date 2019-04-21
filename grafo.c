#ifndef _GRAFO
#define _GRAFO

#include "Rii.h"

struct GrafoSt {
	u32 n; //numero de vertices.
	u32 m; //numero de aristas.
	u32 colores; //numero de colores.
	Vecino *v; //puntero a estructura vecinos.
	Orden *o; //Puntero a estructura con el orden de vecinos "Correcto".
};
#endif