#include "mygraph.h"
#include <stdlib.h>

GRAPH *gnewgraph(short type) {
    GRAPH *newgraph          = malloc(sizeof(GRAPH));
    newgraph->E              = 0;
    newgraph->V              = 0;
    newgraph->connectionlist = NULL;
    newgraph->type           = type;
    return newgraph;
}

GRAPH *gminimaltree(GRAPH *graph);
int gconnectedcomponents(GRAPH *qraph);
int gcheckloop(GRAPH *graph);
int gsssp(GRAPH *graph);
int gsslp(GRAPH *graph);
int gaddvertex(GRAPH *graph, int vertex /* -1 for auto it will be forced to auto in case of type 1*/) {
    switch (graph->type) {
    case 1:
        graph->cmatrix = realloc(graph->cmatrix, sizeof(int *) * (graph->V + 1));
        for (int i = 0; i < graph->V; i++)
            graph->cmatrix[i] = realloc(graph->cmatrix[i], sizeof(int) * (graph->V + 1));
        graph->cmatrix = malloc(sizeof(int) * ++(graph->V));
        break;
    case 2: {
        VERTEX **cursor = &graph->adjlist;
        while (*cursor != NULL)
            cursor = &((*cursor)->next);
        *cursor                       = malloc(sizeof(VERTEX));
        (*cursor)->adj                = NULL;
        (*cursor)->connectedcomponent = -1;
        (*cursor)->next               = NULL;
        (*cursor)->shortestpath       = -1;
        if (vertex == -1)
            (*cursor)->ID = graph->V;
        else
            (*cursor)->ID = vertex;
        graph->V++;
    } break;
    case 3:
        // to do :)
        break;
    }
}

int gaddconnection(GRAPH *graph, int from, int to);
