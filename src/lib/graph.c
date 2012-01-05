#include "graph.h"

graph_node *graph_node_constructor()
{
    graph_node *node       = (graph_node*)malloc(sizeof(graph_node));
    node->name             = 0;
    node->next_node        = 0;
    node->assoc_edge       = 0;
    node->assoc_edge_count = 0;
    return node;
}

void graph_node_destructor(graph_node *node)
{
    if (node->name) {
        free(node->name);
    }

    if (node->assoc_edge) {
        free(node->assoc_edge);
    }

    free(node);
}

graph_edge *graph_edge_constructor()
{
    graph_edge *edge    = (graph_edge*)malloc(sizeof(graph_edge));
    edge->name          = 0;
    edge->source        = 0;
    edge->target        = 0;
    edge->bidirectional = 0;
    edge->next_edge     = 0;
    edge->source_node   = 0;
    edge->target_node   = 0;
    return edge;
}

void graph_edge_destructor(graph_edge *edge)
{
    if (edge->name) {
        free(edge->name);
    }

    if (edge->source) {
        free(edge->source);
    }

    if (edge->target) {
        free(edge->target);
    }

    free(edge);
}

graph_object *graph_object_constructor()
{
    graph_object *object = (graph_object*)malloc(sizeof(graph_object));
    object->next_object    = 0;
    object->edge_list_head = 0;
    object->edge_list_tail = 0;
    object->node_list_head = 0;
    object->node_list_tail = 0;
    object->name           = 0;

    return object;
}

void graph_object_destructor(graph_object *object)
{
    graph_edge *edge, *tmp_edge;
    graph_node *node, *tmp_node;

    if (object->edge_list_head) {
        edge = object->edge_list_head;
        while (edge) {
            tmp_edge = edge->next_edge;
            graph_edge_destructor(edge);
            edge = tmp_edge;
        }
    }

    if (object->node_list_head) {
        node = object->node_list_head;
        while (node) {
            tmp_node = node->next_node;
            graph_node_destructor(node);
            node = tmp_node;
        }
    }

    if (object->name) {
        free(object->name);
    }

    free(object);
}

void graph_object_append_node(graph_object *object, graph_node *node)
{
    if (object->node_list_head) {
        object->node_list_tail->next_node = node;
        object->node_list_tail = node;
    } else {
        object->node_list_head = node;
        object->node_list_tail = node;
    }
}

void graph_object_append_edge(graph_object *object, graph_edge *edge)
{
    if (object->edge_list_head) {
        object->edge_list_tail->next_edge = edge;
        object->edge_list_tail = edge;
    } else {
        object->edge_list_head = edge;
        object->edge_list_tail = edge;
        edge->next_edge = 0;
    }
}

void graph_node_assoc_append(graph_node *node, graph_edge *edge)
{
    if (node->assoc_edge_count == 0) {
        node->assoc_edge = (graph_edge**)malloc(sizeof(graph_edge*));
    } else {
        node->assoc_edge = (graph_edge**)realloc(node->assoc_edge, (node->assoc_edge_count + 1) * sizeof(graph_edge*));
    }

    if (node->assoc_edge_count > 1
        && node->assoc_edge[node->assoc_edge_count - 1] == edge) {
        return;
    }

    node->assoc_edge[node->assoc_edge_count] = edge;
    node->assoc_edge_count++;
}

void graph_object_normalize(graph_object *object)
{
    graph_edge *edge;
    graph_node *node;

    if (object->edge_list_head) {
        edge = object->edge_list_head;
        while (edge) {
            node = object->node_list_head;
            while (node) {
                // find associations
                if (node->name) {
                    if (strcmp(node->name, edge->source) == 0) {
                        edge->source_node = node;
                        graph_node_assoc_append(node, edge);
                    }
                    if (strcmp(node->name, edge->target) == 0) {
                        edge->target_node = node;
                        graph_node_assoc_append(node, edge);
                    }
                }

                node = node->next_node;
            }
            edge = edge->next_edge;
        }
    }
}

