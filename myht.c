#include "myht.h"

// Private declarations

typedef struct {
    PHT *hashtable;
    void *to_lookfor;
} shearch_args;

int validate_new(int hash, PHT *hashtable);
int validate_find(int hash, shearch_args *research);
int hashwrapper_new(PHT *hashtable, void *t);
int hashwrapper_find(PHT *hashtable, void *t);

// Implementation

PHT *hnewpht(int size, int compare(void *, void *), void copy(void *, void *), void _free(void *)) {
    PHT *newthing        = (PHT *) malloc(sizeof(PHT));
    newthing->size       = size;
    newthing->compare    = compare;
    newthing->copy       = copy;
    newthing->free       = _free;
    newthing->customhash = NULL;
    newthing->n_elements = 0;
    newthing->revesemap  = NULL;
    newthing->tablesize  = 1000;
    newthing->map        = (int *) malloc(newthing->tablesize * sizeof(int));
    for (int i = 0; i < newthing->tablesize; i++)
        newthing->map[i] = -1;
    return newthing;
}

int haddelemnt(PHT *hashtable, void *t) {
    hashtable->revesemap                            = (void **) realloc(hashtable->revesemap, ++(hashtable->n_elements) * sizeof(void *));
    hashtable->revesemap[hashtable->n_elements - 1] = malloc(hashtable->size);
    hashtable->copy(hashtable->revesemap[hashtable->n_elements - 1], t);
    int hash             = hashwrapper_new(hashtable, t);
    hashtable->map[hash] = hashtable->n_elements - 1;
    return hashtable->n_elements - 1;
}

void *hgetelement(PHT *hashtable, int value) {
    if (value >= hashtable->n_elements)
        return NULL;
    void *tmp = malloc(hashtable->size);
    hashtable->copy(tmp, hashtable->revesemap[value]);
    return tmp;
}

int hgetvalue(PHT *hashtable, void *t) {
    int hash = hashwrapper_find(hashtable, t);
    if (hash >= 0)
        return hashtable->map[hash];
    else
        return -1;
}

void hdeletevalue(PHT *hashtable, int value) {
    if (value < hashtable->n_elements && value > -1) {
        free(hashtable->revesemap[value]);
        for (int i = value + 1; i < hashtable->n_elements; i++) {
            hashtable->revesemap[i - 1] = hashtable->revesemap[i];
            int hash                    = hashwrapper_find(hashtable, hashtable->revesemap[i]);
            hashtable->map[hash]--;
        }
    }
    return;
}

void hdeleteelement(PHT *hashtable, void *t) {
    hdeletevalue(hashtable, hgetvalue(hashtable, t));
    return;
}

void hsetcustomhash(PHT *hashtable, int hash(void *, int, int (*)(int, void *), void *)) {
    hashtable->customhash = hash;
}

void hfree(PHT *hashtable) {
    for (int i = 0; i < hashtable->n_elements; i++)
        free(hashtable->revesemap[i]);
    free(hashtable->revesemap);
    free(hashtable->map);
    free(hashtable);
    return;
}

int validate_new(int hash, PHT *hashtable) {
    if(hashtable->map[hash] < 0)
        return 1;
    else
        return 0;
}

int validate_find(int hash, shearch_args *research) {
    if(research->hashtable->map[hash] == -1)
        return 1;
    else if(research->hashtable->compare(research->hashtable->revesemap[research->hashtable->map[hash]], research->to_lookfor) == 0)
        return 1;
    else
        return 0;
}

int hashwrapper_new(PHT *hashtable, void *t) {
    int (*hash)(void *, int, int (*)(int, void *), void *);
    if(hashtable->customhash == NULL)
        hash = myhash;
    else
        hash = hashtable->customhash;
    return hash(t, hashtable->tablesize, (int (*)(int, void *))validate_new, hashtable);
}

int hashwrapper_find(PHT *hashtable, void *t) {
    int (*hash)(void *, int, int (*)(int, void *), void *);
    if(hashtable->customhash == NULL)
        hash = myhash;
    else
        hash = hashtable->customhash;
    shearch_args y;
    y.hashtable = hashtable;
    y.to_lookfor = t;
    return hash(t, hashtable->tablesize, (int (*)(int, void *)) validate_find, &y);
}