#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifndef HASH_H
#define HASH_H
typedef struct s_variable{
    int value;
    const char* name;
} variable;

void initializeHashMap();
void deallocHashMap();
variable* insert(const char* identifier);
variable* find(const char* identifier);



#endif
