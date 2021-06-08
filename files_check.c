#include <stdio.h>

void file_check(char *file)
{
    FILE *fp;
    fp = fopen(file, "w");

    fputs("First user", fp);
    printf("End of function");

    fclose(fp);
}

int main()
{

    file_check("user.txt");
    file_check("account.txt");
    file_check("transaction.txt");
    printf("End of program");
    return 0;
}