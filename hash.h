#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifndef HASH_H
#define HASH_H
#ifndef int_64
#define int_64 long long int
#endif
typedef struct s_variable{
    int_64 value;
    const char* name;
} variable;

void initializeHashMap();
void deallocHashMap();
variable* insert(const char* identifier);
variable* find(const char* identifier);



#endif
