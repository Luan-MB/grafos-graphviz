Luan Machado Bernardt | GRR20190363
Lucas Soni Teixeira |

Trabalho de Implementação I - Grafos

    Nesse trabalho, foram implementadas as funções definidas no arquivo grafo.h, bem como funções auxiliares,
utilizando a biblioteca graphviz.h em linguagem C.

FUNÇÔES IMPLEMENTADAS

    Algumas das funções já haviam correspondentes na própria biblioteca graphviz.h, portanto suas implementações 
são apenas chamadas as mesmas, sendo elas:

    - le_grafo (agread);
    - destroi_grafo (agfree);
    - n_vertices (agnnodes);
    - n_arestas (agnedges);
    - grau (agdegree);

    As que foram realmente implementadas serão explicadas a seguir:

    - grau_maximo: Itera sobre todos os vértices do grafo G, utilizando o método da própria biblioteca,

        for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n)); 

    a cada vértice chama a função grau, comparando com o maior grau encontrado até o momento.  

    - grau_minimo: Análogo ao grau_maximo, mas comparando com o menor.

    - grau_medio: Retorna o resultado da divisão do dobro do número de arestas pelo número de vértices,
    pois cada aresta influencia em um grau em dois vértices distintos, logo é a mesma coisa que:

        (soma de todos os graus) / (número de vértices);
    
    - regular: Percorre todos os vértices, comparando o grau dos mesmos com o grau médio, caso todos os vértices
    tenham o mesmo grau, o valor desse grau será o mesmo do grau médio.

    - completo: Verifica se o grau médio é igual ao número de vértices - 1, caso seja, todos os vértices tem o
    maior grau possível, logo o grafo é completo.

    - conexo: Checa se o grafo é conexo utilizando uma busca em profundidade