// Luan Machado Bernardt | GRR20190363
// Lucas Soni Teixeira | GRR20190395
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_COLORS 2

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

	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n))
		if ((grau_n = grau(n, g)) > grau_max)
		grau_max = grau_n;
	return grau_max;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  
	int grau_min = n_vertices(g) - 1;
	int grau_n;

	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n))
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

	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n))
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

static int vertice_visitado (vertice *visitados, int *size, vertice v) {

	for (int i=0; i<(*size); ++i)
		if (visitados[i] == v)
			return TRUE;
	return FALSE;
}

static void check_edges(vertice n, grafo g, vertice *visitados, int *size) {

	if (!vertice_visitado(visitados, size, n)) {
		visitados[*size] = n;
		(*size)++;
	}

	// Itera sobre todas as arestas que incidem em n
	// Caso o outro vertice no qual a aresta incide, nao tenha sido visitado verifica-se fronteira do mesmo
	for (Agedge_t *e = agfstout(g,n); e; e = agnxtout(g,e)) {
			if (!vertice_visitado(visitados, size, e->node))
				verifica_arestas(e->node, g, visitados, size);
		}

	for (Agedge_t *e = agfstin(g,n); e; e = agnxtin(g,e)) {
			if (!vertice_visitado(visitados, size, e->node))
				verifica_arestas(e->node, g, visitados, size);
		}

}

// -----------------------------------------------------------------------------
int conexo(grafo g) {


	vertice vertice_inicial = agfstnode(g);
	vertice *visitados = (vertice *) malloc ((size_t) n_vertices(g) * sizeof(vertice));
	int i_vis = 0;

	// Verifica a fronteira do vertice inicial
	verifica_arestas(vertice_inicial, g, visitados, &i_vis);

	if (i_vis == n_vertices(g))
		return TRUE;
	return FALSE;
}

static int cor_valida(int **adj_matriz, int *colors, int size) {

	// Verifica se nao existem vizinhos com a mesma cor
	for (int i=0; i<size; ++i)
		for (int j=i+1; j<size; ++j)
			if (adj_matriz[i][j] && (colors[j] == colors[i]))
				return FALSE;
	return TRUE;
}

static int colore_grafo(int **adj_matriz, int *colors, int i, int size) {

	// Se coloriu todos os vertices
	if (i == size)
		return TRUE;

	for (int j=1; j<=N_COLORS; ++j) {
		// Colore o vertice i com a cor j
		colors[i] = j;

		if (cor_valida(adj_matriz, colors, i+1))
			// Chama a funcao para o proximo vertice
			if (colore_grafo(adj_matriz, colors, i+1, size))
				return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
	
	int **adj_matriz = matriz_adjacencia(g);
	int *colors = calloc ((size_t) n_vertices(g), sizeof(int));

	// Tenta colorir o grafo com 2 cores
	if (colore_grafo(adj_matriz, colors, 0, n_vertices(g)))
		return TRUE;
	return FALSE;
}

// -----------------------------------------------------------------------------
static int **multiplica_matriz(int **matriz_a, int** matriz_b, int tam) {

	int **matriz_mult = (int **) malloc ((size_t) tam * sizeof(int *));
	for (int i = 0; i < tam; ++i) {
		matriz_mult[i] = (int *) calloc ((size_t) tam, sizeof(int));
	}

	// Multiplica a matriz a pela matriz b
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

	// Soma a diagonal da matriz
	for (int i = 0; i < tam; i++) {
		soma += matriz[i][i];
	}
	return soma;
}

int n_triangulos(grafo g) {
	
	int **adj_matriz = matriz_adjacencia(g);
	int **adj_matriz_sqr = multiplica_matriz(adj_matriz, adj_matriz, n_vertices(g));
	int **adj_matriz_cub = multiplica_matriz(adj_matriz, adj_matriz_sqr, n_vertices(g));
	
	// Calcula o numero de triangulos em g
	return (soma_diagonal(adj_matriz_cub, n_vertices(g)) / 6);
}

static void print_matriz(int **adj_matriz, int size) {

	for (int i=0; i<size; ++i) {
		for (int j=0; j<size; ++j)
			printf("%d ", adj_matriz[i][j]);
		printf("\n");
	}
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
		
	int **matriz = (int **) malloc ((size_t) n_vertices(g) * sizeof(int *));
	for (int i = 0; i < n_vertices(g); ++i) {
		matriz[i] = (int *) calloc ((size_t) n_vertices(g), sizeof(int));
	}
  
	int lin = 0, col = 0;
	for (vertice vert1 = agfstnode(g); vert1; vert1 = agnxtnode(g, vert1)) {
		for (vertice vert2 = agfstnode(g); vert2; vert2 = agnxtnode(g, vert2)) {
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

	// Cria o grafo complementar
	complement = agopen("Complementar", Agstrictundirected, NULL);

	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n)) {
		agnode(complement, agnameof(n), TRUE);
	}

	for (vertice vert1 = agfstnode(g); vert1; vert1 = agnxtnode(g, vert1)) {
		for (vertice vert2 = agfstnode(g); vert2; vert2 = agnxtnode(g, vert2)) {
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

