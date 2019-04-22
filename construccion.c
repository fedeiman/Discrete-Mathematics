#ifndef _CONSTRUCCION
#define _CONSTRUCCION

#include "grafo.c"
#include "vecinos.c"
#include "orden.c"

//Funcion para ordenar los vertices
//usada en qsort.
int cmp(const void *pa, const void *pb) {
  const u32 *a = *(const u32 **)pa;
  const u32 *b = *(const u32 **)pb;
  if(a[0] == b[0]) {
    if(a[1] <= b[1]) return -1;
    else return 1;
  }
  else {
    if(a[0] <= b[0]) return -1;
    return 1;
  }
}

//Funcion de busqueda binaria en el arreglo de
//struct Vecinos.
u32 busqueda_binaria(Vecino *v, u32 dato, u32 array_lenght){
  u32 inf = 0; 
  u32 sup = array_lenght - 1;
  u32 mitad;
  while(inf<=sup){
    mitad = (inf + sup)/2;
    if(v[mitad]->nombre_del_vertice == dato){
      return mitad;
    }
    if(v[mitad]->nombre_del_vertice > dato){
      sup = mitad - 1;
    }
    if(v[mitad]->nombre_del_vertice < dato){
      inf = mitad + 1;
    }
  }
  //Esta linea se ejecutara solo en caso de que el "dato"
  //a buscar no este en v[n]->nombre_del_vetice.
  //Cosa que no puede pasar.
  printf("ERROR");
  return(-1);
}
//Funcion para obtener la primera una linea mediante stdin.
char* linea(char* line){
	if(line) free(line);
	//Aloco espacio para la linea.
  line = (char*)calloc(1,sizeof(char));
	if(!line){ 
		printf("Error al reservar memoria linea 51");
		return NULL; 											
	}
	int i = 0; 
  int tam = 1;
  char c;			
	//Mientras no sea el final del archivo ni se encuentre con \n, \r voy guardando cada caracter de la linea.																								
  while(((c = fgetc(stdin)) != EOF) && (c != '\n') && (c != '\r')) {
  	line[i] = c;
    i++;																										
      if(i == tam) {
				//Realoco espacio para la linea.
        line = (char*)realloc(line, (tam = tam*2)*sizeof(char));	
      }
  }
//Agrego el caracter nulo de ASCII para saber donde termina una linea.
//Devuelvo el tamaño real de la linea.
	line[i] = '\0';																						
	i++;																											
	return (char*)realloc(line, i * sizeof(char));						
}

