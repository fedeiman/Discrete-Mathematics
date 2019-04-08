#ifndef _CONSTRUCCION
#define _CONSTRUCCION

#include "grafo.c"
#include "vecinos.c"

int cmp(const void* a, const void* b) {						//Funcion para ordenar los vertices
    u32 *ap = *(u32**)a, *bp = *(u32**)b;					//usada en qsort.
    u32 fsta = *ap, fstb = *bp;
    u32 snda = *(++ap), sndb = *(++bp);
    if(fsta == fstb) return snda - sndb;
    else return fsta - fstb;
}

u32 busqueda_binaria(Vecino *v, u32 dato, u32 array_lenght){
	u32 inf = 0;											//Funcion de busqueda binaria en el arreglo de 
	u32 sup = array_lenght;									//struct Vecinos.
	u32 mitad;
	while(inf<=sup){
		mitad = (inf + sup)/2;
		if(v[mitad]->nombre_del_vertice == dato){
			return mitad;
		}
		if(v[mitad]->nombre_del_vertice > dato){
			sup = mitad;
			mitad = (inf + sup)/2;
		}
		if(v[mitad]->nombre_del_vertice < dato){
			inf = mitad;
			mitad = (inf + sup)/2;
		}
	}
	printf("ERROR");										//Esta linea se ejecutara solo en caso de que el "dato"
	return(mitad);											//a buscar no este en v[n]->nombre_del_vetice.
}															//Cosa que no puede pasar.

