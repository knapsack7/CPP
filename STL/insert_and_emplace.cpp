#include <iostream>
#include <set>
#include <string>
using namespace std;
/*
	•	emplace() is available in both associative and sequence containers.
	•	It lets you construct objects directly inside the container, saving time and memory.
	•	Especially useful for containers of user-defined classes.
*/
class Person {
public:
    string name;
    int age;

    Person(string name, int age) : name(name), age(age) {
        cout << "Constructor called for " << name << endl;
    }

    Person(const Person& other) {
        cout << "Copy constructor called for " << other.name << endl;
        name = other.name;
        age = other.age;
    }

    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

int main() {
    cout << "=== Using insert() ===" << endl;
    set<Person> s1;
    Person p1("Alice", 30);     // Constructor called
    s1.insert(p1);              // Copy constructor called

    cout << "\n=== Using emplace() ===" << endl;
    set<Person> s2;
    s2.emplace("Bob", 25);      // Only Constructor called, do not use {}. 

    return 0;
}