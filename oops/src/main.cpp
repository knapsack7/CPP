#include "../include/account.h"
#include <iostream>
#include "../include/savings.h"
#include "../include/checking.h"
#include "../include/transaction.h"

int main(){
    Savings acc("Bob", 100, 0.05f);
    transact(&acc);
    std::cout <<"Size of Account: " << sizeof(Account) << std::endl; // 4 bytes for vtable pointer
    return 0;
}