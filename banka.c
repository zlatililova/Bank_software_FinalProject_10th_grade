#include <stdio.h>
#include <stdlib.h>
void deposit(int *amount,int *deposition){

    if(deposition<0){printf("ERROR");}
    *amount=*amount + *deposition;
}
void withdral(int *amount,int *sum,char *p){
    if (*amount<*sum){
        printf("error\n");
        *p="ERROR";
    }
    else{*amount=*amount-*sum;};
}
int main()
{
    int amount=1000;
    int deposition;
    int sum;
    char p;
    printf("Enter the deposit:");
    scanf("%d",&deposition);
    printf("Enter the withdral:");
    scanf("%d",&sum);
    //printf("%d\n",deposition);
    deposit(&amount,&deposition);
    withdral(&amount,&sum,&p);
    printf("%d pachki po stotachki ",amount);
    printf("%c",p);



    return 0;
}
