#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct user_t{

    char username[11];
    int hash_pass;
    unsigned int id;

};

struct account_t{

    char iban[41];
    int balance;
    unsigned int id;
};

int hashing (char password[]){
    int pass_len = strlen(password);
    int sum = 0;

    for(int i = 0; i<pass_len-1; i++){
        sum += password[i];
    }
    return sum;
}

int validate(char name[]){
int l = strlen(name);
int flag = 1;
    //check length is 0 or more than 30
    if (l < 6 || l > 11)
        return 0;

    for (int i = 0; name[i]!='\0'; i++)
    {
        char s = name[i];

        if (s>='a'&&s<='z'){
            flag = 1;
        }
        else if(s>='0'&& s<='9'){
            flag = 1;
        }
        else if(s == '\n'){
            flag = 1;
        }
        else{
          return 0;
        }
    }
    return flag;
}

int return_last_id(){
    FILE *fptr;
    int last_id;
    char str[50];
    char *ptr;

   if ((fptr = fopen("C:\\Users\\user\\Desktop\\text.txt","a+")) == NULL){
       printf("Error! opening file");
       exit(1);
   }
    while (!feof(fptr)){
        fgets(str, sizeof(str), fptr);
    }
    last_id = (int)strtol(str, &ptr, 10);
    fclose(fptr);

    return last_id;
}

struct user_t register_user(void){
    struct user_t new_user;
    char password[11];
    char name[11];
    int is_valid = 0;

    printf("Enter a user name between 5 and 10 characters, use only letters and numbers:\n");
    fgets(name, 10, stdin);
    is_valid = validate(name);

    while(is_valid!=1){
        printf("Invalid data. Enter a user name between 5 and 20 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);
        is_valid = validate(name);
    }

    printf("Enter a password between 5 and 10 characters, use only letters and numbers:\n");
    fgets(password, 10, stdin);
    is_valid = validate(password);

    while(is_valid!=1){
        printf("Invalid data. Enter a password between 5 and 10 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);
        is_valid = validate(name);
    }


        name[strlen(name)-1]='\0';


    strcpy(new_user.username, name);
    new_user.hash_pass = hashing(password);
    new_user.id = return_last_id();
    new_user.id+=1;

    return new_user;
}

void append_user(struct user_t *user){
    FILE *fp;
    fp = fopen("C:\\Users\\user\\Desktop\\text.txt", "a+");
    fprintf(fp, "%d %s %d %c", user->id, user->username, user->hash_pass, '\n');

    fclose(fp);

}

int main(){

    struct user_t u = register_user();
    append_user(&u);

    return 0;
}
