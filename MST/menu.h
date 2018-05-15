#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include "prim.h"

int N, i, j, v;
int V, E;
int G[50][50];


Graph CreateNewGraph()
{
    Graph graph;
    fflush(stdin);
    printf("Enter graph name : ");
    gets(graph.name);
    printf("Graph name = %s \n", graph.name);
    printf("Enter vertices size : ");
    scanf("%d", &V);
    fflush(stdin);
    graph.vertexSize = V;
    for (i = 0; i < graph.vertexSize; i++)
    {
        graph.vertices[i].abv = 'A' + i;
        printf(" %d Enter vertex %c name : ", i + 1, graph.vertices[i].abv);
        gets(graph.vertices[i].name);
    }
    for (i = 0; i < graph.vertexSize; i++)
    {
        printf(" %c <==> %s\n", graph.vertices[i].abv, graph.vertices[i].name);
    }
    printf("Enter edges size : ");
    scanf(" %d", &E);
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
    file = fopen(fname, "r+");
    fgets(graph.name, 50, file);
    fscanf(file, "%d", &V);
    fscanf(file, "%d", &E);
    graph.vertexSize = V;
    graph.edgeSize = E;
    fflush(stdin);
    for (i = 0; i < V; i++)
    {
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
    }
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
    fprintf(file, "%s\n", graph.name);
    fprintf(file, "%d ", V);
    fprintf(file, "%d\n", E);
    for (i = 0; i < V; i++)
    {
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
    while (1)
    {
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
            graph = ImportGraph(toImportGraphName);
            validGraph = 1;
            break;
        case 3:
            // Show
            if (validGraph)
                printGraphData(graph);
            else
                printf("\nPlease create or import graph first !\n");
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