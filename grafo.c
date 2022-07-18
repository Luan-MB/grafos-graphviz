#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) {

  	return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
  
	agfree(g, NULL);
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  	agwrite(g, stdout);
  	return g;
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
  
	if (grau_medio(g) == (agnnodes(g) - 1))
		return 1;
	return 0;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
	return n_vertices(g);
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  	
	return n_vertices(g);
}

static int **multiplica_matriz(int **matriz_a, int** matriz_b, int tam) {

	int **matriz_mult = (int **) malloc ((size_t) tam * sizeof(int *));
	for (int i = 0; i < tam; ++i) {
		matriz_mult[i] = (int *) calloc ((size_t) tam, sizeof(int));
	}

	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			
			for (int k = 0; k < tam; ++k)
				matriz_mult[i][j] += matriz_a[i][k] * matriz_b[k][j];

		}
	}

	return matriz_mult;
}

static int soma_diagonal(int **matriz, int tam) {
	int soma = 0;
	for (int i = 0; i < tam; i++) {
		soma += matriz[i][i];
	}
	return soma;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
	
	int **adj_matriz = matriz_adjacencia(g);
	int **adj_matriz_sqr = multiplica_matriz(adj_matriz, adj_matriz, n_vertices(g));
	int **adj_matriz_cub = multiplica_matriz(adj_matriz, adj_matriz_sqr, n_vertices(g));
	
	return (soma_diagonal(adj_matriz_cub, n_vertices(g)) / 6);
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
		
	int **matriz = (int **) malloc ((size_t) n_vertices(g) * sizeof(int *));
	for (int i = 0; i < n_vertices(g); ++i) {
		matriz[i] = (int *) calloc ((size_t) n_vertices(g), sizeof(int));
	}
  
	int lin = 0, col = 0;
	for (Agnode_t *vert1 = agfstnode(g); vert1; vert1 = agnxtnode(g, vert1)) {
		for (Agnode_t *vert2 = agfstnode(g); vert2; vert2 = agnxtnode(g, vert2)) {
			if (agedge(g, vert1, vert2, NULL, FALSE) != NULL)
				matriz[lin][col] = 1;
			col++;
		}
		lin++;
		col = 0;
	}

  	return matriz;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
	
	Agraph_t *complement;
	complement = agopen("Complementar", Agstrictundirected, NULL);

	for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n)) {
		agnode(complement, agnameof(n), TRUE);
	}

	for (Agnode_t *vert1 = agfstnode(g); vert1; vert1 = agnxtnode(g, vert1)) {
		for (Agnode_t *vert2 = agfstnode(g); vert2; vert2 = agnxtnode(g, vert2)) {
			if (vert2 != vert1) {
				if (agedge(g, vert1, vert2, NULL, FALSE) == NULL) {
					agedge(complement, agnode(complement, agnameof(vert1), FALSE), agnode(complement, agnameof(vert2), FALSE), NULL, TRUE);
				}
			}
		}
	}

	agwrite(complement, stdout);
	
  	return complement;
}

