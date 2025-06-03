# Online Food Ordering System

A robust and scalable C++ implementation of an online food ordering system that follows Object-Oriented Design principles and design patterns.

## 🏗️ Project Structure

The project follows a clean architecture with clear separation of concerns:

```
OnlineFoodOrderingSystem/
├── main.cpp                    # Entry point and composition root
├── TomatoApp.h                # Main facade class
├── models/                    # Core domain entities
├── managers/                  # Business logic managers
├── strategies/               # Strategy pattern implementations
├── factories/                # Factory pattern implementations
├── services/                 # Cross-cutting services
└── utils/                    # Utility functions
```

## 🎯 Key Features

- Restaurant management and menu handling
- User authentication and profile management
- Shopping cart functionality
- Multiple order types (Delivery and Pickup)
- Flexible payment strategies (Credit Card, UPI)
- Order scheduling capabilities
- Notification system

## 🏛️ Architecture

### Core Components

1. **Models**
   - `MenuItem`: Represents food items in the menu
   - `Restaurant`: Restaurant details and menu
   - `User`: User profile and preferences
   - `Cart`: Shopping cart management
   - `Order`: Abstract base class for orders
   - `DeliveryOrder`: Delivery-specific order implementation
   - `PickupOrder`: Pickup-specific order implementation

2. **Managers**
   - `RestaurantManager`: Handles restaurant operations
   - `OrderManager`: Manages order processing and tracking

3. **Strategies**
   - `PaymentStrategy`: Abstract payment strategy
   - `CreditCardPaymentStrategy`: Credit card payment implementation
   - `UpiPaymentStrategy`: UPI payment implementation

4. **Factories**
   - `OrderFactory`: Abstract factory for order creation
   - `NowOrderFactory`: Factory for immediate orders
   - `ScheduledOrderFactory`: Factory for scheduled orders

5. **Services**
   - `NotificationService`: Handles user notifications

6. **Utils**
   - `TimeUtils`: Time-related utility functions

## 🛠️ Design Patterns Used

1. **Facade Pattern**
   - `TomatoApp` class provides a simplified interface to the complex subsystem

2. **Strategy Pattern**
   - Payment processing with different payment methods

3. **Factory Pattern**
   - Order creation with different types (Now/Scheduled)

4. **Abstract Factory Pattern**
   - Creation of related order objects

## 🚀 Getting Started

### Prerequisites

- C++17 or higher
- CMake (for building)

### Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

### Running the Application

```bash
./OnlineFoodOrderingSystem
```

## 📝 Usage Example

```cpp
#include "TomatoApp.h"

int main() {
    TomatoApp app;
    
    // Initialize the application
    app.initialize();
    
    // Start processing orders
    app.start();
    
    return 0;
}
```


## 📄 License

This project is licensed under CoderArmy  - see the LICENSE file for details.

## 👥 Authors

- Coder Army

## 🙏 Acknowledgments

- Thanks to CoderArmy for your system design tutorial series
- Inspired by real-world food delivery applications 