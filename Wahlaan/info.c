#ifndef _INFO
#define _INFO

#include "grafo.c"
#include "vecinos.c"
#include "orden.c"

u32 NumeroDeVertices(Grafo G){
  return(G->n);
}

u32 NumeroDeLados(Grafo G){
  return(G->m);
}

u32 NumeroDeColores(Grafo G){
  return(G->colores);
}

u32 NombreDelVertice(Grafo G, u32 i){
  return(G->v[i]->nombre_del_vertice);
}

u32 ColorDelVertice(Grafo G, u32 i){
  if(i >= G->n){
    printf("i es mayor o igual a la cantidad de vertices");
    return -1;
  } 
  else 
    return(G->o[G->v[i]->index]->color_actual);
}

u32 GradoDelVertice(Grafo G, u32 i){
  if(i >= G->n){
    printf("i es mayor o igual a la cantidad de vertices");
    return -1;
  }  
  else 
    return(G->v[i]->total_vecinos);
}

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j){
  if(i >= G->n || j >= G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1 ){
    return -1;
    printf("i es mayor a la cantidad de vertices o j es mayor a la cantiad de vecinos");
  }  
  else 
    return(G->o[G->v[i]->array_vecinos[j]]->color_actual);
}

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j){
    if(i >= G->n || j >= G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1 ){
    printf("i es mayor a la cantidad de vertices o j es mayor a la cantiad de vecinos");  
    return -1;
    }
  else 
    return(G->o[G->v[i]->array_vecinos[j]]->nombre);
}

#endif

