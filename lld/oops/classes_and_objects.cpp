#include<iostream>
#include<memory>
using namespace std;

class Car {
private:
    string color;
    string make;
    string model;
    int year;

public:
    Car(string color, string make, string model, int year){
        this->color = color;
        this->make = make;
        this->model = model;
        this->year = year;
    }

    void displayInfo() {
        cout << "Car Make : " << make << endl;
        cout << "Car Model :" << model << endl;
        cout << "Car Year :  " << year << endl;
        cout << "Car Color : " << color << endl;
    }
};

int main() {
    unique_ptr<Car> car1 = make_unique<Car>("Red", "Toyota", "Corolla", 2020);
    unique_ptr<Car> car2 = make_unique<Car>("Blue", "Ford", "Mustang", 2021);
    car1->displayInfo();
    cout<<"-------\n";
    car2->displayInfo();
    return 0;
}