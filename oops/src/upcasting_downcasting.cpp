#include <iostream>
#include "../include/account.h"
#include "../include/savings.h"
#include "../include/checking.h"
#include "../include/transaction.h"

int main(){
    Checking ch("Bob", 100);
    Account *pAcc = &ch; // upcasting, the base class must be a pointer or reference to the child class
    // to work as polymorphic, the base class must be a pointer or reference to the child class
    

    Checking *pCh = static_cast<Checking*>(pAcc); // downcasting, the base class must be a pointer or reference to the child class
    // to work as polymorphic, the base class must be a pointer or reference to the child class
    // since child class has all its data members, compiler does object slicing deliberately so that base class
    // pointer can hold reference to the child class object
    // so we need to use static_cast to downcast the pointer
    

    return 0;
}
