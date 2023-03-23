#include "hash.h"

variable* variables;
void initializeHashMap(){
    variables = malloc(128 * (sizeof(variable)));
    for(int i = 0; i < 128; i++){
        variables[i].name = "";
        variables[i].value = 0;
    }
}
int hash(const char* identifier){
    int hashValue = 0;
    for(int i = 0; i < strlen(identifier); i++){
        hashValue += identifier[i] * (int)pow(31, i);
    }
    return hashValue;
}

variable* insert(const char* identifier){
    int firstHashVal = hash(identifier);
    for(int i = 0; i < 128; i++){
        if(strcmp(variables[(firstHashVal + i) % 128].name, "" ) == 0){
            variable* var = &variables[(firstHashVal + i) % 128];
            var->name = identifier;
            return var;
        }
    }
    return NULL; // impossible
}
variable* find(const char* identifier){
    int hashVal = hash(identifier);
    for(int i = 0; i < 128; i++){
        if(strcmp(variables[(hashVal + i) % 128].name, identifier) == 0) return &variables[(hashVal + i) % 128];
    }
    return NULL;
}

void deallocHashMap(){
    free(variables);
}