Grafo ConstruccionDelGrafo(){
	//Declaro variable de tipo Grafo.
	//Luego me fijo que calloc haya podido reservar el espacio, en caso de no poder libero todo lo que este alocado
	//hasta este momento, esto lo hago en todos los callocs.
	Grafo g = (Grafo)calloc(1,sizeof(struct GrafoSt));
	if(!g){
		printf("Error al reservar memoria linea 79");
		return NULL;
	} 				
	char *line = NULL;
	u32 con_linea = 0;

	while(1){
		line = linea(line);
		//Mientras el primer caracter de la linea sea 'c'.
		if (line[0] == 'c'){
			//Aumento el contador de lineas del archivo que estoy leyendo.
			con_linea++;
		}																												
		else{
			break;
		}
	}

	//memcmp compara 2 strings, si son iguales retorna 0.
	//Yo considero que p edge puede esta luego de una linea
	//comentario o no puede estar(es decir nu puede haber
	//espacios luego de una linea comentario ni entre ellas).
	if(memcmp(line,"p edge ",7)){															
		printf("Formanto erroneo, falta p edge\n");							
		if(g) free(g);																								
		if(line) free(line);																							
		return NULL;
	}
	
	con_linea++;
	//i = 7 ya que hay esta el primer numero. 																							
	u32 indice = 7;																								
	g->n = 0;
	g->m = 0;
	
	//Todos los numeros digitos que va a ir leyendo estan entre
	// '0' y '9.'
	//Transforma mi numero en formato char a int.
	if((line[indice] >= '0') && (line[indice] <= '9')){								
		while ((line[indice] >= '0') && (line[indice] <= '9')){					
    		g->n = (g->n * 10) + ((line[indice]) - '0');							
				indice++;
  	}
	}
	else{
		//Considero que luego de p edge no puede haber mas de un espacio.
		printf("Formato erroneo,más de un espacio luego de p edge\n"); 
		if(g) free(g);																							
		if(line) free(line);
		return NULL;
	}
	
	//Busco espacios entre n y m o un final de linea que agregue.
	while(line[indice] == ' ' || line[indice] == '\0') {								
    if(line[indice] == '\0') {																		 
      printf("Error en la linea %u al leer las aristas\n",con_linea);
			if(g) free(g);
			if(line) free(line);
			return NULL;
      } 
		else{
			indice++;
		} 
  }
	
	while ((line[indice] >= '0') && (line[indice] <= '9')){
    g->m = (g->m * 10) + ((line[indice]) - '0');
		indice++;
  }

	//vertices = array de 2*(g->m) punteros de u32.
	u32 **vertices = (u32**)calloc((2*(g->m)),sizeof(u32*));   	
	if (!vertices){ 
		if(g) free(g);
		printf("Error al reservar memoria linea 152");
		return NULL;
	} 
	//Para cada puntero
	//le asigno un array de 2 de u32.
	for(u32 i = 0; i < 2*(g->m); i++) {												 
		vertices[i] = (u32*)calloc(2,sizeof(u32));
		if(!vertices[i]){
			if (vertices) free(vertices);
			if(g) free(g);
			printf("Error al reservar memoria linea 161");
			return NULL;
		}					
	}

	u32 n = 0;
	
	//Un for que va a leer todas las aristas de forma 
	//analoga a lo que se hizo para p edge.
	for(u32 i = 0; i < g->m; i++){														
		line = linea(line);																			
		con_linea++;
		

		//En caso de que falten aristas en el archivo
		//saltaria este error avisando que falta una arista en la linea i+1.
		if(memcmp(line,"e ",2)){																										
			if(line) free(line);																						
			printf("Error en la arista %i en la linea %u\n",i+1,con_linea);
			for(u32 h = 0; h < (2*g->m); h++){					
				if(vertices[h]) free(vertices[h]);								
			}
			if(vertices) free(vertices);
			if(g) free(g);
			return NULL;
		}
		
		u32 j = 2;
		
		if((line[j] >= '0') && (line[j] <= '9')){
			while ((line[j] >= '0') && (line[j] <= '9')){
    		vertices[n][0] = (vertices[n][0] * 10) + ((line[j]) - '0');
				j++;
  		}
		}
		else{
			//Considero que luego de e no puede haber mas de un espacio.
			printf("Formato erroneo,más de un espacio luego de e en la arista %i en la linea %u\n", i+1,con_linea);
			for(u32 h = 0; h < (2*g->m); h++){												
				if(vertices[h]) free(vertices[h]);								
			}
			if(vertices) free(vertices);
			if(g) free(g);
			if(line) free(line);
			return NULL;
		}
		
		while(line[j] == ' ' || line[j] == '\0') {
    	if(line[j] == '\0') {
      	printf("Error en la arista %i al leeer la linea %u\n",i+1,con_linea);
				for(u32 h = 0; h < (2*g->m); h++){					
					if(vertices[h]) free(vertices[h]);								
				}
				if(vertices) free(vertices);
				if(g) free(g);
				if(line) free(line);					
				return NULL;
      } 
			else{
				j++;
			} 
    }	
		
		while ((line[j] >= '0') && (line[j] <= '9')){
    	vertices[n][1] = (vertices[n][1] * 10) + ((line[j]) - '0');
			j++;
  	}
		n++;
	}
	
	if(line) free(line);
	//Declro un variable para iterar en filas
	u32 j = 0;																								
		
	//For para recorrer desde g->m hasta 2*(g->m)
	//y completar con sus lugares pero invertidos.
	for(u32 i = g->m; i < (2*g->m); i++){				    					
		vertices[i][0] = vertices[j][1];									
		vertices[i][1] = vertices[j][0];
		j++;
	}
	//Ordeno los vertices de menor a mayor.
	qsort(vertices, 2 * (g->m), sizeof(vertices[0]), cmp);
	//Me fijo si la cantidad de veritces declarada es la correcta.
	u32 rep = 0;                                              
  	for(u32 i = 0; i < 2*(g->m) - 1; i++){
    	if(vertices[i][0] == vertices[i+1][0]){
      	rep++;
    }
  }
	if(g->n != (2*g->m) - rep){
		for(u32 i = 0; i < (2*g->m); i++){					
			if(vertices[i]) free(vertices[i]);								
		}
		if(vertices) free(vertices);
		if(g) free(g);
		printf("Cantidad de vertices no es la declarada\n");
		return NULL;
	}

	//Declaro una variable de tipo array puntero a Vecino.
	g->v = (Vecino*)calloc((g->n),sizeof(struct Vecinos));
	if(!g->v){
		for(u32 i = 0; i < (2*g->m); i++){												
			if (vertices[i]) free(vertices[i]);								
		}		
		if (vertices) free(vertices);
		if(g) free(g);
		printf("Error al reservar memoria linea 266");
		return NULL;
	}				
	
	//Inicializo mi variable v.
	for(u32 i = 0; i < g->n; i++){														
		g->v[i] = (Vecino)calloc(1,sizeof(struct Vecinos));
		if(!g->v[i]){
			for(u32 h = 0; h < (2*g->m); h++){												
				if (vertices[h]) free(vertices[h]);								
			}		
			if (vertices) free(vertices);
			if(g->v) free(g->v);
			if(g) free(g);
			printf("Error al reservar memoria linea 279");
			return NULL;
		}	
	}

	//Este algoritmo pasa de mi matriz de 2*(2*(g->m)) a un struct
	//sin repeticiones de vertices y con los indices de comienzo
	//y final de los vecinos de cada vertice (indice en mi 
	//matriz de 2*(2*(g->m)) y un arreglo dinamico con los indices
	//de la posicion de los vecinos en la estructura.
	j = 0;
	u32 *aux = (u32*)calloc((g->n),sizeof(u32));
	if(!aux){
		for(u32 i = 0; i < (2*g->m); i++){												
			if (vertices[i]) free(vertices[i]);								
		}		
		if (vertices) free(vertices);
		for(u32 i = 0; i < g->n; i++){																	
			if(g->v[i]) free(g->v[i]); 
		}
		if(g->v) free(g->v);
		if(g) free(g);
		printf("Error al reservar memoria linea 298");
		return NULL;
	}
	
	for(u32 i = 0; i < 2*(g->m); i++){
		if (i+1 < 2*(g->m) && vertices[i][0] != vertices[i+1][0]){ 
			g->v[j]->nombre_del_vertice = vertices[i][0];
			g->v[j+1]->nombre_del_vertice = vertices[i+1][0];
			aux[j] = i;																					
			aux[j+1] = i+1;																				
			j++;                                            		
		}																												
		else {																									
			aux[j] = i;
		}
	}

	//Seteo los indice de inicio y finales de los vecinos.
	for(u32 i = 0; i < g->n; i++){												
		if(i == 0){
			g->v[i]->ind_de_inicio_vecinos = 0;
			g->v[i]->ind_de_final_vecinos = aux[i];
		}
		else{
			g->v[i]->ind_de_inicio_vecinos = aux[i-1] + 1;
			g->v[i]->ind_de_final_vecinos = aux[i];
		}
	}
	for(u32 i = 0; i < g->n; i++){
		g->v[i]->total_vecinos = g->v[i]->ind_de_final_vecinos - g->v[i]->ind_de_inicio_vecinos + 1;
	}
	//Libero el Puntero al arreglo aux.
	if(aux) free(aux);


	//Inicializo el arreglo con el orden.
	//Declaro una variable de tipo array puntero a Orden.
	g->o = (Orden*)calloc((g->n),sizeof(struct Ordenes));
		if(!g->o){
			for(u32 i = 0; i < (2*g->m); i++){												
				if (vertices[i]) free(vertices[i]);								
		}		
		if (vertices) free(vertices);
		for(u32 i = 0; i < g->n; i++){														
			if(g->v[i]->array_vecinos) free(g->v[i]->array_vecinos);			
			if(g->v[i]) free(g->v[i]); 
		}
		if(g->v) free(g->v);
		if(g) free(g);
		printf("Error al reservar memoria linea 346");
		return NULL;
		}

		for(u32 i = 0; i < g->n; i++){														
		g->o[i] = (Orden)calloc(1,sizeof(struct Ordenes));
		if(!g->o[i]){
			for(u32 h = 0; h < (2*g->m); h++){												
			if (vertices[h]) free(vertices[h]);								
		}		
		if (vertices) free(vertices);
		for(u32 h = 0; h < g->n; h++){														
			if(g->v[h]->array_vecinos) free(g->v[h]->array_vecinos);			
			if(g->v[h]) free(g->v[h]); 
		}
		if(g->v) free(g->v);
		if(g->o) free(g->o);
		if(g) free(g);
		printf("Error al reservar memoria linea 363");
		return NULL;
		}	
	}

	for(u32 i = 0; i < g->n; i++){
		g->o[i]->nombre = g->v[i]->nombre_del_vertice;									
	}

	//Inicializo el array dinamico de indice de vecinos.
	for(u32 i = 0; i < g->n; i++){														
		//cantidad de vecinos del vertice i.
		u32 c = g->v[i]->ind_de_final_vecinos - g->v[i]->ind_de_inicio_vecinos + 1;	
		g->v[i]->array_vecinos = (u32*)calloc(c,sizeof(u32));
		if(!g->v[i]->array_vecinos){
			for(u32 h = 0; h < (2*g->m); h++){												
			if (vertices[h]) free(vertices[h]);								
		}		
		if (vertices) free(vertices);
		for(u32 h = 0; h < g->n; h++){														
			if(g->v[h]->array_vecinos) free(g->v[h]->array_vecinos);			
			if(g->v[h]) free(g->v[h]);
			if(g->o[h]) free(g->o[h]); 
		}
		if(g->o) free(g->o);
		if(g->v) free(g->v);
		if(g) free(g);
		printf("Error al reservar memoria linea 389");
		return NULL;
		}
	}
	//Inicializo el array dinamico de indice de vecinos.
	for(u32 i = 0; i < g->n; i++){														
		//cantidad de vecinos del vertice i.
		u32 c = g->v[i]->ind_de_final_vecinos - g->v[i]->ind_de_inicio_vecinos + 1;	
		g->o[i]->array_vecinos = (u32*)calloc(c,sizeof(u32));
		if(!g->o[i]->array_vecinos){
			for(u32 h = 0; h < (2*g->m); h++){												
			if (vertices[h]) free(vertices[h]);								
		}		
		if (vertices) free(vertices);
		for(u32 h = 0; h < g->n; h++){														
			if(g->v[h]->array_vecinos) free(g->v[h]->array_vecinos);			
			if(g->v[h]) free(g->v[h]);
			if(g->o[h]) free(g->o[h]); 
		}
		if(g->o) free(g->o);
		if(g->v) free(g->v);
		if(g) free(g);
		printf("Error al reservar memoria linea 411");
		return NULL;
		}
	}
	
	//For para llenar con busqueda_binaria mi arreglo v[n]->array_vecinos[n].
	for(u32  i = 0; i < g->n; i++){														
		u32 contador = 0;																				
		u32 cantidad = g->v[i]->ind_de_final_vecinos - g->v[i]->ind_de_inicio_vecinos + 1;
		g->o[i]->cant_vecinos = cantidad;
		while(cantidad > contador){
			g->v[i]->array_vecinos[contador] = busqueda_binaria(g->v,vertices[g->v[i]->ind_de_inicio_vecinos + contador][1],g->n);
			g->o[i]->array_vecinos[contador] = busqueda_binaria(g->v,vertices[g->v[i]->ind_de_inicio_vecinos + contador][1],g->n);
			contador ++;
		}
	}												 

	//Recorro el arreglo de punteros principales y los libero.
	for(u32 i = 0; i < (2*g->m); i++){												
		if (vertices[i]) free(vertices[i]);								
	}		

	//Libero el puntero al arreglo de punteros.
	if (vertices) free(vertices);
	
	Greedy(g);	
	
	return g;
}

