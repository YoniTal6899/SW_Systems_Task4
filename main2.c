#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    struct Graph *gr = NULL;
    char ch;
    int input_num;
    while (scanf("%c", &ch))
    {
        if (ch == '\n')
        {
            break;
        }
        if (ch == 'A')
        {
            if (gr != NULL)
            {
                delete_gr(gr);
                gr = NULL;
            }
            scanf("%d", &input_num); 
            gr = build_graph(input_num);
        }
        else if (ch == 'n') 
        {
            int src_A;
            while (scanf("%d", &src_A))
            {
                    add_node(src_A, gr);
                    get_edges(src_A, gr); // get the edges if any are given
            }
        }
        else if (ch == 'B')
        {
            int num_B;
            scanf("%d", &num_B);
            Node *my_src = add_node(num_B, gr);
            // get and and edges to node
            get_edges(my_src->id, gr);
        }
        else if (ch == 'D')
        {
            int to_remove;
            scanf("%d", &to_remove);
            delete_node(to_remove, gr);
        }
        else if (ch == 'S')
        {
            int src;
            int dest;
            scanf("%d", &src);
            scanf("%d", &dest);
            int ans = shortestPath(src, dest, gr);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if (ch == 'T')
        {
            int k;
            scanf("%d", &k);
            TSP(k, gr);
        }
    }
    delete_gr(gr);
    return 0;
}