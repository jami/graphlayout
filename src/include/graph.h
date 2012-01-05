#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

struct _graph_edge;

typedef struct _graph_node
{
    struct _graph_node *next_node;
    struct _graph_edge **assoc_edge;
    int assoc_edge_count;
    char *name;
} graph_node;

typedef struct _graph_edge
{
    struct _graph_edge *next_edge;
    char *name;
    graph_node *source_node;
    graph_node *target_node;
    char *source;
    char *target;
    int bidirectional;
} graph_edge;

typedef struct _graph_object
{
    char *name;
    struct _graph_object *next_object;
    graph_node *node_list_head;
    graph_node *node_list_tail;
    graph_edge *edge_list_head;
    graph_edge *edge_list_tail;
} graph_object;

typedef struct _graph_object_list
{
    graph_object *graph_object_list_head;
    graph_object *graph_object_list_tail;
} graph_object_list;

graph_node *graph_node_constructor();
void graph_node_destructor(graph_node*);
void graph_node_assoc_append(graph_node*, graph_edge*);
int graph_node_read_data(graph_node*, xmlNode*, int);

graph_edge *graph_edge_constructor();
void graph_edge_destructor(graph_edge*);
int graph_edge_read_data(graph_edge*, xmlNode*, int);

graph_object *graph_object_constructor();
void graph_object_destructor(graph_object*);
void graph_object_dump(graph_object*);
void graph_object_append_node(graph_object*, graph_node*);
void graph_object_append_edge(graph_object*, graph_edge*);
graph_edge *graph_object_find_edge(graph_object*, char*);
graph_node *graph_object_find_node(graph_object*, char*);
void graph_object_normalize(graph_object*);

graph_object_list *graph_object_list_constructor();
void graph_object_list_destructor(graph_object_list*);
void graph_object_list_append_graph(graph_object_list*, graph_object*);

#endif
