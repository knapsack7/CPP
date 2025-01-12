#include <iostream>

class GameObject {
  public:
    GameObject() : GameObject("GameObject"){}
  protected:
    GameObject(std::string_view type) {
        std::cout << "Created a " << type << "\n";
    }
  public:
    void render() const { std::cout << "Rendered a " << getType() << "\n"; }

  protected:
    virtual std::string getType() const { return "GameObject"; }
};

class Spaceship : public GameObject {
  public:
    Spaceship() : GameObject("Spaceship"){}
  private:
    std::string getType() const override { return typeName; }
    static constexpr auto typeName = "Spaceship";
};

void display(const GameObject &gameObject) { gameObject.render(); }

int main() {
    GameObject gameObject;
    Spaceship spaceship;
    display(gameObject);
    display(spaceship);
}
