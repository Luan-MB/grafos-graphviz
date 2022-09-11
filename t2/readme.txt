Luan Machado Bernardt | GRR20190363
Lucas Soni Teixeira | GRR20190395

Trabalho de Implementação II - Grafos

    Nesse trabalho, foi implementada a função decompoe que encontra componentes fortes no grafo direcionado
g, bem como as funções auxiliares acha_pos_ordem, acha_componentes, inverte_grafo. As funções implementadas
no primeiro trabalho, exclusivas para grafos não direcionados, foram adptadas para grafos direcionados (se possível),
porém para a implementação da função decompoe, que era o objetivo do trabalho, as mesma não foram utilizadas;

FUNÇÔES IMPLEMENTADAS

    - acha_pos_ordem: Percorre o grafo g iniciando por um vértice v arbitrário, salvando em um vetor a ordem
    na qual cada vértice tem toda sua fronteira visitada.

    - inverte_grafo: Cria um grafo g_invertido, com os mesmos vértices de g, criados na mesma sequência que
    a pos ordem invertida de g, pois isso facilita na hora de percorrer os vértices na função decompoe, tendo
    em vista que como em g_invertido, os vértices já estão na sequência correta (pós ordem inversa), basta
    uma iteração simples sobre os vértices, com agfstnode e agnxtnode;

    - acha_componentes: Função recursiva que adiciona a um subgrafo todos os vértices pertencentes ao mesmo
    componente forte.

    - decompoe: A partir da pós ordem do grafo g, itera sobre os vértices do grafo g invertido, os quais já se
    encontram na ordem inversa da pós ordem, realizando uma busca em profundidade (dfs) em cada vértice 
    (se o mesmo já não foi visitado durante uma busca anterior), salvando os vértices alcançados em um subgrafo. 
    Após isso, para cada subgrafo obtido são inseridas as arestas pertencentes aos mesmos, ao final obtendo um 
    componente forte. O retorno da função é o grafo g, que entrou como parâmetro, com todos os seus componentes 
    fortes na forma de subgrafos, os quais podem ser iterados com o auxílio das funções agfstsubg e agnxtsubg, 
    e exibidos com escreve_grafo, passando o subgrafo como parâmetro;

Referências:

    - Documentação da biblioteca graphviz: https://graphviz.org/pdf/cgraph.pdf
    - Strongly connected componentes: https://www.geeksforgeeks.org/strongly-connected-components/

        