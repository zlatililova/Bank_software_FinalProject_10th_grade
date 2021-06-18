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

void menu1();
void menu2();

int compare(char *file, char *object);
char* create_Iban();

//functions of Zlati
int is_in_database(char name[], int hashed_password);
int hashing (char password[]);
int validate(char name[]);
int return_last_id();
struct user_t log_user(int type_of_log);
void append_user(struct user_t *user);
void append_account(struct account_t *acc);
struct account_t create_account(struct user_t *user);
//end of Zlati's functions

int main()
{
  menu1();
    return 0;
}

void menu1()
{
  char choice = "-"; //Избор в menu1()
  char menu1[] = "What do you want to do?\n"
          "1-Log in\n"
          "2-Register\n"
          "0-Exit\n";

  while(choice != '0')
  {
    printf("%s", menu1);
    scanf("%s", &choice);

      switch (choice)
      {
        case '1':{
        //Log_in();
            struct user_t logged_in_user;
            logged_in_user = log_user(0);
            int id = is_in_database(logged_in_user.username, logged_in_user.hash_pass);
            if(id!=0)
            {
                logged_in_user.id = id;
                menu2(&logged_in_user);
            }
              break;
        }
        case '2':{
            //register
            struct user_t logged_in_user = log_user(1);
            append_user(&logged_in_user);
            struct account_t acc = create_account(&logged_in_user);
            append_account(&acc);

            menu2(logged_in_user);

            break;
        }

        case '0':{
            //logout
            break;
        }

        default:
          printf("Invalid input!\n");
          break;
      }
  }
}

void menu2(struct user_t *user)
{
  char choice2 = "-"; //Избор в menu2()
  char menu2[] = "1-Deposit\n"
                "2-Withdraw\n"
                "3-Transfer\n"
                "4-Edit transactions\n"
                "0-Logout";

  while(choice2 != '0')
  {
    printf("%s", menu2);
    scanf("%s", &choice2);
      switch (choice2)
      {
        case '1':{
            //Deposit

            break;
        }
        case '2':{
            //Withdraw

            break;
        }
        case '3':{
            //Transfer

          break;
        }


        case '4':{
            //edit transactions

          break;
        }

        case '0':
        //go back
          break;
        default:
        printf("Invalid input!\n");
          break;
      }
  }
}
int compare(char *file, char *object){
    FILE *fp;
    int i = 0;

    char buff[50];
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

int is_in_database(char name[], int hashed_password){

  int in_database = 0;
 FILE *fptr;

    char str[50];
    int med;
    int pass_check = 0;
    int id=0;

  if((fptr = fopen("C:\\Users\\user\\Desktop\\users.txt", "a+")) == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

    int name_check = compare("users.txt", name);


    while (!feof(fptr))
    {
        fgets(str, sizeof(str), fptr);
        int i = 0;
        char *token = strtok(str, " ");

        while( token != NULL ) {
            if(i==0){
                sscanf(token, "%d", &id);
                //printf("id = %d\n",id);
            }
            if(i==2){
               sscanf(token, "%d", &med);
            }
            i++;
            token = strtok(NULL, " ");
        }

        if(med == hashed_password){
        pass_check = 1;
        break;
        }
    }

    if(pass_check == 1 && name_check == 1)
        in_database = 1;

    if(in_database == 1){
        return id;
    }else{
    return 0;
    }
}

char* create_Iban(){
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
        else if (s>='A'&&s<='Z'){
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

struct user_t log_user(int type_of_log){//0 - log in or 1 - register
    struct user_t new_user;
    char password[11];
    char *name = malloc(sizeof(char)*11);
    int is_valid = 0;
    int second = 1;

    if(type_of_log == 1){
        second = 1;
    }else{
        second = 0;
    }

    while(is_valid!= 1 || second != 0){
        fgets(name, 10, stdin);
        printf("Enter a user name between 5 and 10 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);

        is_valid = validate(name);
        if(type_of_log == 1){
            second = compare("users.txt", name);
        }
    }

    is_valid = 0;

    while(is_valid!=1){
        printf("Enter a password between 5 and 10 characters, use only letters and numbers:\n");
        fgets(password, 10, stdin);

        is_valid = validate(name);
    }


    name[strlen(name)-1]='\0';


    strcpy(new_user.username, name);
    new_user.hash_pass = hashing(password);
    new_user.id = return_last_id();
    new_user.id+=1;
    free(name);

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
