#include <Rii.h>

typedef GrafoSt *Grafo; 

//Funciones de Construccion/Destruccion/Copia del grafo

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);

Grafo CopiarGrafo(Grafo G);

//Funciones de coloreo

u32 Greedy(Grafo G);

int Bipartito(Grafo G);

//Funciones para extraer información de datos del grafo

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeLados(Grafo G);

u32 NumeroDeColores(Grafo G);

//Funciones de los vertices

u32 NombreDelVertice(Grafo G, u32 i);

u32 ColorDelVertice(Grafo G, u32 i);

u32 GradoDelVertice(Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);

//Funciones de ordenacion

char OrdenNatural(Grafo G);

char OrdenWelshPowell(Grafo G);

char SwitchVertices(Grafo G,u32 i,u32 j);

char RMBCnormal(Grafo G);

char RMBCrevierte(Grafo G);

char RMBCchicogrande(Grafo G);

char SwitchColores(Grafo G,u32 i,u32 j);
