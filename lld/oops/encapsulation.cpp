/*
Encapsulation is one of the four fundamental principles of Object-Oriented Programming (OOP). It is the practice of bundling data (variables) and methods that operate on that data into a single unit (class) while restricting direct access to the internal details.

Encapsulation in C++ is achieved using:

Access Specifiers (private, protected, public)
Getters and Setters
Data Hiding


Encapsulation helps in data protection, modularity, and maintainability of the code.

What is meant by Encapsulation?

Encapsulation means wrapping the data (variables) and code (methods) together into a single unit (class). It restricts direct access to some of an object's components, which helps protect data integrity and prevents unintended modifications.

Key Benefits of Encapsulation
Data Hiding: Prevents direct access to sensitive data.
Increased Security: Controls how data is accessed and modified.
Improved Code Maintainability: Allows changes without affecting other parts of the code.
Better Modularity: Organizes the code into logical components.

3. Encapsulation USingm Access Specifiers

C++ provides access specifiers to enforce encapsulation:

private: Accessible only within the same class.
protected: Accessible within the same class and derived classes.
public: Accessible from anywhere.

*/

//1. Encapsulation with Private Variables

// #include <iostream>
// using namespace std;

// // Class with encapsulated data
// class BankAccount {
// private:
//     string accountHolder;
//     double balance;

// public:
//     // Constructor
//     BankAccount(string name, double bal) {
//         accountHolder = name;
//         balance = bal;
//     }

//     // Getter method to access balance
//     double getBalance() {
//         return balance;
//     }

//     // Setter method to modify balance
//     void deposit(double amount) {
//         if (amount > 0) {
//             balance += amount;
//             cout << "Deposited: " << amount << endl;
//         } else {
//             cout << "Invalid deposit amount" << endl;
//         }
//     }
// };

// int main() {
//     BankAccount account("Alice", 1000);
//     cout << "Current Balance: " << account.getBalance() << endl;
//     account.deposit(500);
//     cout << "Updated Balance: " << account.getBalance() << endl;
//     return 0;
// }


// Encapsultion Using Getters and Setters

// #include <iostream>
// using namespace std;

// class Employee {
// private:
//     string name;
//     int age;

// public:
//     // Getter method
//     string getName() {
//         return name;
//     }

//     // Setter method
//     void setName(string newName) {
//         name = newName;
//     }

//     int getAge() {
//         return age;
//     }

//     void setAge(int newAge) {
//         if (newAge > 18) {
//             age = newAge;
//         } else {
//             cout << "Age must be greater than 18" << endl;
//         }
//     }
// };

// int main() {
//     Employee emp;
//     emp.setName("John Doe");
//     emp.setAge(25);
//     cout << "Employee Name: " << emp.getName() << endl;
//     cout << "Employee Age: " << emp.getAge() << endl;
//     return 0;
// }


// Encapsulation and Data Hiding

// #include <iostream>
// using namespace std;

// class Account {
// private:
//     double balance;

//     bool validateWithdrawal(double amount) {
//         return amount > 0 && amount <= balance;
//     }

// public:
//     Account(double initialBalance) {
//         balance = initialBalance;
//     }

//     void withdraw(double amount) {
//         if (validateWithdrawal(amount)) {
//             balance -= amount;
//             cout << "Withdrawal Successful: " << amount << endl;
//         } else {
//             cout << "Insufficient balance or invalid amount" << endl;
//         }
//     }

//     double getBalance() {
//         return balance;
//     }
// };

// int main() {
//     Account myAccount(1000);
//     myAccount.withdraw(300);
//     cout << "Remaining Balance: " << myAccount.getBalance() << endl;
//     return 0;
// }


// Encapsulation in Real World Applications Ex: Payment System

#include <iostream>
using namespace std;

class PaymentProcessor {
private:
    string cardNumber;
    double amount;

    string maskCardNumber(string cardNumber) {
        return "****-****-****-" + cardNumber.substr(cardNumber.length() - 4);
    }

public:
    PaymentProcessor(string card, double amt) : cardNumber(card), amount(amt) {}

    void processPayment() {
        cout << "Processing payment of " << amount << " for card " << maskCardNumber(cardNumber) << endl;
    }
};

int main() {
    std::unique_ptr<PaymentProcessor> payment = make_unique<PaymentProcessor>("1234567812345678", 250.00);
    payment->processPayment();
    return 0;
}