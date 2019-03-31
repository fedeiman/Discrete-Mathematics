#ifndef _CONSTRUCCION
#define _CONSTRUCCION

#include  "grafo.c"
#include "vecinos.c"

int cmp(const void* a, const void* b) {						//Funcion para ordenar los vertices
    u32 *ap = *(u32**)a, *bp = *(u32**)b;					//usada en qsort
    u32 fsta = *ap, fstb = *bp;
    u32 snda = *(++ap), sndb = *(++bp);
    if(fsta == fstb) return snda - sndb;
    else return fsta - fstb;
}
int main(){
	Grafo g = (Grafo)malloc(sizeof(struct GrafoSt)); 		//Declaro variable de tipo Grafo
	printf("numero de vertices:"); 			  				//Pido y 
	if(scanf("%u",&g->n) < 0) return 1;			  			//guardo n° de vertices
	printf("numero de aristas:"); 			  				//Pido y 
	if(scanf("%u",&g->m) < 0) return 1;           			//guardo n° de aristas
	g->vertices = (u32**)malloc((2*(g->m))*sizeof(u32*));   //g->vertices = array de 2*(g->m) punteros de u32
	for(u32 i = 0; i < 2*(g->m) ; i++){						//Para cada puntero 
        g->vertices[i] = (u32*)malloc(2*sizeof(u32));		//le asigno un array de 2 de u32
	}														
	for(u32 i = 0; i < g->m; i++){ 							//Para cada fila de la matriz 
		printf("conexiones:");								//completo las aristas
		if (scanf("%u", &g->vertices[i][0]) < 0) return 1 ;	//y las guardo en sus correspondientes lugares
		if (scanf("%u", &g->vertices[i][1]) < 0) return 1;
	}
	u32 j = 0;												//Declro un variable para iterar en filas
	for(u32 i = g->m; i<(2*g->m); i++){				    	//For para recorrer desde g->m hasta 2*(g->m)
		g->vertices[i][0] = g->vertices[j][1];				//y completar con sus lugares pero invertidos
		g->vertices[i][1] = g->vertices[j][0];
		j++;
	}
	qsort(g->vertices, 2*(g->m), 8, cmp);					//Ordeno los vertices de menor a mayor

	u32 arrayver [g->n];
	j = 0;

	for(u32 i = 0; i < 2*(g->m); i++){
		if (i+1 < 2*(g->m) && j + 1  <= g->n && g->vertices[i][0] != g->vertices[i+1][0]){
			arrayver[j] = g->vertices[i][0];
			arrayver[j+1] = g->vertices[i+1][0];
			j++;
		}
	}
	
	for(u32 i = 0; i<g->n; i++){
		printf("%u ",arrayver[i]);
	}
	printf("\n");

	for(u32 i = 0; i< 2*g->m; i++){
		for(int j = 0;j<2;j++){
			printf("%u ", g->vertices[i][j]);
		}
		printf("\n");
	}

	for(u32 i = 0;i<(2*g->m);i++){							//Recorro el arreglo de punteros principales
		free(g->vertices[i]);								//y los libero
	}												
	free(g->vertices);										//Libero el puntero al arreglo de punteros 
	free(g);												//Libero la estructura de GrafoSt
}

#endif