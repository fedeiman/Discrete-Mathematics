#ifndef _MAIN
#define _MAIN

//#include "construccion.c"
#include "grafo.c"
#include "vecinos.c"
#include "orden.c"
int main(){
	Grafo g;

	Grafo h;
	g = ConstruccionDelGrafo();
	//int n;
	h = CopiarGrafo(g);
	for(u32 i = 0; i < g->n; i++){
		printf("%u",g->v[i]->total_vecinos);		
	}
	printf("\n");
	for(u32 i = 0; i < g->n; i++){
		printf("%u",h->v[i]->total_vecinos);
	}
	for(u32 i = 0; i < g->n; i++){
		printf("%u",g->v[i]->nombre_del_vertice);
	}
	printf("\n");
	OrdenWelshPowell(g);
	for(u32 i = 0; i < g->n; i++){
		printf("%u",g->v[i]->nombre_del_vertice);
	}
	printf("\n");
	printf("%u\n",g->v[0]->total_vecinos);
	printf("%u\n",g->v[1]->total_vecinos);
	SwitchVertices(g,0,1);
	for(u32 i = 0; i < g->n; i++){
		printf("%u",g->v[i]->nombre_del_vertice);
	}
	printf("\n");
	//u32 n = NombreJotaesimoVecino(g,1,1);
	//u32 j = GradoDelVertice(g,3);
	//printf("%u\n",j);
	//printf("%u\n",n);
	printf("%u\n",g->v[0]->total_vecinos);
	printf("%u\n",g->v[1]->total_vecinos);
	g->colores = 200;
	g->o[0]->color_actaul = 10;
	g->o[1]->color_actaul = 56;
	g->o[2]->color_actaul = 56;
	printf("color init %u\n",g->o[1]->color_actaul);
	printf("color init %u\n",g->o[0]->color_actaul);
	printf("color init %u\n",g->o[2]->color_actaul);
	SwitchColores(g,10,56);
	printf("color switch %u\n",g->o[1]->color_actaul);
	printf("color switch %u\n",g->o[0]->color_actaul);
	printf("color init %u\n",g->o[2]->color_actaul);
	DestruccionDelGrafo(h);
	DestruccionDelGrafo(g);

}
#endif