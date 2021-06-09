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

void register_user (void){
    struct user_t new_user;
    char password[11];

    printf("Enter a user name between 5 and 20 characters:\n");
    fgets(new_user.username, 20, stdin);

    while(strlen(new_user.username)<6){
         printf("Invalid data. Enter a user name between 5 and 20 characters:\n");
        fgets(new_user.username, 20, stdin);
    }

    printf("Enter a password between 6 and 10 characters:\n");
    fgets(password, 10, stdin);
    while(strlen(password)<7){
         printf("Invalid data. Enter a password between 6 and 10 characters:\n");
        fgets(password, 10, stdin);
    }

    new_user.hash_pass = hashing(password);


}
void return_last_id(int i){
    FILE *fptr;
    int last_id;

   if ((fptr = fopen("C:\\Users\\user\\Desktop\\text.txt","r+")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   // Moves the cursor to the end of the file
   fseek(fptr, -sizeof(int), SEEK_END);
    printf("last id = %d\n",last_id);

      fread(&last_id, sizeof(int), 1, fptr);
      //printf("otvorih se\n");
      printf("n1: %d\n", last_id);

      fclose(fptr);



}

int hashing (char password[]){
    int pass_len = strlen(password);
    printf("trlen = %d\n",pass_len);
    int sum = 0;

    for(int i = 0; i<pass_len-1; i++){
        sum += password[i];
    }
    return sum ;
}

int main(){

    register_user();
    return 0;
}