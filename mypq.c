#include "mypq.h"
#include <limits.h>
#define PARENT(i)  (i - 1) / 2
#define LEFT_C(i)  2 * i + 1
#define RIGHT_C(i) 2 * i + 2

// private declarations

int roundup2(int n);    // should round up to the lowest power of two that is lower than the given number
void heapfy_up(PQEL *pq, int l, int i);
void heapfy_down(PQEL *pq, int l, int i);
void swapel(PQEL *a, PQEL *b);

// implementation

PQ *pnewque(short type, int size, int compare(void *, void *), void copy(void *, void *), void _free(void *)) {
    PQ *newpq       = malloc(sizeof(PQ));
    newpq->elements = lnewlist(size, _free, compare, copy);
    newpq->length   = 0;
    newpq->que      = NULL;
    newpq->type     = type;
    return newpq;
}

int pinsert(PQ *que, void *k, int value) {
    int l = roundup2(que->length + 1);
    if (l != que->length)
        que->que = realloc(que->que, sizeof(int) * l);
    ltailadd(que->elements, k);
    que->que[que->length].value = value;
    que->que[que->length].ID    = que->length;
    que->length++;
    heapfy_up(que->que, que->length, que->length - 1);
    return que->length - 1;
}

int pupdate(PQ *que, void *k, int value) {
    int n = lfindin(que->elements, k);
    if (n == -1)
        return 0;
    for (int i = 0; i < que->length; i++)
        if(que->que[i].ID == n)
            que->que[i].value = value;
    return 1;
}

int pisin(PQ *que, void *k) {
    return lfindin(que->elements, k);
}

int pvalueof(PQ *que, void *k) {
    int n = lfindin(que->elements, k);
    if (n == -1)
        return 0;
    int r;
    for (int i = 0; i < que->length; i++)
        if(que->que[i].ID == n)
            r = que->que[i].value;
    return r;
}

void pdelete(PQ *que, void *k) {
    int n = lfindin(que->elements, k);
    if(n == -1)
        return;
    ldeleteindex(que->elements, n);
    for (int i = 0; i < que->length;i++) {
        if(que->que[i].ID == n) {
            que->que[i].value = INT_MIN;
            heapfy_down(que->que, que->length, i);
        }
        if(que->que[i].ID > n)
            que->que[i].ID--;
    }
    int l = roundup2(que->length);
    que->length--;
    if(roundup2(que->length) < l)
        que->que = realloc(que->que, sizeof(PQEL) * roundup2(que->length));
    return;
}

void *pextracttop(PQ *que) {
    void *el = lgetindex(que->elements, que->que->ID);
    pdelete(que, el);
    return el;
}

void *ppeektop(PQ *que) {
    void *el = lgetindex(que->elements, que->que->ID);
    return el;
}

int pvalueoftop(PQ *que) {
    return que->que->value;
}

int roundup2(int n) {
    int t = 1;
    while (t < n)
        t = t << 1;
    return t;
}

int plength(PQ *que) {
    return que->length;
}

void heapfy_up(PQEL *pq, int l, int i) {
    if (i == 0)
        return;
    if(pq[i].value > pq[PARENT(i)].value) {
        swapel(&pq[i], &pq[PARENT(i)]);
        heapfy_up(pq, l, PARENT(i));
    }
    return;
}

void heapfy_down(PQEL *pq, int l, int i) {
    if(RIGHT_C(i) < l) {
        if(pq[RIGHT_C(i)].value > pq[i].value && pq[RIGHT_C(i)].value > pq[LEFT_C(i)].value) {
            swapel(&pq[i], &pq[RIGHT_C(i)]);
            heapfy_down(pq, l, RIGHT_C(i));
        }
    }
    if(LEFT_C(i) < l && pq[LEFT_C(i)].value > pq[i].value) {
        swapel(&pq[LEFT_C(i)], &pq[i]);
        heapfy_down(pq, l, LEFT_C(i));
    }
    return;
}

void swapel(PQEL *a, PQEL *b) {
    PQEL tmp;
    tmp.ID = a->ID;
    tmp.value = a->value;
    a->ID     = b->ID;
    a->value  = b->value;
    b->ID     = tmp.ID;
    b->value  = tmp.value;
    return;
}
