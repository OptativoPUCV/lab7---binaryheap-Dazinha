#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

/*
1. Implemente la función `Heap* createHeap()`. Esta función crea un nuevo dato de tipo Heap inicializando sus variables. Considere que la capacidad incial es de 3 casillas para el arreglo.
> Recuerde reservar memoria para el Heap y también para el arreglo `heapArray`.
*/

Heap* createHeap(){
  Heap *newHeap = (Heap*) malloc(sizeof(Heap));

  if (newHeap != NULL)
  {
    newHeap -> capac = 3;
    newHeap -> size = 0;

    newHeap -> heapArray = (heapElem*)malloc(newHeap->capac * sizeof(heapElem));

    if (newHeap != NULL)
    {
      return newHeap; 
    }
    else
    {
      return NULL;
    }
    
  }

  
   return NULL;
}

/*
2. Implemente la función `void* heap_top(Heap* pq)`. Esta función retorna el dato con mayor prioridad del montículo. 
    > Recuerde que este dato se encuentra en la raíz el montículo, es decir, en la primera casilla del arreglo.
*/

void* heap_top(Heap* pq){
    
  if (pq -> size == 0) 
  {      
    return NULL;
  }

  //está en la raíz
  void *maximo = pq -> heapArray[0].data;
  
  return maximo;
}
/*
3. Implemente la función `void heap_push(Heap* pq, void* data, int p)`. Esta función inserta un nuevo dato con prioridad `p` en el montículo. Si no recuerda como insertar datos en el montículo puede ver las [diapositivas](https://docs.google.com/presentation/d/1ZjXWMf6g05WdICqvno_oyRvorjAThABgbRGbEqc7mYU/edit#slide=id.g55ac49ed61_0_167).

    > Si el arreglo está lleno aumente la capacidad al **doble + 1** usando la función `realloc` así:
    > `arreglo = realloc(arreglo, nueva_capacidad)`
*/

void heap_push(Heap* pq, void* data, int priority){
  heapElem newElem;

  newElem.data = data;
  newElem.priority = priority;

  if (pq -> size == pq -> capac)
  {
    pq -> capac = (pq -> capac * 2) + 1;
    pq -> heapArray = realloc(pq -> heapArray, pq -> capac * sizeof(heapElem));
  }
  
  int posicion = pq -> size;
  pq -> heapArray[posicion] = newElem;
  pq -> size++;

  while (posicion != 0 && pq -> heapArray[posicion].priority > pq->heapArray[(posicion - 1) / 2].priority) {
    heapElem temp = pq -> heapArray[posicion];
    pq -> heapArray[posicion] = pq -> heapArray[(posicion - 1) / 2];
    pq -> heapArray[(posicion - 1) / 2] = temp;
    
    posicion = (posicion - 1) / 2;
  }
  
}
/*
while (i != 0 && h->heapArray[parent(i)].priority < h->heapArray[i].priority) {
  swap(&(h->heapArray[i]), &(h->heapArray[parent(i)]));
  i = parent(i);
}

void swap(heapElem* x, heapElem* y) {
    heapElem temp = *x;
    *x = *y;
    *y = temp;
}
*/

/*
4. Implemente la función `void heap_pop(Heap* pq)`. Esta función elimina el mayor elemento del montículo (la raíz). Si no recuerda el procedimiento puede ver las [diapositivas](https://docs.google.com/presentation/d/1ZjXWMf6g05WdICqvno_oyRvorjAThABgbRGbEqc7mYU/edit#slide=id.g10c6e3d52b_0_98).
*/

void heap_pop(Heap* pq){
  
  //eliminar raíz
  //void* maximo = pq -> heapArray[0].data;
  
  pq -> heapArray[0] = pq -> heapArray[pq -> size - 1];
  pq -> size--;


  reajuste(pq, 0);
  
}

void reajuste(Heap* pq, int posicion) {
    int largest = posicion;
    int left = 2 * posicion + 1;
    int right = 2 * posicion + 2;

    if (left < pq -> size && pq->heapArray[left].priority > pq ->heapArray[largest].priority) {
        largest = left;
    }

    if (right < pq ->size && pq ->heapArray[right].priority > pq ->heapArray[largest].priority) {
        largest = right;
    }

    if (largest != posicion) 
    {
      while (posicion != 0 && pq -> heapArray[posicion].priority > pq->heapArray[(posicion - 1) / 2].priority) {
    heapElem temp = pq -> heapArray[posicion];
    pq -> heapArray[posicion] = pq -> heapArray[(posicion - 1) / 2];
    pq -> heapArray[(posicion - 1) / 2] = temp;
    
    posicion = (posicion - 1) / 2;
  }
        reajuste(pq, largest);
    }
}
