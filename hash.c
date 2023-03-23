int values[128];
char* names[128];
unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int setValue(char *name, int value)
{
    int index = hash(*name) % 128;
    while(*names[index] != *name){
        index++;
    }
    values[index] = value;
    names[index] = *name;
    return value;
}
int getValue(char *name)
{
    int index = hash(*name) % 128;
    while(names[index] != *name){
        index++;
    }
    return values[index];
}