int main(){
	Grafo g = (Grafo)malloc(sizeof(struct GrafoSt)); 		//Declaro variable de tipo Grafo.
	
	printf("numero de vertices:"); 			  				//Pido y
	
	if(scanf("%u",&g->n) < 0) return 1;			  			//guardo n° de vertices.
	
	printf("numero de aristas:"); 			  				//Pido y 
	
	if(scanf("%u",&g->m) < 0) return 1;           			//guardo n° de aristas.
	
	g->vertices = (u32**)malloc((2*(g->m))*sizeof(u32*));   //g->vertices = array de 2*(g->m) punteros de u32.
	
	for(u32 i = 0; i < 2*(g->m); i++){						//Para cada puntero 
        g->vertices[i] = (u32*)malloc(2*sizeof(u32));		//le asigno un array de 2 de u32.
	}

	for(u32 i = 0; i < g->m; i++){ 							//Para cada fila de la matriz 
		printf("conexiones:");								//completo las aristas
		if (scanf("%u", &g->vertices[i][0]) < 0) return 1 ;	//y las guardo en sus correspondientes lugares.
		if (scanf("%u", &g->vertices[i][1]) < 0) return 1;
	}
	u32 j = 0;
															//Declro un variable para iterar en filas
	for(u32 i = g->m; i < (2*g->m); i++){				    //For para recorrer desde g->m hasta 2*(g->m)
		g->vertices[i][0] = g->vertices[j][1];				//y completar con sus lugares pero invertidos.
		g->vertices[i][1] = g->vertices[j][0];
		j++;
	}

	qsort(g->vertices, 2*(g->m), 8, cmp);					//Ordeno los vertices de menor a mayor.
	
	Vecino *v = (Vecino*)malloc((g->n)*sizeof(Vecino));		//Declaro una variable de tipo array puntero a Vecino.

	for(u32 i = 0; i < g->n; i++){							//Inicializo mi variable v.
		v[i] = (Vecino)malloc(sizeof(struct Vecinos));
	}

	j = 0;
	u32 *aux = (u32*)malloc((g->n)*sizeof(u32));

	for(u32 i = 0; i < 2*(g->m); i++){
		if (i+1 < 2*(g->m) && g->vertices[i][0] != g->vertices[i+1][0]){ 
			v[j]->nombre_del_vertice = g->vertices[i][0];
			v[j+1]->nombre_del_vertice = g->vertices[i+1][0];
			aux[j] = i;										//Este algoritmo pasa de mi matriz de 2*(2*(g->m)) a un struct
			aux[j+1] = i+1;									//sin repeticiones de vertices y con los indices de comienzo
			j++;                                            //y final de los vecinos de cada vertice (indice en mi 
		}													//matriz de 2*(2*(g->m)) y un arreglo dinamico con los indices
		else {												//de la posicion de los vecinos en la estructura.
			aux[j] = i;
		}
	}

	for(u32 i = 0; i < g->n; i++){							//Seteo los indice de inicio y finales de los vecinos.
		if(i == 0){
			v[i]->ind_de_inicio_vecinos = 0;
			v[i]->ind_de_final_vecinos = aux[i];
		}
		else{
			v[i]->ind_de_inicio_vecinos = aux[i-1] + 1;
			v[i]->ind_de_final_vecinos = aux[i];
		}
	}
	g->orden = (u32*)malloc(((g->n))*sizeof(u32));			//Inicializo el arreglo con el orden.
	
	for(u32 i = 0; i < g->n; i++){
		g->orden[i] = v[i]->nombre_del_vertice;				//Le doy un orden acutal (de menor a mayor).
	}

	for(u32  i = 0; i < g->n; i++){							//Inicializo el array dinamico de indice de vecinos.
		u32 c = v[i]->ind_de_final_vecinos - v[i]->ind_de_inicio_vecinos + 1;	//cantidad de vecinos del vertice i.
		v[i]->array_vecinos = (u32*)malloc(c*sizeof(u32));
	}

	for(u32  i = 0; i < g->n; i++){							//For para llenar con busqueda_binaria mi arreglo
		u32 contador = 0;									//v[n]->array_vecinos[n].
		u32 cantidad = v[i]->ind_de_final_vecinos - v[i]->ind_de_inicio_vecinos + 1;
		while(cantidad > contador){
			v[i]->array_vecinos[contador] = busqueda_binaria(v,g->vertices[v[i]->ind_de_inicio_vecinos + contador][1],g->n);
			contador ++;
		}
	}

	//----------------PRINTF DE PRUEBA----------------//

	/*for(u32 i = 0; i < g->n; i++){
		u32 contador = 0;
		u32 cantidad = v[i]->ind_de_final_vecinos - v[i]->ind_de_inicio_vecinos + 1;
		while(cantidad > contador){
		printf("El valor de indice de los vecinos de %u es %u\n",v[i]->nombre_del_vertice,v[i]->array_vecinos[contador]);
		contador++;
		}
	}
	for(u32 i = 0; i < g->n; i++){
		printf("El valor de incio de los vecinos de %u es %u\n" ,v[i]->nombre_del_vertice,v[i]->ind_de_inicio_vecinos);
		printf("El valor de final de los vecinos de %u es %u\n" ,v[i]->nombre_del_vertice,v[i]->ind_de_final_vecinos);
	}

	for(u32 i = 0; i < g->n; i++){
	printf("%u ",aux[i]);
	}

	printf("\n");

	for(u32 i = 0; i < g->n; i++){
		printf("%u ",v[i]->nombre_del_vertice);
	}

	printf("\n");
	printf("\n");
	
	for(u32 i = 0; i < 2*g->m; i++){
		for(int j = 0; j < 2; j++){
			printf("%u ", g->vertices[i][j]);
		}
		printf("\n");
	}
	*/
	//---------------------FREES---------------------//

	for(u32 i = 0; i < g->n; i++){							//Free para liberar mi array_vecinos y la posicion v[i]
		free(v[i]->array_vecinos);							//del arreglo de struct Vecinos.
		free(v[i]); 
	}
	for(u32 i = 0; i < (2*g->m); i++){						//Recorro el arreglo de punteros principales
		free(g->vertices[i]);								//y los libero.
	}		
	free(g->orden);											//Libero el arrelog con el orden.
	free(g->vertices);										//Libero el puntero al arreglo de punteros. 
	free(g);												//Libero la estructura de GrafoSt.
	free(v);												//Libero el Puntero al arreglo de Vecinos.
	free(aux);												//Libero el Puntero al arreglo aux.
}

#endif