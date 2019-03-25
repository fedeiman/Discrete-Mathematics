#include  "grafo.c"

int main(){
	Grafo g = malloc(sizeof(struct GrafoSt)); 				//Declaro variable de tipo Grafo
	printf("numero de vertices:"); 			  				//Pido y 
	scanf("%u",&g->n);			  			  				//guardo n° de vertices
	printf("numero de aristas:"); 			  				//Pido y 
	scanf("%u",&g->m);           			  				//guardo n° de aristas
	g->vertices = malloc(2*sizeof(u32*));     				//g->vertices = array de 2 punteros de u32
	for(u32 i = 0; i < 2 ; i++){							//Para cada puntero 
        g->vertices[i] = malloc((2*g->m)*sizeof(u32));		//le asigno un array de 2*g->m de u32
	}														
	for(u32 i = 0;i< g->m;i++){ 							//Para cada columna de la matriz 
		printf("conexiones:");								//completo las aristas
		scanf("%u",&g->vertices[0][i]);						//y las guardo en sus correspondientes lugares
		scanf("%u",&g->vertices[1][i]);
	}
	int j = 0;												//Declro un variable para iterar en columnas
	for(u32 i = g->m;i<(2*g->m);i++){						//For para recorrer desde g->m hasta 2*(g->m)
		g->vertices[0][i] = g->vertices[1][j];				//y completar con sus lugares pero invertidos
		g->vertices[1][i] = g->vertices[0][j];
		j++;
	}
	/*for(int i = 0; i<2;i++){
		for(u32 j = 0;j<(2*g->m);j++){
			printf("%u",g->vertices[i][j]);
		}
		printf("\n");
	}*/
	for(int i = 0;i<2;i++){									//Recorro el arreglo de punteros principales
		free(g->vertices[i]);								//y los libero
	}												
	free(g->vertices);										//Libero el puntero al arreglo de punteros 
	free(g);												//Libero la estructura de GrafoSt
}