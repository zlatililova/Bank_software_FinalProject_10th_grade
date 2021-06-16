#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void update(char *file, int id, int sum)
{
    int counter = 0;
    int flag = 0;

    FILE *fp;
    //
    int i;
    char buff[25]; //creating char array to store data of file
    char sm_buff[10];
    fp = fopen(file, "r+");

    while (fscanf(fp, "%s", buff) != EOF)
    {
        if (counter == 0 || counter % 3 == 0)
        {

            sscanf(buff, "%d", &i);
            if (i == id)
            {
                printf("id = %d", i);
                flag = 1;
                counter = 1;
            }
        }
        if (counter == 2 && flag == 1)
        {
            strncpy(sm_buff, buff, sizeof(sm_buff));
            sscanf(sm_buff, "%d", i);
            break;
        }

        counter++;
    }

    fclose(fp);
    printf("End of FUNCTION");
}

int main()
{
    update("accounts.txt", 1, 50);

    return 0;
}
