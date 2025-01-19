#include<iostream>
#include<string>
#include<memory>

//Step 1: Define the Car Product
class Car{
private:
    std::string engine;
    std::string body;
    int wheels;
    bool hasSunroof;

public:
    //Setter for configuring the Car
    void setEngine(const std::string& engineType){engine = engineType;}
    void setBody(const std::string& bodyType){body = bodyType;}
    void setWheels(int numberOfWheels) { wheels = numberOfWheels; }
    void setSunroof(bool sunroof) { hasSunroof = sunroof; }

    // Display the car's details
    void showDetails() const {
        std::cout << "Car Details:\n";
        std::cout << "Engine: " << engine << "\n";
        std::cout << "Body: " << body << "\n";
        std::cout << "Wheels: " << wheels << "\n";
        std::cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << "\n";
    }
};

//step 2: Define the Abstract Builder

class CarBuilder{
public:
    virtual ~CarBuilder() = default;
    virtual void buildEngine() = 0;
    virtual void buildBody() = 0;
    virtual void buildWheels() = 0;
    virtual void buildSunroof() = 0;
    virtual std::shared_ptr<Car> getCar() = 0;
};

//step3: Create Concrete Builders
class SportsCarBuilder : public CarBuilder{
private:
    std::shared_ptr<Car> car;
public:
    SportsCarBuilder() {car = std::make_shared<Car>();}
    void buildEngine() override {car->setEngine("V8 Engine");}
    void buildBody() override {car->setBody("Sports Body");}
    void buildWheels() override { car->setWheels(4); }
    void buildSunroof() override { car->setSunroof(true); }
    std::shared_ptr<Car> getCar() override { return car;}
};

class SUVCarBuilder : public CarBuilder {
private:
    std::shared_ptr<Car> car;

public:
    SUVCarBuilder() { car = std::make_shared<Car>(); }
    void buildEngine() override { car->setEngine("V6 Engine"); }
    void buildBody() override { car->setBody("SUV Body"); }
    void buildWheels() override { car->setWheels(4); }
    void buildSunroof() override { car->setSunroof(false); }
    std::shared_ptr<Car> getCar() override { return car; }
};

//Step 4: Define the Director
class Director{
private:
    CarBuilder* builder;
public:
    void setBuilder(CarBuilder* newBuilder){builder = newBuilder;}
    std::shared_ptr<Car> constructCar() {
        builder->buildEngine();
        builder->buildBody();
        builder->buildWheels();
        builder->buildSunroof();
        return builder->getCar();
    }
};


class SedanBuilder : public CarBuilder{
private:
    std::shared_ptr<Car> car;
public:
    SedanBuilder(){car = std::make_shared<Car>();}
    void buildEngine() override{car->setEngine("CNG Engine");}
    void buildBody() override{car->setBody("streamline Body");}
    void buildWheels() override { car->setWheels(4); }
    void buildSunroof() override { car->setSunroof(false); }
    std::shared_ptr<Car> getCar() override{return car;}
};

int main(){
    Director director;
    
    //Build a sports Car
    SportsCarBuilder sportsCarBuilder;
    director.setBuilder(&sportsCarBuilder);
    std::shared_ptr<Car> sportsCar = director.constructCar();
    sportsCar->showDetails();

    std::cout<<"\n";

    //Build a SUV
    SUVCarBuilder suvCarBuilder;
    director.setBuilder(&suvCarBuilder);
    std::shared_ptr<Car> suvCar = director.constructCar();
    suvCar->showDetails();

    std::cout<<std::endl;

    //Build Sedan 
    SedanBuilder sedanBuilder;
    director.setBuilder(&sedanBuilder);
    std::shared_ptr<Car> sedanCar = director.constructCar();
    sedanCar->showDetails();
    return 0;
}