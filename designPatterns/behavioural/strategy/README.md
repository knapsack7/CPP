# Strategy Pattern in C++

## Overview
The Strategy Pattern is a behavioral design pattern that enables dynamic selection of algorithms at runtime. It promotes flexibility and reusability by defining a family of algorithms, encapsulating each one, and making them interchangeable.

---

## Key Components

### 1. Context
- Holds a reference to a strategy object.
- Delegates algorithm execution to the current strategy.

### 2. Strategy Interface
- Defines a common interface for all supported algorithms.

### 3. Concrete Strategies
- Implement specific algorithms or behaviors defined by the Strategy Interface.

---

## Advantages
1. **Adherence to Open/Closed Principle**: Enables adding new strategies without modifying existing code.
2. **Eliminates Conditional Logic**: Avoids complex `if-else` or `switch` statements by delegating behavior to strategy objects.
3. **Reusability and Flexibility**: Strategies can be reused across different contexts.

---

## Disadvantages
1. **Complexity Overhead**: Increases the number of classes in the application.
2. **Requires Context Awareness**: The client must know about different strategies to select the appropriate one.
3. **Maintenance**: Managing multiple strategies can be challenging in large systems.

---

## Example Use Case
Imagine an online payment system that supports multiple payment methods such as:
- Credit Card
- PayPal
- Bitcoin

Using the Strategy Pattern, the payment method can be dynamically selected at runtime without modifying the core payment processing logic.

---

## How to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```

2. Navigate to the project directory:
   ```bash
   cd strategy-pattern-cpp
   ```

3. Compile the code:
   ```bash
   g++ -std=c++17 -o strategy_pattern main.cpp
   ```

4. Run the executable:
   ```bash
   ./strategy_pattern
   ```

---

## Example Output
```
Paid 100 using Credit Card.
Paid 100 using PayPal.
Paid 100 using Bitcoin.
```

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
