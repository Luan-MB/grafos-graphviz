#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) {

  	return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
  
	agfree(g, NULL);
	return 1;
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  
  	return agwrite(g, stdout);
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  
  	return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  
  	return agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  
  	return agdegree(g, v, TRUE, TRUE);
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  
	int grau_max = 0;
	int grau_n;

	for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n))
		if ((grau_n = grau(n, g)) > grau_max)
		grau_max = grau_n;
	return grau_max;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  
	int grau_min = n_vertices(g) - 1;
	int grau_n;

	for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n))
		if ((grau_n = grau(n, g)) < grau_min)
		grau_min = grau_n;
	return grau_min;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  
  	return ((n_arestas(g) * 2) / n_vertices(g));
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  
	int grau_avg = grau_medio(g);

	for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n))
		if (grau_avg != grau(n, g))
		return 0;
	return 1;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
	if (grau_medio(g) == (n_vertices(g) - 1))
		return 1;
	return 0;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

