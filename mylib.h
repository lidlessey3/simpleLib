#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef MY_LIB_INCLUDE
#define MY_LIB_INCLUDE

typedef struct {
    int x;
    int y;
} mycouple;

void strtolower(char *str);
void strtoupper(char *str);
void copycouple(void *a, void *b);      // function to copy a couple into another, compatible with mylist ;)
void freecouple(void *p);               // function to free a pointer to a couple, again compatible with mylist
int comparecouple(void *a, void *b);    // will return 0 if same, 1 if different, you guessed it, to be used with mylist
int myhash(void *el, int MAX, int verify(int, void *) /* this functions is used to validate the hash, will return 0 if not ok, 1 if ok*/,
           void *arg /*extra arguments to pass to verify, may be NULL*/);    // will return a hash at most MAX, if a verify function is specified it will use it to check if the
                                                                             // hash is alredy in use and use double hashing to find a new one.
void iswap(int *A, int *B);

#endif
