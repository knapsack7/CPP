# Factory Pattern

## Intent
The **Factory Pattern** provides an interface for creating objects, allowing subclasses or configuration to decide which class to instantiate. It decouples object creation from usage, making code more flexible and maintainable.

## When to Use
- When you need to create objects of several related classes, but don't know which one until runtime.
- When you want to encapsulate object creation logic in one place.
- When you want to decouple client code from concrete classes.

## Why Use It?
- **Centralizes object creation** logic, making it easier to manage and extend.
- **Promotes loose coupling**: client code depends only on interfaces, not concrete implementations.
- **Easier to add new types**: add new classes without changing client code.

## Embedded/Systems Example Use Cases
- Creating different sensor drivers (e.g., temperature, pressure) based on configuration or hardware detection.
- Instantiating different communication protocol handlers (UART, SPI, I2C).
- Selecting different storage backends (SD card, EEPROM, Flash) at runtime.

## Example: Sensor Factory in C++

### 1. Base Interface
```cpp
class Sensor {
public:
    virtual void read() = 0;
    virtual ~Sensor() = default;
};
```

### 2. Concrete Implementations
```cpp
class TemperatureSensor : public Sensor {
public:
    void read() override { std::cout << "Reading temperature\n"; }
};

class PressureSensor : public Sensor {
public:
    void read() override { std::cout << "Reading pressure\n"; }
};
```

### 3. Factory Class
```cpp
#include <memory>
#include <string>

class SensorFactory {
public:
    static std::unique_ptr<Sensor> createSensor(const std::string& type) {
        if (type == "temperature")
            return std::make_unique<TemperatureSensor>();
        else if (type == "pressure")
            return std::make_unique<PressureSensor>();
        else
            return nullptr;
    }
};
```

### 4. Usage
```cpp
auto sensor = SensorFactory::createSensor("temperature");
if (sensor) {
    sensor->read(); // Output: Reading temperature
}
```

## Summary Table
| Use Factory Pattern When...                | Don't Use When...                        |
|--------------------------------------------|------------------------------------------|
| You need to create objects of many types   | Only one type of object is ever created  |
| Object type is decided at runtime          | Object type is always known at compile time |
| You want to centralize creation logic      | Creation logic is trivial                |

## Mnemonic
> "When you want to make objects, but don't want to say exactly which kind."

---

**In summary:**
The Factory Pattern is a powerful tool for embedded and systems engineers to manage object creation flexibly and cleanly, especially when dealing with multiple hardware variants or runtime configuration. 