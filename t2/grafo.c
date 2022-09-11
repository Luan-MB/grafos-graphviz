// Luan Machado Bernardt | GRR20190363
// Lucas Soni Teixeira | GRR20190395

#include <stdio.h>
#include "grafo.h"

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
  
	agclose(g);
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
	if (grau_avg % 2 != 0)
		return 0;

	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n)) {
		int grau_saida = agdegree(g, n, FALSE, TRUE);
		int grau_entrada = agdegree(g, n, TRUE, FALSE);

		if ((grau_saida != grau_avg/2) || (grau_entrada != grau_avg/2))
			return FALSE;
	}
	
	return TRUE;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
	for (vertice v1 = agfstnode(g); v1; v1 = agnxtnode(g, v1))
		for (vertice v2 = agfstnode(g); v2; v2 = agnxtnode(g, v2))
			if (v1 != v2)
				if (!agedge(g, v1, v2, NULL, FALSE))
					return FALSE;
	return TRUE;
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

	for (Agedge_t *e = agfstout(g,n); e; e = agnxtout(g,e)) {
			if (!vertice_visitado(visitados, size, e->node))
				check_edges(e->node, g, visitados, size);
		}

	for (Agedge_t *e = agfstin(g,n); e; e = agnxtin(g,e)) {
			if (!vertice_visitado(visitados, size, e->node))
				check_edges(e->node, g, visitados, size);
		}

}

// -----------------------------------------------------------------------------
int conexo(grafo g) {

	vertice vertice_inicial = agfstnode(g);
	vertice *visitados = (vertice *) malloc ((size_t) n_vertices(g) * sizeof(vertice));
	int i_vis = 0;

	check_edges(vertice_inicial, g, visitados, &i_vis);

	if (i_vis == n_vertices(g))
		return TRUE;
	return FALSE;
}

static int cor_valida(int **adj_matriz, int *colors, int size) {

	for (int i=0; i<size; ++i)
		for (int j=0; j<size; ++j)
			if (adj_matriz[i][j] && (colors[j] == colors[i]))
				return FALSE;
	return TRUE;
}

static int colore_grafo(int **adj_matriz, int *colors, int i, int size) {

	if (i == size)
		return TRUE;

	for (int j=1; j<=N_COLORS; ++j) {
		colors[i] = j;

		if (cor_valida(adj_matriz, colors, i+1))
			if (colore_grafo(adj_matriz, colors, i+1, size))
				return TRUE;
	}

	return FALSE;
}


