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