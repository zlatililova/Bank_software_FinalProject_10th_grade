#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* create_Iban()
{
    printf("function begins\n");
    srand(time(0));
   char *arr = malloc(23*sizeof(char));

    char alphabet[26] = {  'A', 'B', 'C', 'D', 'E', 'F', 'G',
                            'H', 'I', 'J', 'K', 'L', 'M', 'N',
                            'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                            'V', 'W', 'X', 'Y', 'Z' };
    char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i < 23; i++)
    {
        if(i<2 || (i>3 && i<8)){
           arr[i] = alphabet[rand() % 26];
        }
        else{
            arr[i]  = numbers[rand() % 10];
        }
    }
    arr[22] = '\0';

    return arr;

}


int main(){
    char *ptr; 
    ptr = create_Iban();
    printf("%s",*ptr);
    return 0;

}
