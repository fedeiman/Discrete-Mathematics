#ifndef _MAIN
#define _MAIN

//#include "construccion.c"
#include "grafo.c"
#include "vecinos.c"
int main(){
	Grafo g;
	Grafo h;
	g = ConstruccionDelGrafo();
	h = CopiarGrafo(g);
	for(u32 i = 0; i < h->n; i++){
		u32 contador = 0;
		u32 cantidad = h->v[i]->ind_de_final_vecinos - h->v[i]->ind_de_inicio_vecinos + 1;
		while(cantidad > contador){
		printf("El valor de indice de los vecinos de %u es %u\n",h->v[i]->nombre_del_vertice,h->v[i]->array_vecinos[contador]);
		contador++;
		}
	}
	for(u32 i = 0; i < h->n; i++){
		printf("El valor de incio de los vecinos de %u es %u\n" ,h->v[i]->nombre_del_vertice,h->v[i]->ind_de_inicio_vecinos);
		printf("El valor de final de los vecinos de %u es %u\n" ,h->v[i]->nombre_del_vertice,h->v[i]->ind_de_final_vecinos);
	}

	printf("\n");

	for(u32 i = 0; i < h->n; i++){
		printf("%u ",h->v[i]->nombre_del_vertice);
	}

	printf("\n");
	printf("\n");
	
		printf("\n");
	DestruccionDelGrafo(g);
	DestruccionDelGrafo(h);

}
#endif