#ifndef _CONSTRUCCION
#define _CONSTRUCCION

#include "grafo.c"
#include "vecinos.c"
#include "stdio.h"

//Funcion para ordenar los vertices
//usada en qsort.
int cmp(const void* a, const void* b) {
  u32 *ap = *(u32**)a, *bp = *(u32**)b;
  u32 fsta = *ap, fstb = *bp;
  u32 snda = *(++ap), sndb = *(++bp);
  if(fsta == fstb) return snda - sndb;
    else return fsta - fstb;
}

//Funcion de busqueda binaria en el arreglo de
//struct Vecinos.
u32 busqueda_binaria(Vecino *v, u32 dato, u32 array_lenght){
	u32 inf = 0; 
	u32 sup = array_lenght;
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
		printf("Error al reservar memoria linea 48");
		return 0; 											
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

int main (){
	//Declaro variable de tipo Grafo.
	//Luego me fijo que calloc haya podido reservar el espacio, en caso de no poder libero todo lo que este alocado
	//hasta este momento, esto lo hago en todos los callocs.
	Grafo g = (Grafo)calloc(1,sizeof(struct GrafoSt));
	if(!g){
		printf("Error al reservar memoria linea 76");
		return 0;
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
		return -1;
	}
	
	con_linea++;
	//i = 7 ya que hay esta el primer numero. 																							
	u32 i = 7;																								
	g->n = 0;
	g->m = 0;
	
	//Todos los numeros digitos que va a ir leyendo estan entre
	// '0' y '9.'
	//Transforma mi numero en formato char a int.
	if((line[i] >= '0') && (line[i] <= '9')){								
		while ((line[i] >= '0') && (line[i] <= '9')){					
    		g->n = (g->n * 10) + ((line[i]) - '0');							
				i++;
  	}
	}
	else{
		//Considero que luego de p edge no puede haber mas de un espacio.
		printf("Formato erroneo,más de un espacio luego de p edge\n"); 
		if(g) free(g);																							
		if(line) free(line);
		return -1;
	}
	
	//Busco espacios entre n y m o un final de linea que agregue.
	while(line[i] == ' ' || line[i] == '\0') {								
    if(line[i] == '\0') {																		 
      printf("Error en la linea %u al leer las aristas\n",con_linea);
			if(g) free(g);
			if(line) free(line);
			return -1;
      } 
		else{
			i++;
		} 
  }
	
	while ((line[i] >= '0') && (line[i] <= '9')){
    g->m = (g->m * 10) + ((line[i]) - '0');
		i++;
  }

	//g->vertices = array de 2*(g->m) punteros de u32.
	g->vertices = (u32**)calloc((2*(g->m)),sizeof(u32*));   	
	if (!g->vertices){ 
		if(g) free(g);
		printf("Error al reservar memoria linea 149");
		return 0;
	} 
	//Para cada puntero
	//le asigno un array de 2 de u32.
	for(u32 i = 0; i < 2*(g->m); i++) {												 
		g->vertices[i] = (u32*)calloc(2,sizeof(u32));
		if(!g->vertices[i]){
			if (g->vertices) free(g->vertices);
			if(g) free(g);
			printf("Error al reservar memoria linea 158");
			return 0;
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
			for(u32 i = 0; i < (2*g->m); i++){					
				if(g->vertices[i]) free(g->vertices[i]);								
			}
			if(g->vertices) free(g->vertices);
			if(g) free(g);
			return -1;
		}
		
		u32 j = 2;
		
		if((line[j] >= '0') && (line[j] <= '9')){
			while ((line[j] >= '0') && (line[j] <= '9')){
    		g->vertices[n][0] = (g->vertices[n][0] * 10) + ((line[j]) - '0');
				j++;
  		}
		}
		else{
			//Considero que luego de e no puede haber mas de un espacio.
			printf("Formato erroneo,más de un espacio luego de e en la arista %i en la linea %u\n", i+1,con_linea);
			for(u32 i = 0; i < (2*g->m); i++){												
				if(g->vertices[i]) free(g->vertices[i]);								
			}
			if(g->vertices) free(g->vertices);
			if(g) free(g);
			if(line) free(line);
			return -1;
		}
		
		while(line[j] == ' ' || line[j] == '\0') {
    	if(line[j] == '\0') {
      	printf("Error en la arista %i al leeer la linea %u\n",i+1,con_linea);
				for(u32 i = 0; i < (2*g->m); i++){					
					if(g->vertices[i]) free(g->vertices[i]);								
				}
				if(g->vertices) free(g->vertices);
				if(g) free(g);
				if(line) free(line);					
				return -1;
      } 
			else{
				j++;
			} 
    }	
		
		while ((line[j] >= '0') && (line[j] <= '9')){
    	g->vertices[n][1] = (g->vertices[n][1] * 10) + ((line[j]) - '0');
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
		g->vertices[i][0] = g->vertices[j][1];									
		g->vertices[i][1] = g->vertices[j][0];
		j++;
	}
	//Ordeno los vertices de menor a mayor.
	qsort(g->vertices, 2*(g->m), 8, cmp);											
	
	//Me fijo si la cantidad de veritces declarada es la correcta.
	u32 rep = 0;																							
	for(u32 i = 0; i < 2*(g->m); i++){
		if(i+1 < 2*g->m && g->vertices[i][0] == g->vertices[i+1][0]){
			rep++;
		}
	}
	if(g->n != (2*g->m) - rep){
		for(u32 i = 0; i < (2*g->m); i++){					
			if(g->vertices[i]) free(g->vertices[i]);								
		}
		if(g->vertices) free(g->vertices);
		if(g) free(g);
		printf("Cantidad de vertices no es la declarada\n");
		return -1;
	}

	//Declaro una variable de tipo array puntero a Vecino.
	Vecino *v = (Vecino*)calloc((g->n),sizeof(Vecino));
	if(!v){
		for(u32 i = 0; i < (2*g->m); i++){												
			if (g->vertices[i]) free(g->vertices[i]);								
		}		
		if (g->vertices) free(g->vertices);
		if(g) free(g);
		printf("Error al reservar memoria linea 265");
		return 0;
	}				
	
	//Inicializo mi variable v.
	for(u32 i = 0; i < g->n; i++){														
		v[i] = (Vecino)calloc(1,sizeof(struct Vecinos));
		if(!v[i]){
			for(u32 i = 0; i < (2*g->m); i++){												
				if (g->vertices[i]) free(g->vertices[i]);								
			}		
			if (g->vertices) free(g->vertices);
			if(v) free(v);
			if(g) free(g);
			printf("Error al reservar memoria linea 278");
			return 0;
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
			if (g->vertices[i]) free(g->vertices[i]);								
		}		
		if (g->vertices) free(g->vertices);
		for(u32 i = 0; i < g->n; i++){																	
			if(v[i]) free(v[i]); 
		}
		if(v) free(v);
		if(g) free(g);
		printf("Error al reservar memoria linea 297");
		return 0;
	}
	
	for(u32 i = 0; i < 2*(g->m); i++){
		if (i+1 < 2*(g->m) && g->vertices[i][0] != g->vertices[i+1][0]){ 
			v[j]->nombre_del_vertice = g->vertices[i][0];
			v[j+1]->nombre_del_vertice = g->vertices[i+1][0];
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
			v[i]->ind_de_inicio_vecinos = 0;
			v[i]->ind_de_final_vecinos = aux[i];
		}
		else{
			v[i]->ind_de_inicio_vecinos = aux[i-1] + 1;
			v[i]->ind_de_final_vecinos = aux[i];
		}
	}
	//Libero el Puntero al arreglo aux.
	if(aux) free(aux);

	//Inicializo el arreglo con el orden.
	g->orden = (u32*)calloc(((g->n)),sizeof(u32));
	if(!g->orden){
		for(u32 i = 0; i < (2*g->m); i++){												
			if (g->vertices[i]) free(g->vertices[i]);								
		}		
		if (g->vertices) free(g->vertices);
		for(u32 i = 0; i < g->n; i++){																
			if(v[i]) free(v[i]); 
		}
		if(v) free(v);
		if(g) free(g);
		printf("Error al reservar memoria linea 340");
		return 0;
	}						
	
	for(u32 i = 0; i < g->n; i++){
		g->orden[i] = v[i]->nombre_del_vertice;									
	}

	//Inicializo el array dinamico de indice de vecinos.
	for(u32 i = 0; i < g->n; i++){														
		//cantidad de vecinos del vertice i.
		u32 c = v[i]->ind_de_final_vecinos - v[i]->ind_de_inicio_vecinos + 1;	
		v[i]->array_vecinos = (u32*)calloc(c,sizeof(u32));
		if(!v[i]->array_vecinos){
			for(u32 i = 0; i < (2*g->m); i++){												
			if (g->vertices[i]) free(g->vertices[i]);								
		}		
		if (g->vertices) free(g->vertices);
		for(u32 i = 0; i < g->n; i++){														
			if(v[i]->array_vecinos) free(v[i]->array_vecinos);			
			if(v[i]) free(v[i]); 
		}
		if(v) free(v);
		if(g) free(g);
		printf("Error al reservar memoria linea 363");
		return 0;
		}
	}
	
	//For para llenar con busqueda_binaria mi arreglo v[n]->array_vecinos[n].
	for(u32  i = 0; i < g->n; i++){														
		u32 contador = 0;																				
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
	//Recorro el arreglo de punteros principales y los libero.
	for(u32 i = 0; i < (2*g->m); i++){												
		if (g->vertices[i]) free(g->vertices[i]);								
	}		

	//Libero el puntero al arreglo de punteros.
	if (g->vertices) free(g->vertices);


	//---------------------FREES---------------------//

	for(u32 i = 0; i < g->n; i++){														//Free para liberar mi array_vecinos y la posicion v[i]
		if(v[i]->array_vecinos) free(v[i]->array_vecinos);			//del arreglo de struct Vecinos.
		if(v[i]) free(v[i]); 
	}
	
	if(g->orden) free(g->orden);															//Libero el arrelog con el orden.
	
	if(g) free(g);																						//Libero la estructura de GrafoSt.
	
	if(v) free(v);																						//Libero el Puntero al arreglo de Vecinos.
}

#endif