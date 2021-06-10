#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct user_t
{

    char username[21];
    int hash_pass;

    int id;
    //unsigned int id;
};

void file_check(char *file)
{
    FILE *fp;
    fp = fopen(file, "a");

    //fputs("First user", fp);

    //if (file is empty);
    printf("No data\n");

    fclose(fp);
}

int hashing(char *password, int size_of_pass)
{
    printf("%s\n", password);
    int pass_len = strlen(password);
    int sum = 0;

    for (int i = 0; i < pass_len; i++)
    {
        sum += *(password + i);
        printf("sum = %d\n", sum);
    }
    printf("%d\n", size_of_pass);

    printf("%d\n", sum % size_of_pass);

    return sum % size_of_pass;
}

void append_user(struct user_t *user)
{
    FILE *fp;
    fp = fopen("users.txt", "a+");

    fprintf(fp, "%d %s %d %c", user->id, user->username, user->hash_pass, '\n');

    fclose(fp);
}

// not working comparison
void compare(struct user_t *user, char *file, char *object)
{

    FILE *fp;
    char buff[255]; //creating char array to store data of file
    fp = fopen(file, "r");
    //while(fscanf(fp, "%s", buff)!=EOF || fscanf(fp, "%s", buff)!= " "){
    while (fscanf(fp, "%s", buff) != EOF)
    {
        printf("word = %s\n", buff);
        if (strcmp("Dobri", buff) == 0)
        {
            printf("There is somethink");
            break;
        }
    }
    printf("Before close;");

    fclose(fp);
    printf("End of FUNCTION");
}

int main()
{

    file_check("users.txt");
    file_check("accounts.txt");
    file_check("transactions.txt");

    struct user_t first_person;
    strcpy(first_person.username, "Misho");
    //printf("name = %s\n, first_person.username);

    /*
    char * pass = "234234";
    printf("hash = %s\n", hashing( pass, strlen(pass)));
   */
    first_person.hash_pass = 1234;
    first_person.id = 14;
    //printf("name = %d\n", first_person.id);
    append_user(&first_person);

    // compare(,user,)

    //working comparison
    FILE *fp;
    char buff[255]; //creating char array to store data of file
    fp = fopen("users.txt", "r");
    //while(fscanf(fp, "%s", buff)!=EOF || fscanf(fp, "%s", buff)!= " "){
    while (fscanf(fp, "%s", buff) != EOF)
    {
        printf("word = %s\n", buff);
        if (strcmp("Gancho", buff) == 0)
        {
            printf("HERE is equal\n");
        }
    }

    printf("End of FUNCTION");
    fclose(fp);

    printf("End of ProgrAM");
    return 0;
}
