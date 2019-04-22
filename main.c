#ifndef _MAIN
#define _MAIN

//#include "construccion.c"
#include "grafo.c"
#include "vecinos.c"
#include "orden.c"
//#include "greedy.c"
int main(){
	Grafo g;
	Grafo h;
	g = ConstruccionDelGrafo();
	h = CopiarGrafo(g);
	for(u32 i = 0; i<g->n;i++){
		printf("%u",g->v[i]->nombre_del_vertice);
	}
	Greedy(g);
	Greedy(h);
	printf("\n");
	RMBCchicogrande(h);
	for(u32 i = 0; i<g->n;i++){
		printf("%u",g->v[i]->nombre_del_vertice);
	}
	printf("\n");
	DestruccionDelGrafo(g);
	DestruccionDelGrafo(h);

}
#endif