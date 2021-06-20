#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct account_t
{

    char iban[41];
    int balance;
    unsigned int id;
};

void update(char *file, int id, int sum)
{
    int counter = 0;
    int flag = 0;

    printf("ok\n");

    FILE *fp;
    //
    int i;
    int curr_money;
    char buff[50]; //creating char array to store data of file
    //char *ptr;
    char iban[25];
    int money;
    char sm = '\0';

    fp = fopen(file, "r+");

    fseek(fp, 0, SEEK_SET);

    while (!feof(fp))
    {
        fgets(buff, sizeof(buff), fp);
        sscanf(buff, "%d %s %d", &i, iban, &money);
        printf("id = %d\n", i);
        printf("iban = %s\n", iban);
        printf("money = %d\n", money);

        if (i + 1 == id)
        {
            fseek(fp, 25, SEEK_CUR);

            sscanf(buff, "%*d %*s %d", &money);

            //char *point = money;
            //point = sum;

            fprintf(fp, "%d ", sum);

            //mine
            /*
            char money_arr[] = "76";
            int len = strlen(money_arr);

            printf("money = %s  len = %d\n", money_arr, len);

            for (int f = 0; f < len; f++) {
                    printf("buff = %s\n", buff);
                if (buff == '\n' || buff == ' '){
                    int flag =1;
                    printf("here is a flag\n");
                }
                else
                {
                    printf("not here\n");
                    //printf("fp = %c", fp);
                }
                printf("Character we are writing to the File = %c \n", money_arr[f]);
                fputc (money_arr[f], fp);
            }
            if (flag){
           fputc(' ', fp);

           fputc(' ', fp);

           fputc(' ', fp);
            fputc('\n', fp);

            }
*/
            struct account_t acc = {i, iban, sum};
            break;
        }
    }

    fclose(fp);
    printf("End of FUNCTION");
}

int main()
{

    update("accounts.txt", 3, 540);

    return 0;
}
