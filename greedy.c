#ifndef _GREEDY
#define _GREEDY

#include "Rii.h"
#include "grafo.c"
#include "orden.c"
#include "vecinos.c"

u32 binaria(Orden *o, u32 dato, u32 array_lenght){
  u32 inf = 0; 
  u32 sup = array_lenght - 1;
  u32 mitad;
  while(inf<=sup){
    mitad = (inf + sup)/2;
    if(o[mitad]->nombre == dato){
      return mitad;
    }
    if(o[mitad]->nombre > dato){
      sup = mitad - 1;
    }
    if(o[mitad]->nombre < dato){
      inf = mitad + 1;
    }
  }
  //Esta linea se ejecutara solo en caso de que el "dato"
  //a buscar no este en v[n]->nombre_del_vetice.
  //Cosa que no puede pasar.
  printf("ERROR");
  return(-1);
}

u32 max(u32 i, u32 j){
  if(i <= j) return j;
  else return i;
}

u32 Greedy(Grafo G){
  u32 *sinusar = (u32*)calloc((G->n),sizeof(u32));
  if(!sinusar){
    printf("ERROR PARA RESERVAR MEMORIA PARA ARREGLO SINUSAR EN FUN GREEDY");
    return 0;
  }
  u32 *usados = (u32*)calloc((G->n),sizeof(u32));
  if(!sinusar){
    printf("ERROR PARA RESERVAR MEMORIA PARA ARREGLO USADOS EN FUN GREEDY");
    return 0;
  }
  u32 c = 0;
  u32 color = 0;
  u32 resultado = 0;
  
  for(u32 i = 0; i < G->n ; i++){
    G->o[i]->color_actual = ~0u;
  }
  for(u32 i = 0; i < G->n; i++){
    for(u32 j = 0; j < (G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1); j++){
      if(G->o[G->v[i]->array_vecinos[j]]->color_actual != ~0u){
        sinusar[G->o[G->v[i]->array_vecinos[j]]->color_actual] = 1;
        usados[c++] = G->o[G->v[i]->array_vecinos[j]]->color_actual;
      }
    }  
    while(sinusar[color] == 1){
        color++;
    }
    resultado = max(resultado,color + 1);
    G->v[i]->color = color;
    G->o[binaria(G->o,G->v[i]->nombre_del_vertice,G->n)]->color_actual = color;
    color = 0;
    while(c){ 
      sinusar[usados[--c]] = 0;
    }
    //memset(sinusar,0,G->n*sizeof(u32));
  }
  G->colores = resultado;
  if(sinusar) free(sinusar);
  if(usados) free(usados);
  
  return resultado;
}

#endif