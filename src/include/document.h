#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "graph.h"

typedef struct _layout_document
{
    char *document_filepath;
    graph_object_list *graph_list;
} layout_document;

layout_document *layout_document_constructor();
void layout_document_destructor(layout_document*);
void layout_document_read_file(layout_document*, char*);
int layout_document_read_graph(layout_document*, xmlNode*);
void layout_document_dump(layout_document*);

#endif
