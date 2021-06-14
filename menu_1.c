#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
struct user_t{

    char username[11];
    int hash_pass;
    unsigned int id;

};

void menu1();
void menu2();
int is_in_database(char name[], int hashed_password);
int hashing (char password[]);
int compare(char *file, char *object);

int main()
{
  menu1();
    return 0;
}

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
    scanf("%c", &choice);

      switch (choice)
      {
        case '1':{
        //Log_in();
        struct user_t *logged_in_user;

        //това е код на Злати:
        char password[11];
        char name[11];
        int is_valid = 0;

        printf("Enter a user name between 5 and 10 characters, use only letters and numbers:\n");
        fgets(name, 10, stdin);
        //is_valid = validate(name);

        /*while(is_valid != 1){
            printf("Invalid data. Enter a user name between 5 and 20 characters, use only letters and numbers:\n");
            fgets(name, 10, stdin);
            //is_valid = validate(name);
        }*/

        printf("Enter a password between 5 and 10 characters, use only letters and numbers:\n");
        fgets(password, 10, stdin);
        //is_valid = validate(password);

        /*while(is_valid != 1){
            printf("Invalid data. Enter a password between 5 and 10 characters, use only letters and numbers:\n");
            fgets(name, 10, stdin);
            //is_valid = validate(password);
        }*/

        if(is_in_database(name, hashing(password)) == 1)
        {

            menu2(logged_in_user);
        }
          break;}
        case '2':
          break;
        case '0':
          break;
        defaut:
          printf("Invalid input!\n");
          break;
      }
  }
}

void menu2(struct user_t *user)
{
  char choice2 = '-'; //Избор в menu2()
  char menu2[] = "1-Deposit\n"
                "2-Withdraw\n"
                "3-Transfer\n"
                "4-Edit transactions\n"
                "0-Logout";

  while(choice2 != '0')
  {
    printf("%s", menu2);
    scanf("%c", &choice2);
      switch (choice2)
      {
        case '1':
        //това е нечия друга задача
          break;
        case '2':
        //това е нечия друга задача
          break;
        case '3':
        //това е нечия друга задача
          break;
        case '4':
        //това е нечия друга задача
          break;
        case '0':
        //go back
          break;
        defaut:
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

int is_in_database(char name[], int hashed_password)
{

  int in_database = 0;
 FILE *fptr;

    char str[50];
    int med;
    int pass_check = 0;

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


  return in_database;

}

int hashing (char password[]){
  //на Злати функция
    int pass_len = strlen(password);
    int sum = 0;

    for(int i = 0; i<pass_len-1; i++){
        sum += password[i];
    }
    return sum;
}
