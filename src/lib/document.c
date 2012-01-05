#include "document.h"
/**
 * Layout document
 */
layout_document *layout_document_constructor()
{
    layout_document *document = (layout_document*)malloc(sizeof(layout_document));
    document->graph_list = graph_object_list_constructor();
    document->document_filepath = 0;

    return document;
}

void layout_document_destructor(layout_document *document)
{
    if (document == 0) {
        return;
    }

    if (document->document_filepath) {
        free(document->document_filepath);
    }

    if (document->graph_list) {
        graph_object_list_destructor(document->graph_list);
    }

    free(document);
}

void print_element_names(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }

        print_element_names(cur_node->children);
    }
}

int layout_document_read_graph(layout_document *document, xmlNode *element)
{
    xmlNode *root = 0, *graph = 0, *cur = element;

    // find the root node
    for (; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE
            && strcmp(cur->name, "graphml") == 0) {
            root = cur;
            break;
        }
    }

    if (root == 0) {
        printf("Can't find graphml node\n");
        return 0;
    }

    // find the graph node
    cur = root->children;
    for (; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE
            && strcmp(cur->name, "graph") == 0) {
            graph = cur;
            break;
        }
    }

    if (graph == 0) {
        printf("Can't find graph node\n");
        return 0;
    }

    graph_object *graphobject = graph_object_constructor();
    graph_node *graphnode = 0;
    graph_edge *graphedge = 0;

    int graph_node_counter = 0;
    int graph_edge_counter = 0;

    // find the graph node
    cur = graph->children;
    for (; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE
            && strcmp(cur->name, "node") == 0) {

            graphnode = graph_node_constructor();

            if (graph_node_read_data(graphnode, cur, graph_node_counter)) {
                graph_object_append_node(graphobject, graphnode);
            } else {
                graph_node_destructor(graphnode);
            }

            graph_node_counter++;
        } else if (cur->type == XML_ELEMENT_NODE
            && strcmp(cur->name, "edge") == 0) {

            graphedge = graph_edge_constructor();
            if (graph_edge_read_data(graphedge, cur, graph_edge_counter)) {
                graph_object_append_edge(graphobject, graphedge);
            } else {
                graph_edge_destructor(graphedge);
            }

            graph_edge_counter++;
        }
    }

    graph_object_normalize(graphobject);
    graph_object_list_append_graph(document->graph_list, graphobject);

    return 1;
}

void layout_document_read_file(layout_document *document, char *filepath)
{
    xmlDoc  *doc = NULL;
    xmlNode *root_element = NULL;

    document->document_filepath = strdup(filepath);

    /*parse the file and get the DOM */
    doc = xmlReadFile(document->document_filepath, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", document->document_filepath);
    }

    root_element = xmlDocGetRootElement(doc);
    layout_document_read_graph(document, root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void layout_document_dump(layout_document *document)
{
    printf("Source:%s\n", document->document_filepath);

    if (document->graph_list->graph_object_list_head == 0) {
        printf("No graph data available\n");
        return;
    }

    graph_object *graph = document->graph_list->graph_object_list_head;
    graph_object_dump(graph);
}
