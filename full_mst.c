#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>

int N, i, j, v;
int V, E;
int G[50][50];

typedef struct Vertices
{
    char name[50];
    char abv;
} Vertex;

typedef struct Edges
{
    char start;
    char end;
    int weight;
} Edge;

typedef struct Graphs
{
    char name[50];
    Vertex vertices[50];
    Edge edge[50];
    int vertexSize;
    int edgeSize;
} Graph;

int minKey(int key[V], int mstSet[V])
{
    int min = INT_MAX, min_index;
    int v;
    for (v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

int printMST(int parent[V], Graph graph)
{
    printf("\n --- Minimum Spanning Tree --- \n");
    for (i = 1; i < V; i++)
        printf(" %c - %c   %d \n", parent[i] + 'A', i + 'A', G[i][parent[i]]);
    printf("\n\n");
}

void primMST(Graph graph)
{
    int parent[V]; // Array to store constructed MST
    int key[V];    // Key values used to pick minimum weight edge in cut
    int mstSet[V]; // To represent set of vertices not yet included in MST
    // printAdjMatrix(graph);
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

// int** adjMatrix(Graph graph)
// {
//     int G[50][50];
//     int i;
//     for (i = 0; i < graph.edgeSize; i++)
//     {
//         char start = graph.edge[i].start;
//         char end = graph.edge[i].end;
//         G[start - 'A'][end - 'A'] = graph.edge[i].weight;
//     }
//     return G;
// }

void printAdjMatrix(Graph graph)
{
    printf("\n   ");
    for (i = 0; i < V; i++)
    {
        printf("%2c ", graph.vertices[i].abv);
    }
    printf("\n");
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            if (j == 0)
                printf("%2c ", graph.vertices[i].abv);
            printf("%2d ", G[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < graph.vertexSize; i++)
    {
        printf(" %c == %s, \n", graph.vertices[i].abv, graph.vertices[i].name);
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

Graph CreateNewGraph()
{
    Graph graph;
    fflush(stdin);
    printf("Enter graph name : ");
    gets(graph.name);
    printf("Graph name = %s \n", graph.name);
    // do
    // {
    printf("Enter vertices size : ");
    scanf("%d", &V);
    // } while (isalpha(V));
    fflush(stdin);
    graph.vertexSize = V;
    for (i = 0; i < graph.vertexSize; i++)
    {
        graph.vertices[i].abv = 'A' + i;
        printf(" %d Enter vertex %c name : ", i + 1, graph.vertices[i].abv);
        gets(graph.vertices[i].name);
        // scanf("%s", &graph.vertices[i].name);
    }
    for (i = 0; i < graph.vertexSize; i++)
    {
        printf(" %c == %s\n", graph.vertices[i].abv, graph.vertices[i].name);
    }
    // do
    // {
    printf("Enter edges size : ");
    scanf(" %d", &E);
    // } while (isalpha(E));
    printf("%d vertices, %d edges\n", V, E);
    printf("Enter start-vertex, end-vertex and distance (ex. A B 10) \n");
    graph.edgeSize = E;
    for (i = 0; i < E; i++)
    {
        char start, end;
        int w;
        int validType;
        int failCount = 0;
        do
        {
            validType = 1;
            printf(" Edge %d (start end distance): ", i + 1);
            scanf(" %c %c %d", &start, &end, &w);
            start = toupper(start);
            end = toupper(end);
            if (start == end)
            {
                printf("%c to %c is not valid. ");
                validType = 0;
            }
            if (start > 'A' + graph.vertexSize - 1 || !isalpha(start))
            {
                printf("%c is not exists in vertex lists.", start);
                validType = 0;
            }
            if (end > 'A' + graph.vertexSize - 1 || !isalpha(end))
            {
                printf("%c is not exists in vertex lists.", end);
                validType = 0;
            }
            // if(!isdigit(w))
            // {
            //     printf("Distance is invalid. ");
            //     validType = 0;
            // }
            if (failCount > 1)
                printf("Please create this edge again.");
            failCount++;
        } while (!validType);
        G[start - 'A'][end - 'A'] = w;
        G[end - 'A'][start - 'A'] = w;
        graph.edge[i].start = start;
        graph.edge[i].end = end;
        graph.edge[i].weight = w;
    }

    // G = adjMatrix(graph);
    printf("\nCreate graph success!!\n");

    return graph;
}

Graph ImportGraph()
{
    Graph graph;
    struct dirent *de;
    char dname[10] = "";
    DIR *dr = opendir("data");
    FILE *file;
    int gn;
    if (dr == NULL)
    {
        printf("Could not open data directory");
    }
    while ((de = readdir(dr)) != NULL)
    {
        if (strstr(de->d_name, ".dat"))
        {
            char fname[40] = "data/";
            char graphName[50];
            strncpy(dname, de->d_name, de->d_namlen - 4);
            strcat(fname, de->d_name);
            file = fopen(fname, "r+");
            fgets(graphName, 1000, file);
            printf("\n %s : %s", dname, graphName);
            fclose(file);
        }
    }
    closedir(dr);
    int w;
    char fname[40] = "data/";
    char choosebuf[10];
    int countline = 1;
    char *line;
    size_t len = 0;
    printf("\nChoose graph no. : ");
    scanf("%d", &gn);
    itoa(gn, choosebuf, 10);
    strcat(fname, choosebuf);
    strcat(fname, ".dat");
    // printf("%s", fname);
    file = fopen(fname, "r+");
    fgets(graph.name, 50, file);
    fscanf(file, "%d", &V);
    fscanf(file, "%d", &E);
    // printf("%d %d", graph.vertexSize, graph.edgeSize);
    graph.vertexSize = V;
    graph.edgeSize = E;
    fflush(stdin);
    for (i = 0; i < V; i++)
    {
        // fgets(graph.vertices[i].name, 50, file);
        fscanf(file, "%s", graph.vertices[i].name);
        graph.vertices[i].abv = 'A' + i;
    }
    int k = 0;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            fscanf(file, "%d", &w);
            // printf("%d ", w);
            G[i][j] = w;
            if (i > j)
            {
                graph.edge[k].start = i;
                graph.edge[k].end = j;
                graph.edge[k].weight = w;
            }
        }
        // printf("\n");
    }
    // printAdjMatrix(graph);
    fclose(file);
    printf("\nImport graph succeed!\n");
    return graph;
}

void ExportGraph(Graph graph)
{
    struct dirent *de;
    char dname[10];
    DIR *dr = opendir("data");
    FILE *file;
    int countFile = 1;
    if (dr == NULL)
    {
        printf("Could not open data directory");
    }
    while ((de = readdir(dr)) != NULL)
    {
        if (strstr(de->d_name, ".dat"))
        {
            countFile++;
        }
    }
    closedir(dr);
    char fname[50] = "data/";
    char buf[10];
    itoa(countFile, buf, 10);
    strcat(fname, buf);
    strcat(fname, ".dat");
    file = fopen(fname, "a");
    fprintf(file, "%s", graph.name);
    fprintf(file, "%d ", V);
    fprintf(file, "%d\n", E);
    for (i = 0; i < V; i++)
    {
        // fgets(graph.vertices[i].name, 50, file);
        fprintf(file, "%s\n", graph.vertices[i].name);
        graph.vertices[i].abv = 'A' + i;
    }
    int k = 0;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            fprintf(file, "%d ", G[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("\nExport graph succeed!\n");
}

void Menu()
{
    int createChoice;
    Graph graph;
    int validGraph = 0;
    int G[V][V];
    char toImportGraphName[50];
    // TODO: make a simple profile to tree
    while (1)
    {
        // if (validGraph)
        //     printGraphData(graph);
        printf("\n!! --- MST Menu --- !!\n"
               " 1 Create new graph \n"
               " 2 Import existing graph\n"
               " 3 Show graph data\n"
               " 4 Find MST on the graph\n"
               " 5 Export Graph to file\n"
               " 6 Exit\n\n"
               "Choose one (1-6) : ");
        scanf("%d", &createChoice);
        switch (createChoice)
        {
        case 1:
            // Create vertices and edges
            graph = CreateNewGraph();
            validGraph = 1;
            break;
        case 2:
            // Import
            printf("%s", toImportGraphName);
            graph = ImportGraph(toImportGraphName);
            validGraph = 1;
            break;
        case 3:
            // Edit
            if (validGraph)
                printGraphData(graph);
            break;
        case 4:
            // Find mst
            if (!validGraph)
            {
                printf("Error occur or Graph not exits.");
                break;
            }
            primMST(graph);
            break;
        case 5:
            // Export Graph
            if (!validGraph)
            {
                printf("Error occur or Graph not exits.");
                break;
            }
            ExportGraph(graph);
            break;
        case 6:
            // Go back
            return;
            break;
        }
    }
}

// void Introduction()
// {
//     printf("\nA minimum spanning tree (MST) or minimum weight spanning tree is a"
//            "subset of the edges of a connected, edge-weighted (un)directed graph that"
//            "connects all the vertices together, without any cycles and with the minimum"
//            "possible total edge weight. That is, it is a spanning tree whose sum of edge weights"
//            " is as small as possible. More generally, any edge-weighted undirected graph"
//            " (not necessarily connected) has a minimum spanning forest, which is a union of"
//            " the minimum spanning trees for its connected components.\n\n");
// }

// void HowMSTWorks()
// {
//     printf("\n"
//            "How does Prims Algorithm Work? \nThe idea behind Prim’s algorithm is simple, a spanning tree"
//            "means all vertices must be connected. So the two disjoint subsets (discussed above) of "
//            "vertices must be connected to make a Spanning Tree. And they must be connected with the "
//            "minimum weight edge to make it a Minimum Spanning Tree."
//            "\n\n"
//            "Algorithm\n 1) Create a set mstSet that keeps track of vertices already included in MST.\n"
//            " 2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE."
//            "Assign key value as 0 for the first vertex so that it is picked first.\n"
//            " 3) While mstSet doesn’t include all vertices\n"
//            "   a) Pick a vertex u which is not there in mstSet and has minimum key value.\n"
//            "   b) Include u to mstSet.\n"
//            "   c) Update key value of all adjacent vertices of u. \nTo update the key values, iterate through all adjacent vertices. \n\n");
// }

int main()
{
    /* Let us create the following G
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
    int mainChoice;
    // int G[N][N] = {
    //     {0, 2, 0, 6, 0},
    //     {2, 0, 3, 8, 5},
    //     {0, 3, 0, 0, 7},
    //     {6, 8, 0, 0, 9},
    //     {0, 5, 7, 9, 0},
    // };
    printf("############ Minimum Spanning Tree Program ############\n\n"
           ""
           "                #     #  #####  #####   \n"
           "                ##   ##  #        #     \n"
           "                # # # #  #####    #     \n"
           "                #  #  #      #    #     \n"
           "                #     #  #####    #     \n\n"
           " ----------------------------------------------------- \n");
    while (1)
    {
        // printf("\n!!--- Main menu ---!! \n"
        //     //    " 1 Introduction : What is Minimum Spanning Tree ? \n"
        //     //    " 2 How MST works\n"
        //        " 3 MST \n"
        //        " 4 Quit \n\n"
        //        "Choose one (1-4) : "
        //        "");
        // scanf("%d", &mainChoice);
        // switch (mainChoice)
        // {
        // // Introduction
        // case 1:
        //     Introduction();
        //     break;
        // // Create new minimum spanning tree
        // case 2:
        //     HowMSTWorks();
        //     break;
        // // Import exists graph
        // case 3:
            Menu();
        //     break;
        // // Quit
        // case 4:
        //     printf("Bye Bye !!");
        //     return 0;
        //     break;
        // }
    }
    // primMST(G);
    return 0;
}
