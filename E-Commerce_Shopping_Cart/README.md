# E-Commerce Shopping Cart System

## Overview
This project demonstrates a simple e-commerce shopping cart system implemented in C++. It utilizes various design patterns and adheres to SOLID principles.

## Features
- Product Management (adding electronic items and clothing)
- Shopping Cart functionality
- Discount Management using different strategies
- Checkout process

## Design Patterns Used
- **Factory Pattern**: Implicitly used by creating different product types (Electronics, Clothing).
- **Strategy Pattern**: Applied for different discount strategies (Percentage and Fixed Amount discounts).
- **Observer Pattern**: Not implemented here but can be added for notifications.
- **Decorator Pattern**: Not implemented but could be used for adding features to products.

## SOLID Principles Applied
- **Single Responsibility Principle**: Each class has a single responsibility.
- **Open/Closed Principle**: New product types and discount strategies can be added without modifying existing code.
- **Liskov Substitution Principle**: Subtypes of products and discounts can be used interchangeably.
- **Interface Segregation Principle**: Interfaces are specific to client needs.
- **Dependency Inversion Principle**: High-level modules depend on abstractions (DiscountStrategy).

## How to Run
1. Compile the project using a C++ compiler (e.g., g++).
make
2. Run the resulting executable.
./Shopping Cart