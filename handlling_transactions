#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account_t{

    char iban[41];
    int balance;
    int id;
};


struct transaction_t{

    char code[10];
    int sum;
    char iban_to[41];
    char iban_from[41];

};

//CHECK IF FILE IS EMPTY
int file_check(char *file)
{
    FILE *fp;
    fp = fopen(file, "a");

    if (fp == NULL){
        printf("No data\n");
        return 0;
        }
    else {
        if (fp != NULL) {
            fseek (fp, 0, SEEK_END);
           int size = ftell(fp);

            if (0 == size) {
                printf("file is empty\n");
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    fclose(fp);
}

//FUNCTION FOR FOR WITHFRAL FROM ACCOUNT
int withdral(int amount,int sum){
    if (amount<sum){
        printf("no money\n");
        return 0;

        //char ep[] ="ERROR";
    }
    else{amount=amount-sum;};
    return amount;
}

//FUNCTION FOR FOR DEPOSITION FROM ACCOUNT
int deposit(int  amount,int deposition){
    if(deposition<0){
            printf("ERROR");
    }
    else{
        amount = amount + deposition;

        return amount;
    }

}
//FUNCTION FOR CHANGING THE VALUE OF THE MONEY IN AN ACCOUNT
void update(char *file, int id, int sum){
    FILE *fp;
    FILE * fptmp;

     int i;
    char iban[25];
    int money;

    fp = fopen(file, "r");
    fptmp = fopen("temp_file.txt", "w");

    int flag = 0;
    while(fscanf(fp, "%d %s %d" , &i, iban, &money)==3){
        if(i == id){
            flag = 1;
        }

        if (flag != 1){

            fprintf(fptmp, "%d %s %d %c", i, iban, money, '\n');
        }
        else{

            fprintf(fptmp, "%d %s %d %c", i, iban, sum, '\n');
            flag =0;

        }
    }

    fclose(fp);
    fclose(fptmp);
    remove(file);
    rename("temp_file.txt",file );


}

//FINDS STRUCTURE BY USING IBAN
struct account_t find_struct(char *file, char *object){
     FILE *fp;

    int id;
    char iban[25];
    char buff[30];
    int money;

    fp = fopen(file, "r");
    while(fscanf(fp, "%d %s %d" , &id, iban, &money)==3){
        fgets(buff, sizeof(buff),fp);

        sscanf( buff, "%d %s %d", &id, iban,&money);

       if (strcmp(object, iban )== 0) {
             fclose(fp);
             struct account_t account;
             account.balance = money;
             strcpy(account.iban, iban);
             account.id = id;
             return account;
       }

    }
}

//MAKES TRANSACTION BETWEEN TWO ACCOUNTS
void transaction_func(struct transaction_t transaction){
    struct account_t account_from;
    struct account_t account_to;

    account_from = find_struct("accounts.txt", transaction.iban_from);
    account_to = find_struct("accounts.txt", transaction.iban_to);

    int sum_transaction = withdral(account_from.balance, transaction.sum);
    if (sum_transaction > 0){

        //update("accounts.txt", account_from.id, withdral(account_from.balance, transaction.sum));
        update("accounts.txt", account_from.id, sum_transaction);
        update("accounts.txt", account_to.id, deposit(account_to.balance, transaction.sum));
    }
    else{
        printf("no money\n");
    }


}


//HANDLE TRANSACTIONS FROM FILE
void handle_transactions(char *file){

    FILE *fp;
    fp = fopen(file, "r");

    struct transaction_t transaction;
    char code [10];
    int sum;
    char iban_to[41];
    char iban_from[41];

    while (fscanf(fp, "%s %d %s %s" , code, &sum, iban_to, iban_from)==4){
    strcpy(transaction.code, code);
    transaction.sum = sum;
    strcpy(transaction.iban_to, iban_to);
    strcpy(transaction.iban_from, iban_from);

    if (strcmp(transaction.code, "11111") == 0){
         transaction_func(transaction);
    }

    }

    //WIPES DATA IN THE FILE
    fclose(fopen(file, "w"));
    //fclose(fp);

}
//CHECK IF THERE ARE TRANSACTIONS
void check_transactions(char *file){
    if (file_check(file) == 0){
            printf("No transactions");
        }
    else{

        handle_transactions(file);
    }
}

//PUTS NEW TRANSACTION IN THE FILE
void new_transaction(struct transaction_t transaction){

    FILE *fp;
    fp = fopen("transactions.txt", "a+");

    fprintf(fp, "%s %d %s %s %c", transaction.code, transaction.sum, transaction.iban_to, transaction.iban_from, '\n');

    fclose(fp);

}

int main()
{   //SOME STRUCTS FOR EXAMPLE
    struct transaction_t transaction1 = {"11111",50,"KK17DXWL55258195072010", "LR53AXZT41094781650108"};
    struct transaction_t transaction2 = {"11111",100,"LR53AXZT41094781650108", "IB54CVBM16375583454866"};
    struct transaction_t transaction3 = {"11111",30, "JH20UBXN93481554765498", "KR93CMZB02499938878135"};
    struct transaction_t transaction4 = {"11111",50, "KK17DXWL55258195072010", "LR53AXZT41094781650108"};

    new_transaction(transaction1);
    new_transaction(transaction2);
    new_transaction(transaction3);
    new_transaction(transaction4);

    check_transactions("transactions.txt");

    return 0;
}
