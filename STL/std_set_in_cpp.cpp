#include<iostream>
#include<set>
using namespace std;


class Person{
    public:
        float age;
        string name;
    bool operator < (const Person& p) const{
        return age < p.age;
    }
    bool operator > (const Person& p) const{
        return age > p.age;
    }
};


int main(){
    set<Person> set1 = {{30, "manoj"}, {25, "manish"}};
    for(auto const& e : set1){
        cout<<e.age<<"--"<<e.name<<endl;
    }
    set<Person, std::greater<>> set2 = {{30, "ashish"}, {35, "ajay"}};
    for(auto const& e : set2){
        cout<<e.age<<"--"<<e.name<<endl;
    }
    return 0;
}