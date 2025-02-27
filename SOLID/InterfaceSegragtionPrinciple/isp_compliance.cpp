/*
We split the large interface into multiple smaller interfaces, so that each class implements only what it needs.
*/

#include <iostream>
using namespace std;

// ✅ GOOD: Separate interfaces for different responsibilities
class IWorkable {
public:
    virtual void work() = 0;
    virtual ~IWorkable() {}
};

class IEatable {
public:
    virtual void eat() = 0;
    virtual ~IEatable() {}
};

// ✅ Human implements both Work and Eat interfaces
class HumanWorker : public IWorkable, public IEatable {
public:
    void work() override {
        cout << "Human is working." << endl;
    }

    void eat() override {
        cout << "Human is eating." << endl;
    }
};

// ✅ Robot only implements Work interface (no need for Eat)
class RobotWorker : public IWorkable {
public:
    void work() override {
        cout << "Robot is working." << endl;
    }
};

int main() {
    HumanWorker human;
    RobotWorker robot;

    human.work();
    human.eat();  // ✅ Only humans need to eat

    robot.work();  // ✅ Robot only works, no unnecessary method

    return 0;
}

/*🔥 Key Benefits of Using ISP

✅ No forced dependencies – Classes only implement what they need.
✅ Better scalability – We can extend functionality without modifying existing classes.
✅ Improved maintainability – Smaller interfaces are easier to manage and understand.
*/