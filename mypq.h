#include "mylist.h"
#include <stdlib.h>

#ifndef MY_PQ_INCLUDE
#define MY_PQ_INCLUDE

typedef struct {
    int value;
    int ID;
} PQEL;

typedef struct {
    short type;    // can be either 1 or -1 which indicates if it is a max or a min que respectivelly
    unsigned int length;
    PQEL *que;
    LIST *elements;
} PQ;

// declaration of functions

PQ *pnewque(short type, int size, int compare(void *, void *), void copy(void *, void *), void _free(void *));    // Creates a new priority que
int pinsert(PQ *que, void *k, int value);                                                                         // Insert the new element into the que with value
int pupdate(PQ *que, void *k, int value);                                                                         // Updates the value of the elemnt into the que
int pisin(PQ *que, void *k);                                                                                      // returns 1 if the que is present or 0 if not
int pvalueof(PQ *que, void *k);                                                                                   // returns the value associated to the que
void pdelete(PQ *que, void *k);                                                                                   // removes the key from the que
void *pextracttop(PQ *que);                                                                                       // return the key of the first element and then deletes it
void *ppeektop(PQ *que);                                                                                          // same as above, but does not delete
int pvalueoftop(PQ *que);                                                                                         // returns the value of the top elemnt
int plength(PQ *que);                                                                                             // returns the length of the que

#endif