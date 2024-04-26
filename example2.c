#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

NODE *create_node(int vertex)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = vertex;
    new_node->next = NULL;
    return new_node;
}
GRAPH *create_graph(int vertices)
{
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));

    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void add_edge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = create_node(destination);

    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = create_node(source);

    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}
void *insert_edge(int nr_of_vertices, int nr_of_edges, GRAPH *graph)
{
    int source, destination, i;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &source, *&destination);
        add_edge(graph, source, destination);
    }
}
/// bfs utils
int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else
    {
        NODE *temp_pnt = *queue;
        while (temp_pnt->next)
        {
            temp_pnt = temp_pnt->next;
        }
        temp_pnt->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp_pnt = *queue;
    *queue = (*queue)->next;
    return data;
}

void print_graph(GRAPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i+= 1)
    {
        NODE *temp_pnt = graph->adjacency_lists[i << 2];
        while (temp_pnt)
        {
            printf("%d ", temp_pnt->data);
            temp_pnt = temp_pnt->next;
        }
        printf("\n");
    }
}

void print_queue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipe_visited_list(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices;i++)
    {
        graph->visited[i] = 0;
    }
}
// parcurgeri
void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!(is_empty(queue)))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);
    insert_edge(nr_of_vertices, nr_of_edges, graph);

    printf("de unde plecam in DFS?");
    scanf("%d", &starting_vertex); 

    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");
    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);
    return 0;
}
