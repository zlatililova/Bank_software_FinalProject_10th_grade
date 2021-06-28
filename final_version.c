#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct user_t
{

    char username[11];
    int hash_pass;
    unsigned int id;

};
struct account_t
{

    char iban[41];
    int balance;
    unsigned int id;
};

struct transaction_t
{

    char code[10];
    int sum;
    char iban_to[41];
    char iban_from[41];
};

void menu1();
void menu2();
int compare(char *file, char *object);
char* create_Iban();


int is_in_database(char name[], int hashed_password);
int hashing (char password[]);
int validate(char name[]);
int return_last_id();
struct user_t log_user(int type_of_log);
void append_user(struct user_t *user);
void append_account(struct account_t *acc);
struct account_t create_account(struct user_t *user);


int file_check(char *file);
void update(char *file, int id, int sum);
struct account_t find_struct_by_id(char *file, int object);
void transaction_func(struct transaction_t transaction);
void handle_transactions(char *file);
void check_transactions(char *file);
void new_transaction(struct transaction_t transaction);
struct account_t find_struct(char *file, char *object);
void create_transfer(char *file);



int withdral(int amount,int sum);
int deposit(int  amount,int deposition);

int main()
{
    menu1();
    return 0;
}

//the main menu to log in a user
void menu1()
{
    char choice = '-'; //Избор в menu1()
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
        case '1':
        {
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
        case '2':
        {
            //register
            struct user_t logged_in_user = log_user(1);
            append_user(&logged_in_user);
            struct account_t acc = create_account(&logged_in_user);
            append_account(&acc);

            menu2(&logged_in_user);

            break;
        }

        case '0':
        {
            //logout
            break;
        }

        default:
            printf("Invalid input!\n");
            break;
        }
    }
}

