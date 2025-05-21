#include <iostream>

using namespace std;



class Organism{
    public:
        virtual void liveSpan() = 0;
        virtual ~Organism() = default;
};

class Animal: public Organism{
    public:     
        void liveSpan() override{
            cout << "Animal lives for 200 years" << endl;
        }
};

class Human: public Animal{
    public:
        void liveSpan() override{
            cout << "Human lives for 80 years" << endl;
        }
};

class Dog: public Animal{
    public:
        void liveSpan() override{
            cout << "Dog lives for 15 years" << endl;
        }
}; 

class God{
    public:
        God() = default;
        void liveSpanDisplay(Organism* animal){
            animal->liveSpan();
        }
    //If return type was Animal or other class, this wont be able to return 
    // super class referrence hence God wont be able to create all organisms.
    // basic principle of Liskov Substitution Principle is that 
    // if we return any object, we should only assign it to super class referrence

    // so in main if there was some reference trying to hold the return value of this function
    // it would only be able to hold the referrence of the return type if it was super or same class holder 
    // in main class
    
    Organism* createOrganism(string type){
        if(type == "Animal"){
            return new Animal();
        }
        else if(type == "Human"){
            return new Human();
        }
        else if(type == "Dog"){
            return new Dog();
        }
        else{
            return nullptr;
        }
    }
};



int main(){
    God* god = new God();

    
    
    Organism* organism = god->createOrganism("Animal");
    god->liveSpanDisplay(organism);
    delete organism;

    organism = god->createOrganism("Human");
    god->liveSpanDisplay(organism);
    delete organism;
       
    delete god;

    return 0;   
}
