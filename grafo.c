#include "Rii.h"

struct GrafoSt {
	u32 n; //numero de vertices
	u32 m; //numero de aristas
	u32 **vertices; // matriz con los vertices y sus vecinos 
	u32 color; // numero de colores
	u32 *orden; // arreglo con el orden de los vertices de menor a mayor.
	u32 *colores; // arreglo con los colores
};
