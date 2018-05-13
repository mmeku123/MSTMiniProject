#include <stdio.h> 
#include <limits.h>
#include "graph.h"

int i,v;
int V;
int G[50][50];

int minKey(int key[], int mstSet[])
{
    int min = INT_MAX, min_index;
    int v;
    for (v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

int printMST(int parent[], Graph graph)
{
    printf("\n --- Minimum Spanning Tree --- \n");
    printf("Start - End   Weight\n");
    for (i = 1; i < V; i++)
        printf(" %c - %c   %d \n", parent[i] + 'A', i + 'A', G[i][parent[i]]);
    printf("\n\n");
}

void primMST(Graph graph)
{
    int parent[V]; // Array to store constructed MST
    int key[V];    // Key values used to pick minimum weight edge in cut
    int mstSet[V]; // To represent set of vertices not yet included in MST

    for (i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST
    int count;

    for (count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);

        mstSet[u] = 1;

        for (v = 0; v < V; v++)

            if (G[u][v] && mstSet[v] == 0 && G[u][v] < key[v])
                parent[v] = u, key[v] = G[u][v];
    }
    printMST(parent, graph);
}