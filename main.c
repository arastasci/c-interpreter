#include <stdio.h>
#include <stdbool.h>
int main(){
    //printf("Hello, world!\n");
    while(1){
        char* initialInput[256];
        scanf("%s", initialInput);
        char* input[256];
        int j = 0;
        // get rid of whitespaces
        for(int i = 0; i < 256; i++){
            if(initialInput[i] != ' '){
                input[j] = initialInput[i];
                j++;
            }
        }
        // null terminator must be j?

        // parse input
        

        // produce output
        
        


    }
    return 0;
}
