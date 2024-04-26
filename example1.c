#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;

typedef struct Graph
{
    int v;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

typedef struct Stack
{
    int top;
    int stack_capacity;
    int *array;
} STACK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
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

GRAPH *create_graph(int vertex)
{
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->v = vertex;
    graph->adjacency_lists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertex);

    for (int i = 0; i < vertex; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}

STACK *create_stack(int stack_capacity)
{
    STACK *stack = malloc(sizeof(STACK));
    stack->array = malloc(stack_capacity * sizeof(int));
    stack->top = -1;
    stack->stack_capacity = stack_capacity;

    return stack;
}

void push(int pushed_value, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushed_value;
}

void DFS(GRAPH *graph, STACK *stack, int nr_of_vertices)
{
    NODE *adj_list = graph->adjacency_lists[nr_of_vertices];
    NODE *aux = adj_list;
    graph->visited[nr_of_vertices] = 1;
    printf("%d ", nr_of_vertices);
    push(nr_of_vertices, stack);
    while (aux != NULL)
    {
        int connected_vertex = aux->data;
        if (graph->visited[connected_vertex] == 0)
            DFS(graph, stack, connected_vertex);
        aux = aux->next;
    }
}

void insert_edges(GRAPH *graph, int nr_of_edges, int nr_of_vertices)
{
    int source, destination, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

void wipe(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void can_be(GRAPH *graph, int nr_of_vertices, STACK *s1, STACK *s2)
{
    int j,ans;
    int *canb = calloc(5, sizeof(int));
    for (int i = 0; i < nr_of_vertices; i++) 
    {
        DFS(graph, s1, i);
        wipe(graph, nr_of_vertices);
        DFS(graph, s2, j);
        for (int j = 0; j < nr_of_vertices && !ans; j++)
            for (int i = 0; i < nr_of_vertices && !ans; i++)
                if ((s1->array[i] == j) && (s2->array[j] == i))
                    *canb= 1;
    }
}

int main()
{

    int nr_of_vertices, nr_of_edges;

    printf("Cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);

    STACK *s1 = create_stack(2 * nr_of_vertices);
    STACK *s2 = create_stack(2 * nr_of_vertices);

    insert_edges(graph, nr_of_edges, nr_of_vertices);

    can_be(graph, nr_of_vertices, s1, s2);
    return 0;
}