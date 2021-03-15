// This is purley ipothetical for now so it will be for now only a collection of prototipes, not sure what I'll get done though if anything

#include "mylist.h"

#ifndef MY_GRAPH_INCLUDE
#define MY_GRAPH_INCLUDE

typedef struct Connection CONNECTION;
typedef struct Vertex VERTEX;

struct Connection {
    int weight;
    union {
        VERTEX *element;
        int to;
    };
    union {
        CONNECTION *next;
        int from;
    };
};

struct Vertex {
    int ID;
    union {
        int connectedcomponent;
        int shortestpath;
    };
    CONNECTION *adj;
    VERTEX *next;
};

typedef struct {
    union {
        int **cmatrix;           // 1
        VERTEX *adjlist;         // 2
        LIST *connectionlist;    // 3
    };
    short type;    // 1: cmatrix, 2: adjlist, 3:connectionlist
    int V;
    int E;
} GRAPH;

GRAPH *gnewgraph(short type);
GRAPH *gminimaltree(GRAPH *graph);
int gconnectedcomponents(GRAPH *qraph);
int gcheckloop(GRAPH *graph);
int gsssp(GRAPH *graph);
int gsslp(GRAPH *graph);
int gaddvertex(GRAPH *graph, int vertex /* -1 for auto*/);
int gaddconnection(GRAPH *graph, int from, int to);

#endif
