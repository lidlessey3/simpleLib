#include "mylib.h"

void strtolower(char *str) {
    for (; *str != '\0'; str++)
        *str = tolower(*str);
}

void strtoupper(char *str) {
    for (; *str != '\0'; str++)
        *str = toupper(*str);
}

void copycouple(void *a, void *b) {
	mycouple *A, *B;
	A = (mycouple*)a;
	B = (mycouple*)b;
	A->x = B->x;
	A->y = B->y;
	return;
}

void freecouple(void *a) {
	free(a);
	return;
}

int comparecouple(void *a, void *b) {
	mycouple *A, *B;
	A = (mycouple*)a;
	B = (mycouple*)b;
	if(A->x == B->x && A->y == B->y)
		return 0;
	else
		return 1;
}

int myhash(void *el, int MAX, int verify(int, void *), void *args) {
    int *_el = el;
    int hash = *_el % MAX;
	if(verify != NULL) {
        int i = 1;
        while (!verify(hash, args)) {
            hash = (*_el % MAX + (i++) * (*_el % 97 + 1)) % MAX;
			if(i > MAX)
                return MAX + 1;
        }
    }
    return hash;
}

void iswap(int *A, int *B) {
    int tmp = *A;
    *A      = *B;
    *B      = tmp;
    return;
}
