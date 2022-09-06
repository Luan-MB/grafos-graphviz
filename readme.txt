Luan Machado Bernardt | GRR20190363
Lucas Soni Teixeira | GRR20190395

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

    - conexo: Checa se o grafo é conexo utilizando uma busca em profundidade, iniciando a partir do primeiro nodo
    obtido pela função agfstnode, da própria biblioteca, itera sobre todas as arestas do vértice, chamando a função
    recursivamente para os vértices vizinhos. Quando visitado pela primeira vez, o vértice é salvo em um vetor
    de visitados. Ao final compara se o número de vértices no vetor é igual a n_vertices, ou seja, foi possível
    visitar todos eles.

    - bipartido: Determina se o grafo é bipartido, utilizando um algoritmo recursivo de coloração de vértices, que 
    tenta colorir os vértices do grafo com 2 cores. Quando um vértice é colorido com uma cor, verifica-se na 
    matriz de adjacência se há algum vizinho com a mesma cor, caso haja tenta-se colorir com a outra cor, se
    também não for possível, retorna-se na recursão. Caso a cor seja válida, chama-se a função recursivamente 
    para o próximo vértice na matriz. Se o algoritmo chegar ao último vértice e encontrar uma cor válida,
    significa que o grafo é bipartido.

    - n_triangulos: Conta quantos triângulos existem no grafo, por meio da matriz de adjacência do grafo ao cubo.
    A diagonal principal da matriz de adjacência de um grafo elevada a 3, possui a quantidade de passeios de
    tamanho 3 que iniciam e terminam no vértice i, ou seja, triângulos. No entanto, cada vértice presente no
    ciclo, terá seu valor correspondente na diagonal principal incrementado em 2, pois existem passeios em ambos
    os sentidos, portanto deve-se dividir a soma da diagonal por 6, pois um triãngulo representa duas unidades em 3
    vértices diferentes.

    - matriz_adjacencia: Itera sobre os vértices do grafo, verificando a existência de arestas entre i e j, por meio
    da função:

        agedge(g, i, j, NULL, FALSE);

    que quando possui o último parâmetro definido com FALSE, retorna se existe a aresta em g. Para cada combinação de
    i e j, a posição i j da matriz é preenchida com 1 caso exista aresta e 0 senão.

    - complemento: Cria um novo grafo e percorre todos os vértices do grafo original, os copiando para o complemento. 
    Após isso, para cada vértice i e j, verifica a existência de uma aresta, assim como visto na função acima, caso 
    não exista uma aresta entre i e j no grafo, ela deve ser criada no complemento. 
    As funções de criação de um grafo, vértices e arestas utilizadas são, respectivamente:

        agopen("Complementar", Agstrictundirected, NULL);

        Cria um grafo com nome "Complementar" que é estritamente não direcionado, com isso não é possível haver arestas
        entre i e j em ambos os sentidos, apenas um.

        agnode(complement, agnameof(n), TRUE);

        Cria um vértice com nome agnameof(n) no grafo apontado por complement. Caso O último parâmetro seja FALSE,
        será verificada a existência do vértice.

        agedge(complement, i, j, NULL, TRUE);
        
        Cria a aresta entre i e j no grafo apontado por complement. Caso o último argumetno seja FALSE, como já visto,
        apenas verifica a existência da aresta i--j;

Referências:

    - Documentação da biblioteca graphviz: https://graphviz.org/pdf/cgraph.pdf
    - Triângulos em um grafo: https://www.geeksforgeeks.org/number-of-triangles-in-a-undirected-graph/
    - Coloração de grafos: https://www.geeksforgeeks.org/m-coloring-problem-backtracking-5/

        