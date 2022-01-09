struct Edge{
    int src;
    int dest;
    int w;
    struct Edge *next;
    struct Edge *prev;
} typedef Edge;

struct Node{
    struct Node *next;
    struct Node *prev;
    int id;
    Edge *edges_head;
    int neig;
} typedef Node;

typedef struct Graph {
    int N;
    Node *head;
} Graph;

struct GraphDijkstra
{
    int vertexNum;
    int **edges;
};

int shortestPath(int src,int dest, Graph *gr);
int Dijkstra(struct GraphDijkstra *graph, int src,int dest);
int shortestPathDijkstra(int src,int dest, Graph *gr);
void get_edges(int src_A, struct Graph *gr);
Graph *build_graph(int);
void set_edge(int, int, int , Graph *gr);
Node *add_node(int, Graph *gr);
void delete_node(int, Graph *gr);
int shortsPath(int, int, struct Graph *gr);
void printGraph(struct Graph *gr);
void delete_gr(Graph*gr);
void TSP(int, struct Graph *gr);