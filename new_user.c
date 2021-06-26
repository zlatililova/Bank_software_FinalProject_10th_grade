void add_user(struct user_t new_user)
{
    printf("hash = %d\n", new_user.hash_pass);
    //convert hash_pass into int
    char txt[20];
    sprintf(txt, "%d", new_user.hash_pass);
    //printf("%s",txt);

    FILE *fp;
    fp = fopen("users.txt", "a");
    //not sure
    //fputs(new_user.username,fp);
    //hash
    fputs(txt, fp);

    //id
    /*
    char id [50];
    sprintf(txt,"%u",new_user.id);
    fputs(id, fp);
*/
    printf("End of function\n");

    fclose(fp);
}
