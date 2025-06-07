#include "integer.h"
#include <iostream>
#include <memory>

#include <string>

class Project{
    std::string m_name;
public:
    void setName(const std::string& name){
        m_name = name;
    }
    std::string getName() const{
        return m_name;
    }
    void showProjectDetails() const {
        std::cout << "Project Name : " << m_name << std::endl;
    }
};

class Employee{
    std::shared_ptr<Project> m_project{};
public:
    void setProject(const std::shared_ptr<Project> &prj){
        m_project = prj;
    }
    const std::shared_ptr<Project>& getProject() const{
        return m_project;
    }
    void showEmployeeDetails(){
        std::cout << "Employee is working on " << m_project->getName() << std::endl;
    }
};

void showProjectDetails(std::shared_ptr<Project> p){
    p->showProjectDetails();
}


void showInfo(std::shared_ptr<Employee> &emp){
    std::cout<<"Employee project details : \n ";
    emp->getProject()->showProjectDetails();
}

int main(){
    std::shared_ptr<Project> prj{new Project{}};
    prj->setName("Video Decoder");
    std::shared_ptr<Employee> e1{new Employee{}};
    e1->setProject(prj);
    std::shared_ptr<Employee> e2{new Employee{}};
    e2->setProject(prj);
    std::shared_ptr<Employee> e3{new Employee{}};
    e3->setProject(prj);
    e3.reset();
    showInfo(e1);
    showInfo(e2);
    prj->showProjectDetails();
    std::cout<<"Number of employees working on the project : " << prj.use_count() << std::endl;

    return 0;
}