#ifndef _INFO
#define _INFO

#include "grafo.c"
#include "vecinos.c"

u32 NumeroDeVertices(Grafo G){
  return(G->n);
}

u32 NumeroDeLados(Grafo G){
  return(G->m);
}
u32 NumeroDeColores(Grafo G){
  return(G->color);
}

u32 NombreDelVertice(Grafo G, u32 i){
  return(G->v[i]->nombre_del_vertice);
}

u32 ColorDelVertice(Grafo G, u32 i){
  if(i >= G->n)
    return -1;
  else 
    return(G->v[i]->color);
}

u32 GradoDelVertice(Grafo G, u32 i){
  if(i >= G->n)
    return -1;
  else 
    return(G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1);
}

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j){
  if(i >= G->n || j >= G->n)
    return -1;
  else 
    return(G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1);
}








#endif

