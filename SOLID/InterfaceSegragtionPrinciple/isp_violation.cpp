/*
Interface Segregation Principle (ISP) in C++

📌 Principle Definition:

	Clients should not be forced to depend on interfaces they do not use.

This means that instead of creating one large interface with multiple unrelated functionalities,
we should create smaller, specific interfaces that provide only the required methods for each class.

*/

/*
🚨 Violation of ISP (Bad Example)

Here, we create a 
huge interface IWorker that forces all workers (both humans and robots) to implement unnecessary methods.
*/


#include <iostream>
using namespace std;

// ❌ BAD: One big interface with unrelated responsibilities
class IWorker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;  // Robots don't eat! Why force them?
    virtual ~IWorker() {}
};

// Concrete class for a Human Worker
class HumanWorker : public IWorker {
public:
    void work() override {
        cout << "Human is working." << endl;
    }

    void eat() override {  // Makes sense for humans
        cout << "Human is eating." << endl;
    }
};

// Concrete class for a Robot Worker
class RobotWorker : public IWorker {
public:
    void work() override {
        cout << "Robot is working." << endl;
    }

    void eat() override {  // ❌ Bad! Robots don’t eat, but must implement this!
        cout << "Robot does not need to eat!" << endl;
    }
};

int main() {
    HumanWorker human;
    RobotWorker robot;

    human.work();
    human.eat();

    robot.work();
    robot.eat();  // ❌ Unnecessary method for robots

    return 0;
}  

/*
🔴 Problems in this approach:
	1.	Forces unrelated functionality – RobotWorker is forced to implement eat(), which makes no sense.
	2.	Violates SRP (Single Responsibility Principle) – IWorker has multiple responsibilities (both working and eating).
	3.	Not scalable – What if we need a FlyingRobotWorker? Should it implement fly() too?
*/