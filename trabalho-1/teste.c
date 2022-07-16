#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  escreve_grafo(g);
  
  printf("Número de vértices = %d\n", n_vertices(g));
  printf("Número de arestas = %d\n", n_arestas(g));
  printf("Grau máximo = %d\n", grau_maximo(g));

  destroi_grafo(g);

  return 0;
}
