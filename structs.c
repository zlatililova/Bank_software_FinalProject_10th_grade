struct user_t{

    char username[21];
    int hash_pass;
    unsigned int id;
};

struct account_t{
    
    char iban[41];
    int balance;
    unsigned int id;
};

struct transaction_t{

    char code[10];
    int sum;
    char iban_to[41];
    char iban_from[41];
};




