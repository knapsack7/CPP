#include <iostream>

struct GameObject {
//    GameObject() { std::cout << "Created a " << getType() << "\n"; }
    void render() const { std::cout << "Rendered a " << getType() << "\n"; }
    virtual std::string getType() const = 0;
};

class Spaceship : public GameObject {
    std::string getType() const override { return "Spaceship"; }
};

void display(const GameObject &gameObject) { gameObject.render(); }

int main() {
    Spaceship spaceship;
    display(spaceship);
}