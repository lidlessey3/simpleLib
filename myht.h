#include "mylib.h"
#include <stdlib.h>

// this library will provide a biective hash table, that allows to from an element K to access its value V (assigned progressivilely starting from 0) and also the other way around

#ifndef MY_HT_INCLUDE
#define MY_HT_INCLUDE

// structs

typedef struct {
    int *map;                          // This array will contain the values V assigned to each element its length will be table size
    int tablesize;                     // the size of the map array, or in other the number of possible hashes
    void **revesemap;                  // the reverse map, it contains the element at index V its length will be n_size
    int n_elements;                    // the number of values currentli stored into the hash_table
    int size;                          // the dimension of an element
    int (*compare)(void *, void *);    // will return 0 if same, or true if different
    void (*copy)(void *, void *);      // will copy B into A
    void (*free)(void *);              // will free an elemnt
    int (*customhash)(void *, int, int (*)(int, void *),
                      void *);    // the custom hash function in case it is specified it must recive as arguments the elemnt and the maximum value it can return
} PHT;

// functions

PHT *hnewpht(int size, int compare(void *, void *), void copy(void *, void *), void _free(void *));    // it will return a new PHT elemnt
int haddelemnt(PHT *hashtable, void *t);                                                               // Will add the element to the table and return the value
void *hgetelement(PHT *hashtable, int value);                                                          // will return the element associated with that value NULL if not found
int hgetvalue(PHT *hashtable, void *t);                                                                // will return the value associated with that element -1 if not found
void hdeletevalue(PHT *hashtable, int value);    // removes the value from the table, NOTE: it will also reduce by one all subsequent values!!!!!!
void hdeleteelement(PHT *hashtable, void *t);    // same as above, but from the element associeted
void hsetcustomhash(PHT *hashtable, int hash(void * /*the elemnt to hash*/, int /*max possible hash*/, int (*)(int, void *) /*validate function*/,
                                             void * /*extra args to pass to the validate func*/));    // Will use this function to compute hashes, it is recomanded to set one if
                                                                                                      // using pointers in element return - for errors
void hfree(PHT *hashtable);                                                                           // deletes the entire structure

#endif