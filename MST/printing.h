#include <stdio.h>

int i, j, V;
int G[50][50];

void printAdjMatrix(Graph graph)
{
    printf("\n   ");
    // print abv A B C D E F
    for (i = 0; i < V; i++)
    {
        printf("%2c ", graph.vertices[i].abv);
    }
    printf("\n");

    // print adj matrix
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            // print abv
            if (j == 0)
                printf("%2c ", graph.vertices[i].abv);
            printf("%2d ", G[i][j]);
        }
        printf("\n");
    }
    // comparasion abv <--> full name
    for (i = 0; i < graph.vertexSize; i++)
    {
        printf(" %c <==> %s, \n", graph.vertices[i].abv, graph.vertices[i].name);
    }
}

void printGraphData(Graph graph)
{
    printf("\n<- GRAPH INFO ->\n\n");
    printf("Graph name : %s\n", graph.name);
    printf("Vertices size : %d\n", graph.vertexSize);
    printf("Edges size : %d\n", graph.edgeSize);
    printf("\n- Adj. matrix - ");
    printAdjMatrix(graph);
}