Grafo CopiarGrafo(Grafo G){
	Grafo copia = (Grafo)calloc(1,sizeof(struct GrafoSt));
	if(!copia){
		printf("Error al reservar memoria linea 456");
		return NULL;
	}
	copia->n = G->n;
	copia->m = G->m;
	copia->colores = G->colores;

	//Declaro una variable de tipo array puntero a Vecino.
	copia->v = (Vecino*)calloc((copia->n),sizeof(struct Vecinos));
	if(!copia->v){		
		if(copia) free(copia);
		printf("Error al reservar memoria linea 465");
		return NULL;
	}
	//Inicializo mi variable v.
	for(u32 i = 0; i < copia->n; i++){														
		copia->v[i] = (Vecino)calloc(1,sizeof(struct Vecinos));
		if(!copia->v[i]){
			if(copia->v) free(copia->v);
			if(copia) free(copia);
			printf("Error al reservar memoria linea 473");
			return NULL;
		}	
	}
	for(u32 i = 0; i < copia->n; i++){
		copia->v[i]->nombre_del_vertice = G->v[i]->nombre_del_vertice;
		copia->v[i]->ind_de_inicio_vecinos = G->v[i]->ind_de_inicio_vecinos;
		copia->v[i]->ind_de_final_vecinos = G->v[i]->ind_de_final_vecinos;
		copia->v[i]->total_vecinos = G->v[i]->total_vecinos;
		copia->v[i]->color = G->v[i]->color;
		copia->v[i]->cant_color = G->v[i]->cant_color;
	}
	//Inicializo el array dinamico de indice de vecinos.
	for(u32 i = 0; i < copia->n; i++){														
		//cantidad de vecinos del vertice i.
		u32 c = copia->v[i]->ind_de_final_vecinos - copia->v[i]->ind_de_inicio_vecinos + 1;	
		copia->v[i]->array_vecinos = (u32*)calloc(c,sizeof(u32));
		if(!copia->v[i]->array_vecinos){		
		for(u32 h = 0; h < copia->n; h++){														
			if(copia->v[h]->array_vecinos) free(copia->v[h]->array_vecinos);			
			if(copia->v[h]) free(copia->v[h]); 
		}
		if(copia->v) free(copia->v);
		if(copia) free(copia);
		printf("Error al reservar memoria linea 493");
		return NULL;
		}
	}

	//For para llenar cmi arreglo v[n]->array_vecinos[n].
	for(u32  i = 0; i < copia->n; i++){														
		u32 contador = 0;																				
		u32 cantidad = copia->v[i]->ind_de_final_vecinos - copia->v[i]->ind_de_inicio_vecinos + 1;
		while(cantidad > contador){
			copia->v[i]->array_vecinos[contador] = G->v[i]->array_vecinos[contador];
			contador ++;
		}
	}
	//Inicializo el arreglo con el orden.
	//Declaro una variable de tipo array puntero a Orden.
	copia->o = (Orden*)calloc((copia->n),sizeof(struct Ordenes));
		if(!copia->o){
		for(u32 i = 0; i < copia->n; i++){														
			if(copia->v[i]->array_vecinos) free(copia->v[i]->array_vecinos);			
			if(copia->v[i]) free(copia->v[i]); 
		}
		if(copia->v) free(copia->v);
		if(copia) free(copia);
		printf("Error al reservar memoria linea 517");
		return NULL;
		}
		//aloco espacio para o[n] y luego lo copio.
		for(u32 i = 0; i < copia->n; i++){														
		copia->o[i] = (Orden)calloc(1,sizeof(struct Ordenes));
		if(!copia->o[i]){		
		for(u32 h = 0; h < copia->n; h++){														
			if(copia->v[h]->array_vecinos) free(copia->v[h]->array_vecinos);			
			if(copia->v[h]) free(copia->v[h]); 
		}
		if(copia->v) free(copia->v);
		if(copia->o) free(copia->o);
		if(copia) free(copia);
		printf("Error al reservar memoria linea 530");
		return NULL;
		}	
	}
		for(u32 i = 0; i < copia->n; i++){														
		//cantidad de vecinos del vertice i.
		u32 c = copia->v[i]->ind_de_final_vecinos - copia->v[i]->ind_de_inicio_vecinos + 1;	
		copia->o[i]->array_vecinos = (u32*)calloc(c,sizeof(u32));
		if(!copia->o[i]->array_vecinos){		
		for(u32 h = 0; h < copia->n; h++){														
			if(copia->v[h]->array_vecinos) free(copia->v[h]->array_vecinos);		
			if(copia->v[h]) free(copia->v[h]); 
		}
		if(copia->v) free(copia->v);
		if(copia) free(copia);
		printf("Error al reservar memoria linea 546");
		return NULL;
		}
	}
		for(u32  i = 0; i < copia->n; i++){														
		u32 contador = 0;																				
		u32 cantidad = copia->v[i]->ind_de_final_vecinos - copia->v[i]->ind_de_inicio_vecinos + 1;
		while(cantidad > contador){
			copia->o[i]->array_vecinos[contador] = G->o[i]->array_vecinos[contador];
			contador ++;
		}
		copia->o[i]->cant_vecinos = G->o[i]->cant_vecinos;
	}

	for(u32 i = 0; i < copia->n; i++){
		copia->o[i]->nombre = G->o[i]->nombre;
		copia->o[i]->color_actual = G->o[i]->color_actual;							
	}
		return copia;
}

void DestruccionDelGrafo(Grafo G){
	
	//Free para liberar mi array_vecinos y la posicion v[i]
	//del arreglo de struct Vecinos.
	for(u32 i = 0; i < G->n; i++){														
		if(G->v[i]->array_vecinos) free(G->v[i]->array_vecinos);			
		if(G->v[i]) free(G->v[i]); 
	}	
	for(u32 i = 0; i < G->n; i++){														
		if(G->o[i]->array_vecinos) free(G->o[i]->array_vecinos);			
		if(G->o[i]) free(G->o[i]); 
	}			 			 	
	
	//Libero el puntero al arreglo.
	if (G->o) free(G->o);

	//Libero el Puntero al arreglo de Vecinos.
	if(G->v) free(G->v);																						
	
	//Libero la estructura de GrafoSt.
	if(G) free(G);																						
	
}
#endif