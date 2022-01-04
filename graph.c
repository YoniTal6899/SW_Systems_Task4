#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#define MAX __INT_MAX__
int k=0;
int finished=0;
int arr1[100];

node *getNode(pnode *head, int id)
{
    node *p = *head;
    while (p != NULL)
    {
        if (p->node_num == id)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
node *createNode(int id)
{
    node *n = (node *)malloc(sizeof(node));
    n->node_num = id;
    n->edges = NULL;
    n->next = NULL;
    return n;
}

void build_graph_cmd(pnode *head)
{
    pnode *tempN = head;
    pedge *tempE = NULL;
    int Nodes_Num;
    char garbage;
    scanf("%d", &Nodes_Num);
    scanf("%c", &garbage);
    scanf("%c", &garbage);
    int i=0;
    while (i<Nodes_Num)
    {
        node *n = createNode(i);
        *tempN = n;
        tempN = &((*tempN)->next);
        i++;
    }
    i=0;
    while(i<Nodes_Num)
    {
        int id;
        int dest;
        int w;        
        scanf("%d", &id);
        scanf("%c", &garbage);
        node *q = getNode(head, id);
        tempE = &(q->edges);
        while (scanf("%d%d", &dest, &w))
        {
            edge *e = (edge *)malloc(sizeof(edge));
            if (e == NULL)
            {
                printf("Error allocating memory to edge! :(\n");
                return;
            }
            e->weight = w;
            node *p = getNode(head, dest);
            e->endpoint = p;
            *tempE = e;
            tempE = &((*tempE)->next);
        }
        if (i + 1 != Nodes_Num)
        {            
            scanf("%c", &garbage);
        }
        i++;
    }   
}
void insert_node_cmd(pnode *head)
{
    int id;
    int dest;
    int w;
    pnode *tmp = head;
    scanf("%d", &id);
    node *n = getNode(head, id);
    if (n != NULL)
    {
        pedge *tempE = &(n->next->edges);
        pedge t = *tempE;
        while (t)
        {
            *tempE = t->next;
            free(t);
            t = *tempE;
        }        
    }
    else
    {
        n = createNode(id);
        if (*tmp != NULL)
        {
            while ((*tmp)->next)
            {
                tmp = &((*tmp)->next);
            }
        }
        else
        {
            *tmp=n;          
        }
        (*tmp)->next = n;        
    }
    pedge *tempE = &(n->edges);
    while (scanf("%d%d", &dest, &w))
    {
        edge *e = (edge *)malloc(sizeof(edge));
        if (e == NULL)
        {
            return;
        }
        e->weight = w;
        node *p = getNode(head, dest);
        e->endpoint = p;
        *tempE = e;
        tempE = &((*tempE)->next);
    }
}

void delete_node_cmd(pnode *head)
{
    int id;
    scanf("%d", &id);
    node *n = *head;
    char garbage;
    pnode *p = head;
    while (n!=NULL)
    {
        if (n->node_num != id)
        {
            edge *e = n->edges;
            pedge *pe = &(n->edges);
            while (e!=NULL)
            {
                if (e->endpoint->node_num == id)
                {
                    *pe = e->next;
                    free(e);
                    e = *pe;
                }
                else
                {
                    pe = &(e->next);
                    e = e->next;
                }
            }
            p = &(n->next);
            n = n->next;
        }
        else
        {
            *p = n->next;
            free(n);
            scanf("%c", &garbage);
            return;            
        }
    }
    scanf("%c", &garbage);
}
void InitMaxVal(pnode *head)
{
    pnode p = *head;
    while (p)
    {
        p->tag = MAX;
        p = p->next;
    }
}

void Dikstra(pnode *head, int src)
{
    InitMaxVal(head);
    pnode p = getNode(head, src);
    pedge ed_list = p->edges;
    p->tag = 0;
    while (p!=NULL)
    {
        pedge e = p->edges;
        while (e!=NULL)
        {
            int t_w = p->tag + e->weight;
            if (t_w < 0)
            {
                t_w = MAX;
            }
            int d_t = e->endpoint->tag;
            if (t_w < d_t)
            {
                e->endpoint->tag = p->tag + e->weight;
                e->endpoint->parent = p;
            }
            e = e->next;
        }
        if (ed_list != NULL)
        {
            p = ed_list->endpoint;
            ed_list = ed_list->next;
        }
        else
        {
            p = p->next;
        }
    }
}

void shortsPath_cmd(pnode head)
{
    int src;
    int dest;
    scanf("%d%d", &src, &dest);
    Dikstra(&head, src);
    pnode Ndst = getNode(&head, dest);
    if (Ndst->tag != MAX)
    {
       printf("%d ", Ndst->tag);
    }
    else
    {
        printf("-1");        
    }
}
int shortsPath(pnode head, int src, int dest)
{
    Dikstra(&head, src);
    pnode a = getNode(&head, dest);
    if (a->tag != MAX)
    {
        return a->tag;
    }
    return -1;
}


int sum(int* a, int (*b)[6], int size)
{
    int sum = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if ( b[a[i]][a[i+1]]==-1 )
        {
            return MAX;
        }
        sum = sum + b[a[i]][a[i + 1]];
        if (sum < 0)
            return MAX;
    }
    return sum;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void permute(int *a, int (*b)[6], int i, int n)
{
    if (i == (n - 1))
    {
    
        arr1[k] = sum(a, b, n);
        k++;
    }
    else
    {
        for (int j = i; j < n; j++)
        {
            swap((a + i), (a + j));
            permute(a, b, i + 1, n);
            swap((a + i), (a + j));
        }
    }
}
void TSP_cmd(pnode head)
{

    k = 0;
    int num;
    int size;
    scanf("%d", &size);
    int *nodes = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &num);
        nodes[i] = num;
    }
    int matrix[6][6];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = shortsPath(head, nodes[i], nodes[j]);
             
            }
        }
    }
    int min = MAX;
    int to_permute[size];
    for (int i = 0; i < size; i++)
    {
        to_permute[i] = i;
    }
    permute(to_permute, matrix, 0, size);
    for (int i = 0; i < k; i++)
    {
        if (arr1[i] < min)
        {
            min = arr1[i];
        }
    }
 
    if (min==MAX){
       min=-1; 
    }
    printf("%d ", min);
    free(nodes);
    char garbage;
    scanf("%c", &garbage);
}


int main(){
    char a;
    pnode head;
    int flag =0;
    char garbage;
    while (scanf("%c", &a)!=0){

        if (flag)
        {
            scanf("%c", &garbage);
        }
        flag++;
        switch (a)
        {
            case 'A':
                build_graph_cmd(&head);
                break;
            case 'B':
                insert_node_cmd(&head);
                break;
            case 'D':
                delete_node_cmd(&head);
                break;
            case 'S':
                printf("Dijsktra shortest path: ");
                shortsPath_cmd(head); 
                printf(" \n");
                break;
            case 'T':
                printf("TSP shortest path: ");
                TSP_cmd(head); 
                printf(" \n");
                break;      
            default:
                return 0;
                
        } 
    }
    return 0;
}