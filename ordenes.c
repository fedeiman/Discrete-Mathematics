#ifndef _ORDENES
#define _ORDENES
#include "grafo.c"
#include "vecinos.c"

char OrdenNatural(Grafo G){
  for(u32 i = 0; i < G->n; i++){
    G->v[i]->nombre_del_vertice = G->v[i]->nombre_del_vertice; 
  }
  return 0;
}

//char OrdenWelshPowell(Grafo G){}


#endif