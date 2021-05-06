#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define INF INT_MAX

typedef struct queueNode
{
    vertex v;
    struct queueNode *next;
} queueNode;

typedef struct queue
{
    queueNode *front;
    queueNode *rear;
} queue;

queue *initqueue()
{
    queue *q;
    q = (queue *)malloc(sizeof(struct queue));
    q->front = (queueNode *)malloc(sizeof(struct queueNode));
    q->rear = (queueNode *)malloc(sizeof(struct queueNode));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

queue *enqueue(queue *q, vertex x)
{
    queueNode *temp = (queueNode *)malloc(sizeof(struct queueNode));

    temp->v = x;
    temp->next = NULL;

    if (q->front == NULL)
    {
        q->front = temp;
        q->rear = temp;
    }

    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }

    return q;
}

int dequeue(queue *q)
{
    int x = q->front->v.vertexId;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return x;
}

void getFastestPath(struct Graph *G, vertex src, vertex dest)
{
    queue *q = initqueue();
    enqueue(q, src);

    int cost[G->numVertices];

    for (int i = 0; i < G->numVertices; i++)
    {
        cost[i] = INF;
    }

    cost[src.vertexId] = 0;

    int visited[G->numVertices];
    for (int i = 0; i < G->numVertices; i++)
    {
        visited[i] = 0;
    }

    visited[src.vertexId] = 1;

    printf("Initialisation Done");

    while (q->front != NULL)
    {
        int x = dequeue(q);
        visited[x] = 1;
        printf("x = %d",x);

        struct ListNode *crawl = G->adjacencyList[x];
        while(crawl!=NULL)
        {
             printf("%d ",crawl->dest.vertexId);
             crawl=crawl->next;
        }
        printf("\n");

        struct ListNode *temp = G->adjacencyList[x];
        int i = 0;

        while (temp != NULL)
        {   
            printf("In the loop\n");

            if ((x != temp->dest.vertexId) && (cost[temp->dest.vertexId] >= (cost[x] + temp->SD.weight)))
            {   
                printf("In the if block\n");
                cost[temp->dest.vertexId] = cost[x] + temp->SD.weight;
                //G->path[temp->SD.weight]->next = G->path[x];
                G->path[temp->dest.vertexId]->next = G->path[x];
            }
            if (visited[temp->SD.weight] == 0)
            {
                visited[temp->dest.vertexId] = 1;
                enqueue(q, temp->dest);
            }

            temp = temp->next;
        }
    }

    for(int i=0;i<G->numVertices;i++)
    {
        struct ListNode* temp=G->path[i];
        printf("%d ",temp->dest.vertexId);
    }

    printf("Done");

    struct ListNode *tempi = G->path[dest.vertexId];  //tempi=NULL

    printf("\nthe shortest path between '%s' and '%s' in map is :", src.vertexName, dest.vertexName);

    while (tempi != NULL)
    {
        printf("%s", tempi->dest.vertexName);
        tempi = tempi->next;
        if (tempi != NULL)
            printf("->");
    }
    printf("\n\n");
}

struct Graph *CreateGraph(int iNumber_of_vertices)
{
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    assert(G != NULL);

    G->numVertices = iNumber_of_vertices;

    //AdjacencyList is the array of pointers to listnodes

    G->adjacencyList = (ListNode **)malloc(sizeof(ListNode *) * iNumber_of_vertices);

    G->path = (ListNode **)malloc(sizeof(ListNode *) * iNumber_of_vertices);

    assert(G->adjacencyList != NULL);

    for (int i = 0; i < iNumber_of_vertices; i++)
    {
        //G->adjacencyList[i] = (struct ListNode *)malloc(sizeof(struct ListNode *));
        G->adjacencyList[i] = NULL;
        G->path[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        G->path[i]->dest.vertexId = i;
        G->path[i]->next = NULL;
        //G->path[i]=NULL;
    }

    return G;
}

void AddStreet(struct Graph *G, vertex u, vertex v, struct StreetData SD)
{
    ListNode *temp;
    temp = G->adjacencyList[u.vertexId];
    int found = 0;
    vertex w;

    while (temp != NULL)
    {
        w = temp->dest;

        if (v.vertexId == w.vertexId)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        temp = G->adjacencyList[u.vertexId];
        ListNode *New = (ListNode *)malloc(sizeof(struct ListNode));
        assert(New != NULL);
        New->dest = v;
        New->SD = SD;
        //Add at beginning
        New->next = temp;
        G->adjacencyList[u.vertexId] = New;
    }

    ListNode *tempi;
    tempi = G->adjacencyList[v.vertexId];
    int foundi = 0;
    vertex wi;

    while (tempi != NULL)
    {
        wi = tempi->dest;
        if (u.vertexId == wi.vertexId)
        {
            foundi = 1;
            break;
        }
        tempi = tempi->next;
    }

    if (!foundi)
    {
        tempi = G->adjacencyList[v.vertexId];
        ListNode *New = (ListNode *)malloc(sizeof(struct ListNode));
        assert(New != NULL);
        New->dest = u;
        New->SD = SD;
        //Add at beginning
        New->next = tempi;
        G->adjacencyList[v.vertexId] = New;
    }

    //printf("%d",G->adjacencylist[u.vertexId])
    return;
}
/*
8 15
a b 1 1 1 1 1
a c 1 1 1 1 1
a d 1 1 1 1 1
b d 1 1 1 1 1
b e 1 1 1 1 1
c g 1 1 1 1 1
c d 1 1 1 1 1
c h 1 1 1 1 1
d e 1 1 1 1 1
d g 1 1 1 1 1
e g 1 1 1 1 1
e f 1 1 1 1 1
f h 1 1 1 1 1
f g 1 1 1 1 1
g h 1 1 1 1 1
*/
