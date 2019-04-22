#ifndef _RII
#define _RII

/* 
Integrante:
Federico Matías Imán
Mail
 matiasiman@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef struct GrafoSt *Grafo; 
typedef struct Vecinos *Vecino;
typedef struct Ordenes *Orden;

//Funciones de Construccion/Destruccion/Copia del grafo // construccion.c

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);

Grafo CopiarGrafo(Grafo G);

//Funciones de coloreo //greedy.c

u32 Greedy(Grafo G);

int Bipartito(Grafo G); //mal

//Funciones para extraer información de datos del grafo// info.c

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeLados(Grafo G);

u32 NumeroDeColores(Grafo G);

//Funciones de los vertices// info.c

u32 NombreDelVertice(Grafo G, u32 i);

u32 ColorDelVertice(Grafo G, u32 i);

u32 GradoDelVertice(Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);

//Funciones de ordenacion // ordenamiento.c

char OrdenNatural(Grafo G);//mal

char OrdenWelshPowell(Grafo G);

char SwitchVertices(Grafo G,u32 i,u32 j);

char RMBCnormal(Grafo G);

char RMBCrevierte(Grafo G);

char RMBCchicogrande(Grafo G); //mal

char SwitchColores(Grafo G,u32 i,u32 j);

#endif