void graph_object_dump(graph_object *graph)
{
    graph_node *node;
    graph_edge *edge;
    int counter;
    int assoc_num;

    while (graph) {
        printf("Graph dump ---------\n");
        printf("Node dump:\n");
        node = graph->node_list_head;
        counter = 1;

        while (node) {
            assoc_num = node->assoc_edge_count;
            printf("Node(%d) name:%s assoc:%d\n", counter, node->name, assoc_num);
            counter++;
            node = node->next_node;
        }

        printf("Edge dump:\n");
        edge = graph->edge_list_head;
        counter = 1;

        while (edge) {
            printf(
                "Edge(%d) id:%s assoc: %s => %s\n",
                counter,
                edge->name,
                edge->source_node ? edge->source_node->name : "undef source",
                edge->target_node ? edge->target_node->name : "undef target"
            );
            counter++;
            edge = edge->next_edge;
        }

        printf("-------------------\n");
        graph = graph->next_object;
    }
}

graph_edge *graph_object_find_edge(graph_object *object, char *name)
{
    graph_edge *edge = object->edge_list_head;
    while (edge) {
        if (edge->name
            && strcmp(edge->name, name)) {
            return edge;
        }
        edge = edge->next_edge;
    }

    return 0;
}

graph_node *graph_object_find_node(graph_object *object, char *name)
{
    graph_node *node = object->node_list_head;
    while (node) {
        if (node->name
            && strcmp(node->name, name)) {
            return node;
        }
        node = node->next_node;
    }

    return 0;
}

graph_object_list *graph_object_list_constructor()
{
    graph_object_list *list = (graph_object_list*)malloc(sizeof(graph_object_list));
    list->graph_object_list_head = 0;
    list->graph_object_list_tail = 0;
    return list;
}

void graph_object_list_destructor(graph_object_list *list)
{
    graph_object *object, *tmp_object;

    if (list->graph_object_list_head) {
        object = list->graph_object_list_head;
        while (object) {
            tmp_object = object->next_object;
            graph_object_destructor(object);
            object = tmp_object;
        }
    }

    free(list);
}

void graph_object_list_append_graph(graph_object_list *list, graph_object *object)
{
    if (list->graph_object_list_head) {
        list->graph_object_list_tail->next_object = object;
        list->graph_object_list_tail = object;
    } else {
        object->next_object = 0;
        list->graph_object_list_head = object;
        list->graph_object_list_tail = object;
    }
}

int graph_node_read_data(graph_node *g_node, xmlNode *x_node, int index)
{
    xmlChar *id = xmlGetProp(x_node, "id");
    if (!id) {
        int len = snprintf(NULL, 0, "node%d", index);
        g_node->name = malloc((len + 1) * sizeof(char));
        snprintf(g_node->name, len + 1, "node%d\0", index);
    } else {
        g_node->name = strdup(id);
        xmlFree(id);
    }

    return 1;
}

int graph_edge_read_data(graph_edge *g_edge, xmlNode *x_node, int index)
{
    char buffer[200];
    xmlChar *source = xmlGetProp(x_node, "source");

    if (!source) {
        return 0;
    }

    xmlChar *target = xmlGetProp(x_node, "target");

    if (!target) {
        xmlFree(source);
        return 0;
    }

    g_edge->source = strdup(source);
    g_edge->target = strdup(target);
    xmlFree(source);
    xmlFree(target);

    xmlChar *id = xmlGetProp(x_node, "id");
    if (id) {
        g_edge->name = strdup(id);
        xmlFree(id);
    } else {
        int len = snprintf(NULL, 0, "edge%d", index);
        g_edge->name = malloc((len + 1) * sizeof(char));
        snprintf(g_edge->name, len + 1, "edge%d\0", index);
    }

    return 1;
}