// -----------------------------------------------------------------------------
int bipartido(grafo g) {
	
	int **adj_matriz = matriz_adjacencia(g);
	int *colors = calloc ((size_t) n_vertices(g), sizeof(int));

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

int n_triangulos(grafo g) {
	
	int **adj_matriz = matriz_adjacencia(g);
	int **adj_matriz_sqr = multiplica_matriz(adj_matriz, adj_matriz, n_vertices(g));
	int **adj_matriz_cub = multiplica_matriz(adj_matriz, adj_matriz_sqr, n_vertices(g));
	
	return (soma_diagonal(adj_matriz_cub, n_vertices(g)) / 3);
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
	char nome[] = "g_complementar";
	complement = agopen(nome, Agstrictdirected, NULL);

	// Cria todos os vertices de g em g_complementar
	for (vertice n = agfstnode(g); n; n = agnxtnode(g, n)) {
		agnode(complement, agnameof(n), TRUE);
	}

	// Cria todos os arcos ausentes em g em g_complementar
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

static void acha_pos_ordem(grafo g, vertice *visitados, vertice vert, int *tamanho, vertice *pos_ordem, int *p_tamanho) {

	if (vertice_visitado(visitados, tamanho, vert)) {
		return;
	}

    visitados[(*tamanho)++] = vert;

	// Itera sobre os arcos cujo vert é cauda
    for (vertice v = agfstnode(g); v; v = agnxtnode(g, v)) {
        if (agedge(g, vert, v, NULL, FALSE)) {
          	acha_pos_ordem(g, visitados, v, tamanho, pos_ordem, p_tamanho);
		}
    }

    pos_ordem[(*p_tamanho)++] = vert;
}

static void acha_componentes(grafo g, vertice *visitados, vertice vert, int *tamanho, grafo subgrafo) {

    visitados[(*tamanho)++] = vert;
	// Adiciona o vertice ao subgrafo
	agnode(subgrafo, agnameof(vert), TRUE);

	// Itera sobre os arcos cujo vert é cauda
    for (vertice v = agfstnode(g); v; v = agnxtnode(g, v)) {
        if ((agedge(g, vert, v, NULL, FALSE)) && (!vertice_visitado(visitados, tamanho, v))) {
          	acha_componentes(g, visitados, v, tamanho, subgrafo);
		}
    }

}

static grafo inverte_grafo(grafo g, vertice *pos_ordem, int n_vert) {

	char nome[] = "g_reverso";
	grafo g_reverso = agopen(nome, Agdirected, NULL);

	// Cria os vertices no grafo na pos ordem inversa
	for (int i=(n_vert-1); i>=0; --i) {
		agnode(g_reverso, agnameof(pos_ordem[i]), TRUE);
	}

	// Cria os arcos em g no sentido contrario
	for (vertice v1 = agfstnode(g); v1; v1 = agnxtnode(g, v1)) {
		for (vertice v2 = agfstnode(g); v2; v2 = agnxtnode(g, v2)) {
			if (agedge(g, v1, v2, NULL, FALSE)) {
				agedge(g_reverso, agnode(g_reverso, agnameof(v2), FALSE), agnode(g_reverso, agnameof(v1), FALSE), NULL, TRUE);
			}
		}
	}

	return g_reverso;
}

//------------------------------------------------------------------------------
grafo decompoe(grafo g) {

	if (!agisdirected(g))
		return 0;
		
	int num_verts = n_vertices(g);

    vertice *visitados_um = malloc ((size_t) num_verts * sizeof(vertice));
	int visitados_tam = 0;

	vertice *pos_ordem = malloc ((size_t) num_verts * sizeof(vertice));
	int pos_ordem_t = 0;

	// Percorre o grafo g salvando a pos ordem
	for (vertice vert = agfstnode(g); vert; vert = agnxtnode(g, vert)) {
		acha_pos_ordem(g, visitados_um, vert, &visitados_tam, pos_ordem, &pos_ordem_t);
	}

	// A partir da pos ordem gera um grafo g_invertido com os arcos de g em sentidos opostos
	grafo invertido = inverte_grafo(g, pos_ordem, num_verts);
	
	vertice *visitados_dois = malloc ((size_t) num_verts * sizeof(vertice));
	visitados_tam = 0;

	int componentes_fortes = 0;

	// Percorre o g_invertido a partir da pos ordem inversa criando subgrafos para cada componente forte
	for (vertice vert = agfstnode(invertido); vert; vert = agnxtnode(invertido, vert)) {
		if (!vertice_visitado(visitados_dois, &visitados_tam, vert)) {

			grafo subgrafo = agsubg(g, NULL, TRUE);

			componentes_fortes++;
			acha_componentes(invertido, visitados_dois, vert, &visitados_tam, subgrafo);
		}
	}

	free(visitados_um);
	free(pos_ordem);
	free(visitados_dois);
	destroi_grafo(invertido);

	// Adiciona os arcos nos subgrafos de g
	for (grafo h = agfstsubg(g); h; h = agnxtsubg(h))
		for (vertice v1 = agfstnode(h); v1; v1 = agnxtnode(h, v1))
			for (vertice v2 = agfstnode(h); v2; v2 = agnxtnode(h, v2)) {
				if (agedge(g, v1, v2, NULL, FALSE))
					agedge(h, v1, v2, NULL, TRUE);
			}

	return g;
}

