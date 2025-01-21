# Observer Pattern in C++

## Overview
The Observer Pattern is a behavioral design pattern that defines a one-to-many dependency between objects. When the state of one object (the Subject) changes, all its dependent objects (Observers) are notified and updated automatically.

---

## Key Components

### 1. Subject
- Maintains a list of observers and provides methods to add, remove, and notify observers.

### 2. Observer
- An interface that defines the update method, which is called by the Subject when its state changes.

### 3. Concrete Subject
- A specific implementation of the Subject. It stores the state and notifies observers when the state changes.

### 4. Concrete Observer
- Implements the Observer interface and updates itself based on the Subject's state.

---

## Advantages
1. **Loose Coupling**: Observers and Subjects are loosely coupled, improving flexibility and reusability.
2. **Automatic Updates**: Observers are automatically notified of state changes.
3. **Dynamic Relationships**: Observers can be added or removed at runtime.

---

## Disadvantages
1. **Performance Overhead**: Notifying a large number of observers can be resource-intensive.
2. **Order of Notification**: Observers are notified in an arbitrary order, which might lead to issues in some cases.
3. **Memory Leaks**: Observers must be properly removed to avoid memory leaks, especially in languages without garbage collection.

---

## Example Use Case
Consider a stock market application where multiple clients (observers) need to be notified whenever a stock price (subject) changes.

---

## How to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>