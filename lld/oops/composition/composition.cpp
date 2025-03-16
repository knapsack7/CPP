#include <iostream>
#include <memory>
using namespace std;

class Engine {
public:
    virtual void start() = 0; // Pure virtual function
    virtual ~Engine() = default;
};

class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "Petrol Engine started." << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel Engine started." << endl;
    }
};

class Car {
private:
    unique_ptr<Engine> engine;
public:
    Car(unique_ptr<Engine> e) : engine(std::move(e)) {}
    void startCar() {
        engine->start();
        cout << "Car is ready to go!" << endl;
    }
};

int main() {
    unique_ptr<PetrolEngine> petrolEngine = make_unique<PetrolEngine>();
    unique_ptr<DieselEngine> dieselEngine = make_unique<DieselEngine>();
    
    Car petrolCar(std::move(petrolEngine));
    petrolCar.startCar();
    
    Car dieselCar(std::move(dieselEngine));
    dieselCar.startCar();
    
    return 0;
}