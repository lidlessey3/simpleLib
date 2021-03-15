#include "mybst.h"

// private functions declaration, for internal use only
int r_itempresent(NODE *r, void *item, int compare(void *, void *), int depth);
NODE **r_getnode(NODE **r, void *item, int compare(void *, void *));// will return a pointer to the pointer
                                                                    // pointing to the item, or to NULL
NODE **getmaxnode(NODE **r);                                        // get the maximum node
NODE **getminnode(NODE **r);                                        // get the minimum node
void r_armageddon(NODE *r, void _free(void *));                     // recursively delete the node and its childs
void r_copy(NODE *dest, NODE *src, void copy(void *, void *));      // recursively copy the node and its children
void r_headinsert(NODE **r, void *item, int compare(void *, void *),
                  void copy(void *, void *));                       // recursively add the item as the new head
int r_getlevel(NODE *r, void *item, int compare(void *, void *));   // searches for item and returns its level

// Implementation
TREE *tnewtree(int size, void _free(void *), void copy(void *, void *), int compare(void *, void *)) {
    TREE *new    = malloc(sizeof(TREE));
    new->size    = size;
    new->free    = _free;
    new->copy    = copy;
    new->compare = compare;
    new->head    = NULL;
    return new;
}

TREE *tcopytree(TREE *in) {
    TREE *out    = malloc(sizeof(TREE));
    out->size    = in->size;
    out->compare = in->compare;
    out->copy    = in->copy;
    out->free    = in->free;
    out->head    = malloc(out->size);
    r_copy(out->head, in->head, in->copy);
    return out;
}

int titempresent(TREE *tree, void *item) {
    return r_itempresent(tree->head, item, tree->compare, 1);
}

void *tgetdirectreference(TREE *tree, void *item) {
    NODE *thing = *(r_getnode(&tree->head, item, tree->compare));
    return thing->element;
}

void tdeletenode(TREE *tree, void *item) {
    NODE **victim = r_getnode(&tree->head, item, tree->compare);
    if (*victim != NULL) {
        if ((*victim)->l == NULL && (*victim)->r == NULL) {// if both branches are empty, just delete it
            tree->free((*victim)->element);
            free(*victim);
            *victim = NULL;
        } else if ((*victim)->l == NULL && (*victim)->r != NULL) {// if one of them isn't just substitute
            NODE *tmp = *victim;                                  // the deleted node with it
            *victim   = tmp->r;
            tree->free(tmp->element);
            free(tmp);
        } else if ((*victim)->l != NULL && (*victim)->r == NULL) {
            NODE *tmp = *victim;
            *victim   = tmp->l;
            tree->free(tmp->element);
            free(tmp);
        } else {                                          // if neither is then I get the maximum node
            NODE **max_left = getmaxnode(&((*victim)->l));// on the left branch and put it in place
            NODE *tmp       = *max_left;                  // of the deleted node
            *max_left       = tmp->l;
            tmp->l          = (*victim)->l;
            tmp->r          = (*victim)->r;
            tree->free((*victim)->element);
            free(*victim);
            *victim = tmp;
        }
    }
    return;
}

void tleafadd(TREE *tree, void *item) {
    NODE **tmp = r_getnode(&tree->head, item, tree->compare);
    if (*tmp != NULL)
        return;
    NODE *new    = malloc(sizeof(NODE));
    new->l       = NULL;
    new->r       = NULL;
    new->counter = 0;
    new->element = malloc(tree->size);
    tree->copy(new->element, item);
    *tmp = new;
    return;
}

void theadadd(TREE *tree, void *item) {
    r_headinsert(&tree->head, item, tree->compare, tree->copy);
    return;
}

void tfree(TREE *tree) {
    r_armageddon(tree->head, tree->free);
    free(tree);
    return;
}

int r_itempresent(NODE *r, void *item, int compare(void *, void *), int depth) {
    if (r == NULL)
        return 0;
    int status = compare(r->element, item);
    switch (status) {
    case 0:
        return depth;
        break;
    case 1:
        return r_itempresent(r->r, item, compare, depth + 1);
        break;
    case -1:
        return r_itempresent(r->l, item, compare, depth + 1);
        break;
    }
}

NODE **r_getnode(NODE **r, void *item, int compare(void *, void *)) {
    if (*r == NULL || !compare((*r)->element, item))
        return r;
    NODE **tmp;
    switch (compare((*r)->element, item)) {
    case 1:
        tmp = &((*r)->r);
        break;
    case -1:
        tmp = &((*r)->l);
        break;
    }
    return r_getnode(tmp, item, compare);
}

NODE **getmaxnode(NODE **r) {
    for (; (*r)->r != NULL; r = &((*r)->r))
        ;
    return r;
}

NODE **getminbode(NODE **r) {
    for (; (*r)->l != NULL; r = &((*r)->l))
        ;
    return r;
}

void r_armageddon(NODE *r, void _free(void *)) {
    if (r == NULL)
        return;
    r_armageddon(r->l, _free);
    r_armageddon(r->r, _free);
    _free(r->element);
    free(r);
    return;
}

void r_copy(NODE *dest, NODE *src, void copy(void *, void *)) {
    copy(dest->element, src->element);
    dest->counter = src->counter;
    if (src->l != NULL)
        r_copy(dest->l, src->l, copy);
    else
        dest->l = NULL;
    if (src->r != NULL)
        r_copy(dest->r, src->r, copy);
    else
        dest->r = NULL;
    return;
}

void r_headinsert(NODE **r, void *item, int compare(void *, void *), void copy(void *, void *)) {
    if (*r == NULL) {
        *r = malloc(sizeof(NODE));
        copy((*r)->element, item);
        (*r)->l = NULL;
        (*r)->r = NULL;                 //io prego sta cosa funzioni perchè non ne ho idea :)
        return;
    }
    NODE *tmp;
    switch (compare((*r)->element, item)) {
    case 1:
        r_headinsert(&(*r)->r, item, compare, copy);
        tmp = (*r)->r;
        (*r)->r = tmp->l;
        tmp->l  = *r;
        break;
    case -1:
        r_headinsert(&(*r)->l, item, compare, copy);
        tmp = (*r)->l;
        (*r)->l = tmp->r;
        tmp->r  = *r;
        break;
    }
    *r = tmp;
}

int tgetlevel(TREE *tree, void *item) {
	return r_getlevel(tree->head, item, tree->compare);
}

int r_getlevel(NODE *r, void *item, int compare(void *,void *)) {
	if(r == NULL)
		return -1;
	else if(compare(item, r->element) == 0)
		return 0;
	int n = -1;
	if(compare(item, r->element) == 1)
		n = r_getlevel(r->l, item, compare);
	else
		n = r_getlevel(r->r, item, compare);
	if(n >= 0)
		n++;
	return n;
}
