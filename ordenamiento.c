#ifndef _ORDENAMIENTO
#define _ORDENAMIENTO

#include "Rii.h"
#include "grafo.c"
//#include "construccion.c"
#include "vecinos.c"
#include "orden.c"

int grado(Vecino v){
  return (v->total_vecinos);
}

  int powell(const void *pa, const void *pb){
  u32 n1,n2;
  Vecino *a = (Vecino *)pa;
  Vecino *b = (Vecino *)pb;
  n1 = grado(*a);  
  n2 = grado(*b);
  if(n1 > n2) return(-1);
  else if(n1 < n2) return(1);
  else return(0);
}
int color(Vecino v){
  return(v->color);
}
int cant_col(Vecino v){
  return(v->cant_color);
}

int RMBCn(const void *pa, const void *pb){
  u32 n1,n2;
  Vecino *a = (Vecino *)pa;
  Vecino *b = (Vecino *)pb;
  n1 = color(*a);  
  n2 = color(*b);
  if(n1 < n2) return(-1);
  else if(n1 > n2) return(1);
  else return(0);
}

int RMBCr(const void *pa, const void *pb){
  u32 n1,n2;
  Vecino *a = (Vecino *)pa;
  Vecino *b = (Vecino *)pb;
  n1 = color(*a);  
  n2 = color(*b);
  if(n1 < n2) return(-1);
  else if(n1 > n2) return(1);
  else return(0);
}

int RMBCc(const void *pa, const void *pb){
  u32 n1,n2;
  Vecino *a = (Vecino *)pa;
  Vecino *b = (Vecino *)pb;
  n1 = cant_col(*a);  
  n2 = cant_col(*b);
  if(n1 > n2) return(-1);
  else if(n1 < n2) return(1);
  else return(0);
}

char OrdenNatural(Grafo G){
  for(u32 i = 0; i < G->n; i++){
    G->v[i]->nombre_del_vertice = G->v[i]->nombre_del_vertice; 
  }
  return 0;
}

char OrdenWelshPowell(Grafo G){
  qsort(G->v,G->n,sizeof(G->v[0]),powell);
  return 0;
}

char SwitchVertices(Grafo G,u32 i,u32 j){
  if(i >= G->n || j >= G->n){
    printf("i o j es mayor a la cantidad de vertices");
    return (1);
  }  
  else{
    Vecino n = G->v[i];
    G->v[i] = G->v[j];
    G->v[j] = n;
    return 0;
  }
}
char RMBCnormal(Grafo G){
  qsort(G->v,G->n,sizeof(G->v[0]),RMBCn);
  return 0;
}

char RMBCrevierte(Grafo G){
  qsort(G->v,G->n,sizeof(G->v[0]),RMBCr);
  return 0;
}

char RMBCchicogrande(Grafo G){
	u32 *cancol = (u32*)calloc(G->n,sizeof(u32));
  if(!cancol){
    printf("ERROR AL RESERVAR MEMORIA PARA RMBCchicogrande");
    return 1;
  } 
	for(u32 i = 0; i < G->n; i++){
		cancol[G->v[i]->color] = cancol[G->v[i]->color] + 1; 
	}
  for(u32 i = 0; i < G->n; i++){
    G->v[i]->cant_color = cancol[G->v[i]->color];
  }
  qsort(G->v,G->n,sizeof(G->v[0]),RMBCc);
  if(cancol) free(cancol);
  return 0;
}

char SwitchColores(Grafo G,u32 i,u32 j){
  if(i > G->colores || j > G->colores){
    printf("i o j son mayores a la cantidad de colores");
    return 1;
  }
  else{
    for(u32 h = 0; h < G->n; h++){
      if(G->v[h]->color == i){ 
        G->v[h]->color = j;
      }
      else if(G->v[h]->color == j){
        G->v[h]->color = i;
      }
    }
  }
  return 0;
}

#endif