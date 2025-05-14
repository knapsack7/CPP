# State Design Pattern

## Intent
The **State Pattern** allows an object to alter its behavior when its internal state changes. The object will appear to change its class. This is especially useful for implementing state machines in embedded systems.

## When to Use
- When an object must change its behavior at runtime depending on its state.
- When state-specific behavior is scattered across many conditional statements (e.g., `if`/`switch`), making code hard to maintain.
- When you want to encapsulate state-specific logic in separate classes.

## Why Use It?
- **Improves maintainability:** Each state is a separate class, making code easier to extend and modify.
- **Eliminates complex conditionals:** Replaces large `switch`/`if` statements with polymorphism.
- **Encapsulates state transitions:** State transitions are explicit and managed in one place.

## Embedded/Systems Example Use Cases
- Device or protocol state machines (e.g., idle, active, error, sleep).
- Communication protocol handlers (e.g., handshake, data transfer, disconnect).
- Power management (e.g., normal, low-power, shutdown states).

## Example: Device State Machine in C++

### 1. State Interface
```cpp
class DeviceState {
public:
    virtual void handle() = 0;
    virtual ~DeviceState() = default;
};
```

### 2. Concrete States
```cpp
class IdleState : public DeviceState {
public:
    void handle() override {
        std::cout << "Device is idle.\n";
    }
};

class ActiveState : public DeviceState {
public:
    void handle() override {
        std::cout << "Device is active.\n";
    }
};

class ErrorState : public DeviceState {
public:
    void handle() override {
        std::cout << "Device is in error state!\n";
    }
};
```

### 3. Context (Device)
```cpp
#include <memory>

class Device {
private:
    std::unique_ptr<DeviceState> state;
public:
    Device(std::unique_ptr<DeviceState> initialState) : state(std::move(initialState)) {}
    void setState(std::unique_ptr<DeviceState> newState) {
        state = std::move(newState);
    }
    void handle() {
        state->handle();
    }
};
```

### 4. Usage
```cpp
Device device(std::make_unique<IdleState>());
device.handle(); // Output: Device is idle.
device.setState(std::make_unique<ActiveState>());
device.handle(); // Output: Device is active.
device.setState(std::make_unique<ErrorState>());
device.handle(); // Output: Device is in error state!
```

## Summary Table
| Use State Pattern When...                   | Don't Use When...                        |
|---------------------------------------------|------------------------------------------|
| Object behavior depends on its state        | Behavior is always the same              |
| You have complex state-dependent logic      | Only a few simple states                 |
| You want to encapsulate state transitions   | State logic is trivial                   |

## Mnemonic
> "When an object's behavior should change with its state, use State!"

---

**In summary:**
The State Pattern is ideal for embedded and systems applications that require clear, maintainable, and extensible state machines, such as device modes, protocol handlers, or power management. 