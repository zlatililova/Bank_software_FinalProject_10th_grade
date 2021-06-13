#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

char* create_Iban()
{
    //printf("function begins\n");
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

int compare(char *file, char *object){
    FILE *fp;
    int i = 0;
    char buff[25]; //creating char array to store data of file
    fp = fopen(file, "r");

    while (fscanf(fp,"%s",buff)!= EOF)
    {
        if (strncmp(object,buff,strlen(object)-1)==0)
        {
            i = 1;
        }
    }
    fclose(fp);
    return i;
}

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

   if ((fptr = fopen("C:\\Users\\user\\Desktop\\users.txt","a+")) == NULL){
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
    char *name = malloc(sizeof(char)*11);
    int is_valid = 0;
    int second = 1;

    printf("Enter a user name between 5 and 10 characters, use only letters and numbers:\n");
    fgets(name, 10, stdin);
    is_valid = validate(name);
    second = compare("users.txt", name);

    while(is_valid!=1 || second != 0){
        printf("Invalid data. Enter a user name between 5 and 20 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);
        is_valid = validate(name);
        second = compare("users.txt", name);
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
    fp = fopen("C:\\Users\\user\\Desktop\\users.txt", "a+");
    fprintf(fp, "%d %s %d %c", user->id, user->username, user->hash_pass, '\n');

    fclose(fp);

}

void append_account(struct account_t *acc){
    FILE *fp;
    fp = fopen("C:\\Users\\user\\Desktop\\accounts.txt", "a+");
    fprintf(fp, "%d %s %d %c", acc->id, acc->iban, acc->balance, '\n');

    fclose(fp);

}

struct account_t create_account(struct user_t *user){
    struct account_t new_acc;
    new_acc.id = user->id;
    new_acc.balance = 0;
    strcpy(new_acc.iban, create_Iban());

    return new_acc;

}

int main(){

    struct user_t u = register_user();
    append_user(&u);
    struct account_t a = create_account(&u);
    append_account(&a);

    return 0;
}
