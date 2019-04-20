#ifndef _MAIN
#define _MAIN

//#include "construccion.c"
#include "grafo.c"
#include "vecinos.c"
int main(){
	Grafo g;
	g = ConstruccionDelGrafo();
		printf("%u\n",g->v[1]->ind_de_final_vecinos);
		DestruccionDelGrafo(g);
	
}
#endif