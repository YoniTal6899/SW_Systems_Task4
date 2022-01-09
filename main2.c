#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    struct Graph *g = NULL;
    char a;
    int src;
    int dest;
    int Nodeid;
    int nodes_num;
    int k;
    while (scanf("%c", &a))
    {
        switch (a)
        {
            case '\n':
                break;
        
            case 'A':
                if (g != NULL)
                {
                    delete_gr(g);
                    g = NULL;
                }
                scanf("%d", &nodes_num); 
                g = build_graph(nodes_num);
                break;

            case 'n':
                while (scanf("%d", &Nodeid))
                {
                    add_node(Nodeid, g);
                    get_edges(Nodeid, g); 
                }
                break;
        
            case 'B':
                scanf("%d", &Nodeid);
                Node *n = add_node(Nodeid, g);
                get_edges(Nodeid, g);
                break;

            case 'D':
                scanf("%d", &Nodeid);
                delete_node(Nodeid, g);
                break;
        
            case 'S':
                scanf("%d", &src);
                scanf("%d", &dest);
                int ans = shortestPath(src, dest, g);
                printf("Dijsktra shortest path: %d \n", ans);
     
            case 'T':        
                scanf("%d", &k);
                TSP(k, g);
                break;
        
            default:
                delete_gr(g);
                return 0;
        }
    }
    
}