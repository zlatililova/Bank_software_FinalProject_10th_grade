#include <stdio.h>
#include <stdlib.h>

struct account_t
{

    char iban[41];
    int balance;
    unsigned int id;
};

struct employee
{
    char name[50];
    char designation[50];
    int age;
    float salary
} employee;

void update(char *file, int id, int sum)
{
    FILE *fp;
    FILE *fptmp;

    int i;
    char buff[50]; //creating char array to store data of file
    //char *ptr;
    char iban[25];
    int money;

    fp = fopen(file, "r");
    //see for employee
    fptmp = fopen("temp_file.txt", "w");

    //why
    fseek(fp, 0, SEEK_SET);
    int flag = 0;
    while (!feof(fp))
    {

        fgets(buff, sizeof(buff), fp);

        sscanf(buff, "%d %s %d", &i, iban, &money);

        if (flag != 1)
        {

            fprintf(fptmp, "%d %s %d %c", i, iban, money, '\n');
        }
        else
        {

            fprintf(fptmp, "%d %s %d %c", i, iban, sum, '\n');
            flag = 0;
        }

        if (i + 1 == id)
        {
            flag = 1;
        }
    }

    fclose(fp);
    fclose(fptmp);
    remove(file);
    rename("temp_file.txt", file);
}

int main()
{
    update("accounts.txt", 4, 8543);

    return 0;
}