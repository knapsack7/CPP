#include <iostream>
#include <typeinfo>

using namespace std;

struct Contact{
    std::string m_name;
    std::string mobile;
    std::string address;
    std::string email;
    Contact(const std::string &name, const std::string &mobile, const std::string &address, const std::string &email) : m_name{name}, mobile{mobile}, address{address}, email{email}{
        //std::cout << "Contact(const std::string &, const std::string &, const std::string &, const std::string &) called" << std::endl;
    }
    Contact(const std::string &&name, const std::string &&mobile, const std::string &&address, const std::string &&email) : m_name{std::move(name)}, mobile{std::move(mobile)}, address{std::move(address)}, email{std::move(email)}{
        std::cout << "Contact(const std::string &&, const std::string &&, const std::string &&, const std::string &&) called" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Contact& obj){
        os << "Name: " << obj.m_name << std::endl << "Mobile: " << obj.mobile << std::endl << "Address: " << obj.address << std::endl << "Email: " << obj.email;
        return os;
    }
};
struct Employee{
    std::string m_name;
    int m_id;
    double m_salary;
    Contact m_contact;
    Employee(const std::string &name, int id, double salary, const Contact &contact) : m_name{name}, m_id{id}, m_salary{salary}, m_contact{contact}{
        //std::cout << "Employee(const std::string &, int, double, const Contact &) called" << std::endl;
    }
    Employee(const std::string &&name, int id, double salary, const Contact &&contact) : m_name{std::move(name)}, m_id{id}, m_salary{salary}, m_contact{std::move(contact)}{
        std::cout << "Employee(const std::string &&, int, double, const Contact &&) called" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Employee& obj){
        os << "Name: " << obj.m_name << std::endl << "ID: " << obj.m_id << std::endl << "Salary: " << obj.m_salary << std::endl << "Contact: " << obj.m_contact;
        return os;
    }
};

enum class ObjType{
    INT,
    STRING,
    EMPLOYEE,
    CONTACT
};

template<typename T>
constexpr ObjType getObjType() {
    if constexpr (std::is_same_v<T, int>) return ObjType::INT;
    else if constexpr (std::is_same_v<T, std::string>) return ObjType::STRING;
    else if constexpr (std::is_same_v<T, Employee>) return ObjType::EMPLOYEE;
    else if constexpr (std::is_same_v<T, Contact>) return ObjType::CONTACT;
    else return ObjType::INT; // default case
}

template<typename T, typename... Args>
T* createObject(Args&&... args){
    constexpr ObjType type = getObjType<T>();
    switch(type) {
        case ObjType::INT:
            if constexpr (std::is_same_v<T, int>) {
                return new int(std::forward<Args>(args)...);
            }
            break;
        case ObjType::STRING:
            if constexpr (std::is_same_v<T, std::string>) {
                return new std::string(std::forward<Args>(args)...);
            }
            break;
        case ObjType::EMPLOYEE:
            if constexpr (std::is_same_v<T, Employee>) {
                return new Employee(std::forward<Args>(args)...);
            }
            break;
        case ObjType::CONTACT:
            if constexpr (std::is_same_v<T, Contact>) {
                return new Contact(std::forward<Args>(args)...);
            }
            break;
    }
    return nullptr;
}

int main(){
    int *p1 = createObject<int>(5);
 
    std::string *s = createObject<std::string>("Hello"); //Default construction
 
    Employee *emp = createObject<Employee>("Bob", 101, 1000.0, Contact("Bob", "1234567890", "Home", "bob@email.com"));
 
    Contact *p = createObject<Contact>("Joey", "987654321", "Boulevard Road, Sgr", "joey@poash.com");

    cout << "*p1: " << *p1 << endl;
    cout << "*s: " << *s << endl;
    cout << *emp << std::endl;
    cout << *p << std::endl;

    // Clean up
    delete p1;
    delete s;
    delete emp;
    delete p;

    return 0;
}