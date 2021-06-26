#include <stdio.h>
#include <stdlib.h>
struct list_t {
  struct transaction_t* head;
  struct transaction_t* tail;
  int size;
};
struct transaction_t{

    char code[10];
    int sum;
    char iban_to[41];
    char iban_from[41];
    struct transaction_t* prev;
    struct transaction_t* next;

};
void push_front(struct list_t* list, struct transaction_t* profil) {
  struct transaction_t* new_node = malloc(sizeof(struct transaction_t));
  new_node=profil ;

  new_node->prev = NULL;
  if(list->head != NULL) {

    list->head->prev = new_node;
  } else {
    list->tail = new_node;
  }
  new_node->next = list->head;

  list->head = new_node;

  list->size++;
}
void print_list(struct list_t* list) {
  struct transaction_t* curr = list->head;
  int counter = 1;
  printf("Size = %d\n", list->size);

  while(curr != NULL) {
    printf("[%d] %s\n", counter++, curr->code);
    curr = curr->next;
  }
}


int main()
{

    struct list_t profilelist={NULL,NULL,0};

    struct transaction_t Kolo={"121",50,"KK17DXWL55258195072010","LR53AXZT41094781650108",NULL,NULL};
    struct transaction_t Dani={"126",51,"KK17DXWL55258195072010","LR53AXZT41094781650108",NULL,NULL};
    struct transaction_t Moni={"121",52,"KK17DXWL55258195072010","LR53AXZT41094781650108",NULL,NULL};
    struct transaction_t Zlati={"122",53,"KK17DXWL55258195072010","LR53AXZT41094781650108",NULL,NULL};
    struct transaction_t Niki={"124",54,"KK17DXWL55258195072010","LR53AXZT41094781650108",NULL,NULL};




    push_front(&profilelist,&Kolo);
    push_front(&profilelist,&Dani);
    push_front(&profilelist,&Moni);
    push_front(&profilelist,&Zlati);
    push_front(&profilelist,&Niki);

    print_list(&profilelist);


    printf("Hello world!\n");
    return 0;
}