//the secondary menu for the main opperations
void menu2(struct user_t *user)
{
    char choice2 = '-'; //Избор в menu2()
    char menu2[] = "1-Deposit\n"
                   "2-Withdraw\n"
                   "3-Transfer\n"
                   "4-Edit transactions\n"
                   "0-Logout\n";
    struct account_t acc;

    while(choice2 != '0')
    {
        system("cls");
        printf("%s", menu2);
        scanf("%s", &choice2);
        switch (choice2)
        {
        case '1':
        {
            //Deposit
            acc = find_struct_by_id("accounts.txt", user->id);
            int money = 0;
            while(money == 0)
            {
                printf("Enter sum you want to deposit\n");
                scanf("%d",&money);
            }

            int new_amount = deposit(acc.balance, money);
            update("accounts.txt",acc.id, new_amount);

            break;
        }
        case '2':
        {
            //Withdraw
            int id = user->id;
            acc = find_struct_by_id("accounts.txt",id);
            int money = 0;
            //while(money == 0){
            printf("Enter sum you want to withdraw\n");
            scanf("%d",&money);
            int new_amount = withdral(acc.balance, money);
            update("accounts.txt",acc.id, new_amount);

            break;
        }
        case '3':
        {
            //Transfer
            create_transfer("accounts.txt");

            break;
        }


        case '4':
        {
            //edit transactions
            check_transactions("transactions.txt");
            printf("All transactions are made\n");
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

//function that checks if a certain string can be found in a file
int compare(char *file, char *object)
{
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

//function that check if the data, entered by a user, is present in the users file
int is_in_database(char name[], int hashed_password)
{

    int in_database = 0;
    FILE *fptr;

    char str[11];
    int med;
    int pass_check = 0;
    int name_check = 1;
    int id = 0;

    if((fptr = fopen("users.txt", "r")) == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


    while (fscanf(fptr, "%d %s %d",&id,str,&med)==3)
    {
        if(med == hashed_password)
        {
            pass_check = 1;
        }
        name_check = strncmp(name,str,sizeof(str));

        if(pass_check == 1 && name_check == 0)
        {
            in_database = 1;
            break;

        }


    }


    if(in_database == 1)
    {
        return id;
    }
    else
    {
        return 0;
    }
}

//funtion the generates a random Iban
char* create_Iban()
{
    //printf("function begins\n");
    srand(time(0));
    char *arr = malloc(23*sizeof(char));

    char alphabet[26] = {  'A', 'B', 'C', 'D', 'E', 'F', 'G',
                           'H', 'I', 'J', 'K', 'L', 'M', 'N',
                           'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                           'V', 'W', 'X', 'Y', 'Z'
                        };
    char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i < 23; i++)
    {
        if(i<2 || (i>3 && i<8))
        {
            arr[i] = alphabet[rand() % 26];
        }
        else
        {
            arr[i]  = numbers[rand() % 10];
        }
    }
    arr[22] = '\0';

    return arr;

}

//algorithm for encrypting the password
int hashing (char password[])
{
    int pass_len = strlen(password);
    int sum = 0;

    for(int i = 0; i<pass_len-1; i++)
    {
        sum += password[i];
    }
    return sum;
}

//function that checks if the entered data is the needed lenght and consists only of letters and numbers
int validate(char name[])
{
    int l = strlen(name);
    int flag = 1;
    //check length is 0 or more than 30
    if (l < 6 || l > 11)
        return 0;

    for (int i = 0; name[i]!='\0'; i++)
    {
        char s = name[i];

        if (s>='a'&&s<='z')
        {
            flag = 1;
        }
        else if (s>='A'&&s<='Z')
        {
            flag = 1;
        }
        else if(s>='0'&& s<='9')
        {
            flag = 1;
        }
        else if(s == '\n')
        {
            flag = 1;
        }
        else
        {
            return 0;
        }
    }
    return flag;
}

//helping function to create an unique id based on the last id, present in the files
int return_last_id()
{
    FILE *fptr;
    int last_id;
    char str[50];
    char *ptr;

    if ((fptr = fopen("C:\\Users\\user\\Desktop\\users.txt","a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while (!feof(fptr))
    {
        fgets(str, sizeof(str), fptr);
    }
    last_id = (int)strtol(str, &ptr, 10);
    fclose(fptr);

    return last_id;
}

//main function for logging a user, based on the flag given it either logs or registers the user
struct user_t log_user(int type_of_log) //0 - log in or 1 - register
{
    struct user_t new_user;
    char password[11];
    char *name = malloc(sizeof(char)*11);
    int is_valid = 0;
    int second = 1;

    if(type_of_log == 1)
    {
        second = 1;
    }
    else
    {
        second = 0;
    }

    while(is_valid!= 1 || second != 0)
    {
        fgets(name, 10, stdin);
        printf("Enter a user name between 5 and 10 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);

        is_valid = validate(name);
        if(type_of_log == 1)
        {
            second = compare("users.txt", name);
        }
    }

    is_valid = 0;


    while(is_valid!=1)
    {
        printf("Enter a password between 5 and 10 characters, use only letters and numbers:\n");
        fgets(password, 10, stdin);

        is_valid = validate(password);
    }


    name[strlen(name)-1]='\0';


    strcpy(new_user.username, name);
    new_user.hash_pass = hashing(password);
    new_user.id = return_last_id();
    new_user.id+=1;
    free(name);

    return new_user;

}

//appends a stucture user_t to the file of users
void append_user(struct user_t *user)
{
    FILE *fp;
    fp = fopen("C:\\Users\\user\\Desktop\\users.txt", "a+");
    fprintf(fp, "%d %s %d %c", user->id, user->username, user->hash_pass, '\n');

    fclose(fp);

}

//appends a stucture accounts_t to the file of accounts
void append_account(struct account_t *acc)
{
    FILE *fp;
    fp = fopen("C:\\Users\\user\\Desktop\\accounts.txt", "a+");
    fprintf(fp, "%d %s %d %c", acc->id, acc->iban, acc->balance, '\n');

    fclose(fp);

}

//function to create a new account if the user is registering for the first time
struct account_t create_account(struct user_t *user)
{
    struct account_t new_acc;
    new_acc.id = user->id;
    new_acc.balance = 0;
    strcpy(new_acc.iban, create_Iban());

    return new_acc;

}

//function that checks if a file is existing and check if it is empty 
int file_check(char *file)
{
    FILE *fp;
    fp = fopen(file, "a");

    if (fp == NULL)
    {
        printf("No data\n");
        return 0;
    }
    else
    {
        if (fp != NULL)
        {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
                printf("file is empty\n");
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    fclose(fp);
}

//function to perform the main opperation when withdrawing
int withdral(int amount, int sum)
{
    if (amount<sum)
    {
        printf("no money\n");
        return 0;
    }
    else
    {
        amount = amount-sum;
    }
    return amount;
}

//function to perform the main opperation when depositing
int deposit(int  amount,int deposition)
{
    if(deposition<0)
    {
        printf("ERROR");
    }
    else
    {
        amount = amount + deposition;

        return amount;
    }

}

//function to update balance of a certain account in accounts.txt; it uses a temporaty file
void update(char *file, int id, int sum)
{
    FILE *fp;
    FILE * fptmp;

    int i;
    char iban[25];
    int money;

    fp = fopen(file, "r");
    fptmp = fopen("temp_file.txt", "w");

    int flag = 0;
    while(fscanf(fp, "%d %s %d", &i, iban, &money)==3)
    {
        if(i == id)
        {
            flag = 1;
        }

        if (flag != 1)
        {

            fprintf(fptmp, "%d %s %d %c", i, iban, money, '\n');
        }
        else
        {

            fprintf(fptmp, "%d %s %d %c", i, iban, sum, '\n');
            flag =0;

        }
    }

    fclose(fp);
    fclose(fptmp);
    remove(file);
    rename("temp_file.txt",file);


}

//finds and returns account based on a given id
struct account_t find_struct_by_id(char *file, int object)
{
    FILE *fp;

    int id;
    char iban[25];
    char buff[30];
    int money;

    fp = fopen(file, "r");
    while(fscanf(fp, "%d %s %d", &id, iban, &money)==3)
    {

        if (object == id)
        {
            fclose(fp);
            struct account_t account;
            account.balance = money;
            strcpy(account.iban, iban);
            account.id = id;
            return account;
        }

    }
}

//finds and returns account based on a given Iban
struct account_t find_struct(char *file, char *object)
{
    FILE *fp;

    int id;
    char iban[25];
    char buff[30];
    int money;

    fp = fopen(file, "r");
    while(fscanf(fp, "%d %s %d", &id, iban, &money)==3)
    {
        fgets(buff, sizeof(buff),fp);

        sscanf( buff, "%d %s %d", &id, iban,&money);

        if (strcmp(object, iban )== 0)
        {
            fclose(fp);
            struct account_t account;
            account.balance = money;
            strcpy(account.iban, iban);
            account.id = id;
            return account;
        }

    }
}

//makes the main operation of a transaction - withdraw form first acc and deposit to the second
void transaction_func(struct transaction_t transaction)
{
    struct account_t account_from;
    struct account_t account_to;

    account_from = find_struct("accounts.txt", transaction.iban_from);
    account_to = find_struct("accounts.txt", transaction.iban_to);

    int sum_transaction = withdral(account_from.balance, transaction.sum);
    if (sum_transaction > 0)
    {

        //update("accounts.txt", account_from.id, withdral(account_from.balance, transaction.sum));
        update("accounts.txt", account_from.id, sum_transaction);
        update("accounts.txt", account_to.id, deposit(account_to.balance, transaction.sum));
    }
    else
    {
        printf("no money\n");
    }


}

//the file handling of transacion - it extracts all the necessary information from the file
void handle_transactions(char *file)
{

    FILE *fp;
    fp = fopen(file, "r");

    struct transaction_t transaction;
    char code [10];
    int sum;
    char iban_to[41];
    char iban_from[41];

    while (fscanf(fp, "%s %d %s %s", code, &sum, iban_to, iban_from)==4)
    {
        strcpy(transaction.code, code);
        transaction.sum = sum;
        strcpy(transaction.iban_to, iban_to);
        strcpy(transaction.iban_from, iban_from);

        if (strcmp(transaction.code, "11111") == 0)
        {
            transaction_func(transaction);
        }

    }

    //WIPES DATA IN THE FILE
    fclose(fopen(file, "w"));
    //fclose(fp);

}

//checks if there are any transactions in the file and handles them
void check_transactions(char *file)
{
    if (file_check(file) == 0)
    {
        printf("No transactions");
    }
    else
    {

        handle_transactions(file);
    }
}

//appenrd a new tranfer to the file
void new_transaction(struct transaction_t transaction)
{

    FILE *fp;
    fp = fopen("transactions.txt", "a+");

    fprintf(fp, "%s %d %s %s %c", transaction.code, transaction.sum, transaction.iban_to, transaction.iban_from, '\n');

    fclose(fp);

}

//gets all the necessary info form the user and creates a tranfer struct
void  create_transfer(char *file)
{
    char iban_to [31];
    char iban_from [31];
    int sum_transaction;
    struct account_t account_from;

    int is_valid = 0;

    while(is_valid!=1)
    {
        fgets(iban_from, sizeof(iban_from), stdin);
        printf("Enter an iban from whom the transaction:\n");
        fgets(iban_from, sizeof(iban_from), stdin);
        iban_from[strcspn(iban_from, "\n")] = 0;

        is_valid = compare(file, iban_from);
    }

    is_valid = 0;
    while(is_valid!=1)
    {
        fgets(iban_to, sizeof(iban_to), stdin);
        printf("Enter an iban to whom the transaction:\n");
        fgets(iban_to, sizeof(iban_to), stdin);
        iban_to[strcspn(iban_to, "\n")] = 0;

        is_valid = compare(file, iban_to);
    }

    is_valid = 0;

    while(is_valid!=1)
    {

        printf("Enter sum:\n");
        scanf("%d", &sum_transaction);
        account_from = find_struct(file,iban_from);
        if (sum_transaction <= account_from.balance)
        {
            is_valid = 1;
        }
    }


    struct transaction_t transaction;
    strcpy(transaction.code, "11111");
    transaction.sum = sum_transaction;
    strcpy(transaction.iban_from, iban_from);
    strcpy(transaction.iban_to, iban_to);
    new_transaction(transaction);
}
