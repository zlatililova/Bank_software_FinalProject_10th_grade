#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct user_t{

    char username[21];
    int hash_pass;
    unsigned int id;

};

struct account_t{
    
    char iban[41];
    int balance;
    unsigned int id;
};

int hashing (char* password, int size_of_pass){
    int pass_len = strlen(password);
    int sum = 0;

    for(int i = 0; i<pass_len; i++){
        sum += *(password+i);        
    }    
    return sum % size_of_pass;
}