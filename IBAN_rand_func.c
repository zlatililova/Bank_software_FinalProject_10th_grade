#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void file_check(char *file)
{
    FILE *fp;
    fp = fopen(file, "a");

    fclose(fp);
}

void add_random_symbols(char *file, int lower, int upper, int counter)
{
    printf("funcrion begins  ");
    srand(time(0));
    FILE *fp;
    fp = fopen(file, "a+");

    int i;
    for (i = 0; i < counter; i++)
    {
        int str = (rand() % (upper - lower + 1)) + lower;
        fprintf(fp, "%c", str);
    }
    fclose(fp);
    printf("Function ends\n ");
}

void append_IBAN(char *file)
{
    FILE *fp;
    fp = fopen(file, "a+");
    printf("OK \n");
    //random numbers;
    //first two letters
    add_random_symbols(file, 'A', 'Z', 2);
    //special num
    add_random_symbols(file, '0', '9', 2);

    //adds 4 random letters to file
    add_random_symbols(file, 'A', 'Z', 4);
    printf("First add is ok\n");
    // adds 14 random number chars to file;
    add_random_symbols(file, '0', '9', 14);

    fprintf(fp, "%c", '\n');
    fclose(fp);
}

int main()
{

    file_check("IBAN.txt");
    append_IBAN("IBAN.txt");
    printf("\n The answer is %d \n", compare("IBAN.txt", "QODZSU26194226790289BGG"));
    printf("\n The answer is %d \n", compare("IBAN.txt", "QODZSU26194226790289BG"));

    return 0;
}
