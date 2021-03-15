#include <stdlib.h>

#ifndef MY_BST_INCLUDE
#define MY_BST_INCLUDE

typedef struct node {
    void *element;
    struct node *l;
    struct node *r;
    int counter;
} NODE;

typedef struct {
    int size;
    NODE *head;
    void (*free)(void *);             //will free the element
    void (*copy)(void *, void *);     //will copy the second element into the first
    int (*compare)(void *, void *);   //will return 0 if same, 1 if B goes to right of A, -1 if otherwise
} TREE;

TREE *tnewtree(int size, void free(void *), void copy(void *, void *),
               int compare(void *, void *));// will create a new binary search tree
TREE *tcopytree(TREE *in);                  // will make a copy of the give tree
int titempresent(TREE *tree, void *item);   // will return the depth of the item(considering the root as 1) if found, 0 otherwise
void *
tgetdirectreference(TREE *tree,
                    void *item);// will return a direct reference to element in the tree or NULL if not found
void tdeletenode(TREE *tree, void *item);// will delete the give item if found
/*IMPORTANT: if the given item is already present, no changes will be made and the function will simply return*/
void tleafadd(TREE *tree, void *item);// will add the item as a new leaf, a copy will be made, so feel free to
                                      // delete the element given
void theadadd(TREE *tree, void *item);// will add the item as the new head, again a copy will be made
void tfree(TREE *tree);               // will free the entire tree
int tgetlevel(TREE *tree, void *item); // will return the level of the item, -1 if not fount

#endif
