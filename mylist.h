#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef MY_LIST_INCLUDE
#define MY_LIST_INCLUDE

typedef struct Element {
    void *element;
    struct Element *next;
    struct Element *prev;
} ELEMENT;

typedef struct {
    ELEMENT *list;
    int size;                          // the size in bites of every element
    void (*remove)(void *);            // this function should prepare for the free()
    int (*compare)(void *, void *);    // this function should return 0 if same, 1 if their order is correct, -1
                                       // if they should be reversed
    void (*copy)(void *, void *);      // this function should copy the second element into the first
} LIST;

LIST *lnewlist(int size, void remove(void *), int compare(void *, void *), void copy(void *, void *));    // will create a new list
LIST *lcopylist(LIST *src);                                                                               // will return a copy of the given list
int lfindin(LIST *list, void *element);                                                                   // will return the index of the element, or -1 if not found
int lgetlength(LIST *list);                                                                               // will return the length of the list
void lheadadd(LIST *list,
              void *element);    // will add the element at the begging NOTE: it will make a copy of the element
void ltailadd(LIST *list,
              void *element);                // will add the element at the end NOTE: it will make a copy of the element
void lsortadd(LIST *list, void *element);    // will add the element in following the compare function NOTE: it
                                             // will make a copy of the element
void *lpop(LIST *list);                      // will return a copy of the first element and then delete it
void *lgetindex(LIST *list, int n);          // will return a copy of the nth element
void ldeleteindex(LIST *list, int n);        // will delete the nth element
void lreplaceindex(LIST *list, int n,
                   void *element);                   // will replace the nth element with the given one
void laddatpos(LIST *list, int n, void *element);    // will add the element at the nth position
void lfree(LIST *list);                              // will delete the list
void *ldirectreference(LIST *list, int n);           // will return a direct reference to the nth element

// WIP

void lcallonall(LIST *list, void function(void * /*whathever the arguments thing is*/, void * /*the element in the list*/),
                void *arguments);    // Will call the given function on all the elements on the list

#endif
