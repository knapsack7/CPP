#include <iostream>
#include <memory>

class Employee;

class Project{
public:
    std::shared_ptr<Employee> m_emp{};
    Project(){
        std::cout<<"Project()"<< std::endl;
    }
    ~Project(){
        std::cout<<"~Project()"<< std::endl;
    }
};

class Employee{
public:
    std::weak_ptr<Project> m_prj{};
    Employee(){
        std::cout<<"Employee()"<< std::endl;
    }
    ~Employee(){
        std::cout<<"~Employee()"<< std::endl;
    }
};

int main(){
    std::shared_ptr<Employee> emp{new Employee{}};
    std::shared_ptr<Project> prj{new Project{}};
    // output shows destructor is not called
    // because of circular reference and therefore memory leak
    emp->m_prj = prj; 
    prj->m_emp = emp;
    
    return 0;
}