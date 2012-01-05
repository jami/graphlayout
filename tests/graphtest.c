#include "testframework.h"
#include "graph.h"

void graph_test_edge()
{
    graph_edge *edge = graph_edge_constructor();

    TEST_ASSERT(edge != 0);
    TEST_ASSERT(edge->source == 0);
    TEST_ASSERT(edge->target == 0);
    TEST_ASSERT(edge->bidirectional == 0);
    TEST_ASSERT(edge->next_edge == 0);

    graph_edge_destructor(edge);
}

void graph_test_node()
{
    graph_node *node = graph_node_constructor();

    TEST_ASSERT(node != 0);
    TEST_ASSERT(node->name == 0);
    TEST_ASSERT(node->next_node == 0);

    graph_node_destructor(node);
}

void graph_test_object()
{
    graph_object *object = graph_object_constructor();
    TEST_ASSERT(object != 0);
    TEST_ASSERT(object->edge_list_head == 0);
    TEST_ASSERT(object->edge_list_tail == 0);
    TEST_ASSERT(object->node_list_head == 0);
    TEST_ASSERT(object->node_list_tail == 0);
    TEST_ASSERT(object->name == 0);
    graph_object_destructor(object);
}

void graph_test_object_functions()
{
    graph_object *object = graph_object_constructor();
    TEST_ASSERT(object != 0);

    graph_node *node = graph_node_constructor();
    node->name = strdup("node1");
    graph_object_append_node(object, node);
    TEST_ASSERT(object->node_list_head == node);
    TEST_ASSERT(object->node_list_tail == node);

    graph_node *node2 = graph_node_constructor();
    node2->name = strdup("node2");
    graph_object_append_node(object, node2);
    TEST_ASSERT(object->node_list_head == node);
    TEST_ASSERT(object->node_list_tail == node2);

    graph_edge *edge = graph_edge_constructor();
    edge->name = strdup("edge1");
    graph_object_append_edge(object, edge);
    TEST_ASSERT(object->node_list_head == node);
    TEST_ASSERT(object->node_list_tail == node2);
    TEST_ASSERT(object->edge_list_head == edge);
    TEST_ASSERT(object->edge_list_tail == edge);

    graph_edge *edge2 = graph_edge_constructor();
    edge2->name = strdup("edge2");
    graph_object_append_edge(object, edge2);
    TEST_ASSERT(object->node_list_head == node);
    TEST_ASSERT(object->node_list_tail == node2);
    TEST_ASSERT(object->edge_list_head == edge);
    TEST_ASSERT(object->edge_list_tail == edge2);

    graph_object_destructor(object);
}

void graph_test_object_normalize()
{
    graph_object *object = graph_object_constructor();

    graph_node *node = graph_node_constructor();
    node->name = strdup("node1");
    graph_object_append_node(object, node);

    graph_node *node2 = graph_node_constructor();
    node2->name = strdup("node2");
    graph_object_append_node(object, node2);

    graph_node *node3 = graph_node_constructor();
    node3->name = strdup("node3");
    graph_object_append_node(object, node3);

    graph_edge *edge = graph_edge_constructor();
    edge->name = strdup("edge1");
    edge->source = strdup("node1");
    edge->target = strdup("node3");
    graph_object_append_edge(object, edge);

    graph_edge *edge2 = graph_edge_constructor();
    edge2->name = strdup("edge2");
    edge2->source = strdup("node2");
    edge2->target = strdup("node3");
    graph_object_append_edge(object, edge2);

    graph_edge *edge3 = graph_edge_constructor();
    edge3->name = strdup("edge3");
    edge3->source = strdup("node3");
    edge3->target = strdup("node3");
    graph_object_append_edge(object, edge3);

    graph_object_normalize(object);

    TEST_ASSERT(node->assoc_edge_count == 1);
    TEST_ASSERT(node2->assoc_edge_count == 1);
    TEST_ASSERT(node3->assoc_edge_count == 3);
    // graph_object_dump(object);

    graph_object_destructor(object);
}

void graph_test_object_list()
{
    graph_object_list *list = graph_object_list_constructor();
    TEST_ASSERT(list != 0);
    graph_object *object1 = graph_object_constructor();
    TEST_ASSERT(object1 != 0);
/*
    graph_node *node = graph_node_constructor();
    node->name = strdup("node1");
    graph_object_append_node(object1, node);
*/
    graph_object_list_append_graph(list, object1);
    TEST_ASSERT(list->graph_object_list_head == object1);
    TEST_ASSERT(list->graph_object_list_tail == object1);

    graph_object_list_destructor(list);
}

void graph_test_run()
{
    graph_test_edge();
    graph_test_node();
    graph_test_object();
    graph_test_object_functions();
    graph_test_object_list();
    graph_test_object_normalize();
}
