#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Teachable {
public:
    virtual void teach() = 0;
    virtual string getName() = 0;
    virtual ~Teachable() = default; // must destructor
};


class Professor : public Teachable {
private:
    string name;
    string subject;
public:
    Professor (string name, string subject) : name(name), subject(subject){}
    void teach() override {
        cout << name << " is teaching " << subject << endl;
    }
    string getName() override {return name;}
};

class University {
private:
    string universityName;
    vector<unique_ptr<Teachable>> professors;
public:
    University(string name) : universityName(name) {}
    
    void addProfessor(unique_ptr<Teachable> professor) {
        professors.push_back(std::move(professor));
    }
    
    void showProfessors() {
        cout << "Professors at " << universityName << ":" << endl;
        for (unique_ptr<Teachable> &professor : professors) {
            professor->teach();
        }
    }
};

int main() {
    unique_ptr<Teachable> prof1 = make_unique<Professor>("Dr. Adams", "Physics");
    unique_ptr<Teachable> prof2 = make_unique<Professor>("Dr. Lee", "Chemistry");
    

    unique_ptr<University> university = make_unique<University>("MIT");
    university->addProfessor(std::move(prof1));
    university->addProfessor(std::move(prof2));
    
    university->showProfessors();
    
    return 0;
}
