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
        void liveSpanDisplay(Animal* animal){
            animal->liveSpan();
        }
};



int main(){
    God* god = new God();

    Animal* animal = new Animal();
    god->liveSpanDisplay(animal);
    delete animal;

    Human* human = new Human();
    god->liveSpanDisplay(human);
    delete human;

    Dog* dog = new Dog();
    god->liveSpanDisplay(dog);
    delete dog;
    
    //This violates LSP rule as
    //we can only pass argument of same class or subtype class
    // since only same class or super class can hold the referrence of subtype class
    //god->liveSpanDisplay(new Organism());
    delete god;
    return 0;   
}
