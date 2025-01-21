#include <iostream>
#include <vector>
#include <string>

// Observer Interface
class Observer {
public:
    virtual void update(int state) = 0;
    virtual ~Observer() = default;
};

// Subject Interface
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

// Concrete Subject
class ConcreteSubject : public Subject {
private:
    std::vector<Observer*> observers;
    int state;

public:
    void setState(int newState) {
        state = newState;
        notify();
    }

    int getState() const {
        return state;
    }

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(state);
        }
    }
};

// Concrete Observer
class ConcreteObserver : public Observer {
private:
    std::string name;
    ConcreteSubject& subject;

public:
    ConcreteObserver(const std::string& name, ConcreteSubject& subject) : name(name), subject(subject) {}

    void update(int state) override {
        std::cout << name << ": Received update with new state: " << state << std::endl;
    }
};

// Example Usage
int main() {
    ConcreteSubject subject;

    ConcreteObserver observer1("Observer 1", subject);
    ConcreteObserver observer2("Observer 2", subject);

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setState(10);
    subject.setState(20);

    subject.detach(&observer1);
    subject.setState(30);

    return 0;
}

