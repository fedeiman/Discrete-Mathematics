#ifndef _MAIN
#define _MAIN

//#include "construccion.c"
#include "grafo.c"
#include "vecinos.c"
#include "orden.c"
//#include "greedy.c"
int main(){
	Grafo g;
	u32 j;
	g = ConstruccionDelGrafo();
	OrdenWelshPowell(g);
	j = Greedy(g);
	printf("%u\n",j);
	DestruccionDelGrafo(g);

}
#endif