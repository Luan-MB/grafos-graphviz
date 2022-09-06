#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  escreve_grafo(g);
  printf("%d\n", decompoe(g));
  destroi_grafo(g);

  return 0;
}
