#include "mylist.h"

LIST *lnewlist(int size, void remove(void *), int compare(void *, void *), void copy(void *, void *)) {
    LIST *newlist    = (LIST *) malloc(sizeof(LIST));
    newlist->list    = NULL;
    newlist->size    = size;
    newlist->remove  = remove;
    newlist->compare = compare;
    newlist->copy    = copy;
    return newlist;
}

LIST *lcopylist(LIST *src) {
    LIST *newlist = lnewlist(src->size, src->remove, src->compare, src->copy);
    int n         = lgetlength(src);
    for (int i = 0; i < n; i++) {
        void *el = lgetindex(src, i);
        ltailadd(newlist, el);
        src->remove(el);
    }
    return newlist;
}

int lfindin(LIST *list, void *element) {
    ELEMENT *cursor = list->list;
    for (int n = 0; cursor != NULL; (cursor = cursor->next) && n++)
        if (list->compare(cursor->element, element) == 0)
            return n;
    return -1;
}

int lgetlength(LIST *list) {
    int l;
    ELEMENT *cursor = list->list;
    for (l = 0; cursor != NULL; l++)
        cursor = cursor->next;
    return l;
}

void lheadadd(LIST *list, void *element) {
    laddatpos(list, 0, element);
}

void ltailadd(LIST *list, void *element) {
    laddatpos(list, lgetlength(list), element);
}

void lsortadd(LIST *list, void *element) {
    ELEMENT *cursor = list->list;
    int n;
    for (n = 0; cursor != NULL && list->compare(cursor->element, element) >= 1; n++)
        cursor = cursor->next;
    laddatpos(list, n, element);
}

void *lpop(LIST *list) {
    ELEMENT *element = list->list;
    if (element == NULL)
        return NULL;
    list->list = element->next;
    if (list->list != NULL)
        list->list->prev = NULL;
    void *result = element->element;
    free(element);
    return result;
}

void *lgetindex(LIST *list, int n) {
    if (n >= lgetlength(list))
        return NULL;
    ELEMENT *cursor = list->list;
    for (int i = 0; i < n; i++)
        cursor = cursor->next;
    void *element = malloc(list->size);
    list->copy(element, cursor->element);
    return element;
}

void ldeleteindex(LIST *list, int n) {
    if (n >= lgetlength(list))
        return;
    ELEMENT **cursor = &list->list;
    for (int i = 0; i < n; i++)
        cursor = &((*cursor)->next);
    list->remove((*cursor)->element);
    ELEMENT *tmp = *cursor;
    *cursor      = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    free(tmp);
    return;
}

void lreplaceindex(LIST *list, int n, void *element) {
    ldeleteindex(list, n);
    laddatpos(list, n, element);
}

void laddatpos(LIST *list, int n, void *element) {
    if (n > lgetlength(list))
        return;
    ELEMENT **cursor = &list->list;
    for (int i = 0; i < n; i++)
        cursor = &((*cursor)->next);
    ELEMENT *tmp       = *cursor;
    *cursor            = (ELEMENT *) malloc(sizeof(ELEMENT));
    (*cursor)->element = malloc(list->size);
    list->copy((*cursor)->element, element);
    (*cursor)->next = tmp;
    if (tmp != NULL)
        tmp->prev = *cursor;
    return;
}

void lfree(LIST *list) {
    int n = lgetlength(list);
    for (int i = 0; i < n; i++) {
        ldeleteindex(list, 0);
    }
    free(list);
}

void *ldirectreference(LIST *list, int n) {
    if (n >= lgetlength(list))
        return NULL;
    ELEMENT *cursor = list->list;
    for (int i = 0; i < n; i++)
        cursor = cursor->next;
    return cursor->element;
}

void lcallonall(LIST *list, void function(void * /*whathever the arguments thing is*/, void * /*the element in the list*/), void *arguments) {
    ELEMENT *cursor = list->list;
    while(cursor != NULL) {
        function(arguments, cursor->element);
        cursor = cursor->next;
    }
    return;
}
