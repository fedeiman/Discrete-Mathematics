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
  //Aloco espacio para dos arreglos.
  u32 *sinusar = (u32*)calloc((G->n),sizeof(u32));
  if(!sinusar){
    printf("ERROR PARA RESERVAR MEMORIA PARA ARREGLO SINUSAR EN FUN GREEDY");
    return 0;
  }
  u32 *usados = (u32*)calloc((G->n),sizeof(u32));
  if(!usados){
    printf("ERROR PARA RESERVAR MEMORIA PARA ARREGLO USADOS EN FUN GREEDY");
    return 0;
  }
  u32 c = 0;
  u32 color = 0;
  u32 resultado = 0;
  //Seteo el color decada vertice en "2^32 -1"
  for(u32 i = 0; i < G->n ; i++){
    G->o[i]->color_actual = ~0u;
  }
  //Recorro todos los vertices
  for(u32 i = 0; i < G->n; i++) {
    //Para cada vertice recorro sus vecinos.
    for(u32 j = 0; j < (G->v[i]->ind_de_final_vecinos - G->v[i]->ind_de_inicio_vecinos + 1); j++){
      //Si el vecino esta pintado marco en sinusar[color] 1 y en usados[n] el color
      //en sinusar marco con 1 el color usado y en usados el color
      if(G->o[G->v[i]->array_vecinos[j]]->color_actual != ~0u){
        sinusar[G->o[G->v[i]->array_vecinos[j]]->color_actual] = 1;
        usados[c++] = G->o[G->v[i]->array_vecinos[j]]->color_actual;
      }
    }
    //Busco el color que tengo que usar.  
    while(sinusar[color] == 1){
        color++;
    }
    //Me voy quedando con el maximo color.
    resultado = max(resultado,color + 1);
    //Asigno los colores.
    G->v[i]->color = color;
    G->o[G->v[i]->index]->color_actual = color;
    color = 0;
    //Limpio el arreglo usados.
    while(c){ 
      sinusar[usados[--c]] = 0;
    }
  }
  G->colores = resultado;
  if(sinusar) free(sinusar);
  if(usados) free(usados);

  return resultado;
}

int Bipartito(Grafo G) {
  u32 c = 0;
  u32 *usados = (u32*)calloc((G->n),sizeof(u32));
  if(!usados){
    printf("ERROR PARA RESERVAR MEMORIA PARA ARREGLO USADOS EN FUN BIPARTITO");
    return 0;
  }

  G->colores = 1;
  //Seteo los colores en "2^32-1".
  for(u32 i = 0; i < G->n ; i++){
    G->o[i]->color_actual = ~0u;
  }
  //Para cada vertice, si no fue pintado, lo pinto con 0.
  for(u32 i = 0; i < G->n; i++) if (G->o[i]->color_actual == ~0u){
      usados[c++] = i;
      G->o[i]->color_actual = 0;
      //Agarro el primer elmento en mi "stack"
      while(c != 0){
        u32 x = usados[--c];
        //Para cada vecino de mi vertice.
        for(u32 j = 0; j < G->o[x]->cant_vecinos; j++){
          //si el vertice no esta pintado, lo pinto con (G->o[x]->color_actual + 1) % 2, (0 o 1 si es bipartico)
          if(G->o[G->o[x]->array_vecinos[j]]->color_actual == ~0u) {
            G->o[G->o[x]->array_vecinos[j]]->color_actual = (G->o[x]->color_actual + 1) % 2;
            //Una ves pintado, lo pongo en el stack para ver sus vecinos.
            usados[c++] = G->o[x]->array_vecinos[j];
            G->colores = 2;
          }
          //Si el vertice esta pintado con el color G->o[x]->color_actual entonces el grafo no es bipartito.
          else if (G->o[G->o[x]->array_vecinos[j]]->color_actual == G->o[x]->color_actual){
            Greedy(G);
            if(usados) free(usados);          
            return 0;
          }
        }
      }
  }
  if(usados) free(usados);
  return 1;
}
#endif