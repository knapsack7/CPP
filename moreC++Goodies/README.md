# C++ Enums: Complete Reference

This README provides an overview of **enumerations (`enum`) in C++**, with examples and explanations.

---

## 🔹 1. Unscoped vs Scoped Enums

### ✅ Unscoped Enum (Classic C Style)
```cpp
enum Color { RED, GREEN, BLUE };
Color c = RED;  // Implicitly converts to int

- No enum prefix needed when using enumerators.
- implicit conversion to int allowed(can cause conflicts)
- Suitable for backward compatibility or small enums.


### ✅ Scoped Enum (enum class- C++11++)
```cpp
enum class Status { OK, ERROR, TIMEOUT };
Status s = Status::OK;

- Enumerators are scoped to the enum type
- prevents name pollution
- No implicits conversion to int (type-safe)

## 🔹 2. Underlying Type of Enums

### ✅ Default (UnScoped:usually int)

```cpp
enum Priority {LOW, MEDIUM, HIGH}; // underlying type : int

### Explicitly Specified

```cpp
enum class ErrorCode : unint8_t {NONE = 0, FATAL : 255};

- helps control memory layout
- Mandatory when forward-declaring an unscoped enum


## 🔹 3. Forward Declartation (Opaque Enums)

### ✅ Scoped Enum(C++11++)
```cpp
enum class Direction : int;  // Forward declaration
// Later definition
enum class Direction : int { NORTH, SOUTH, EAST, WEST };

- only allowed with scoped enums or unscoped enums with underlying type


## 🔹 4. Elaborated type specifier
```cpp
enum Color { RED, GREEN };
void print(enum Color c);  // Using elaborated type specifier

- helps disambiguate enum names when hidden by other declarations
- cannot be used to forward-declare an enum


## 🔹 5. Notes
- You cannot redeclare a scoped enum as unscoped or vice-versa
- All declarations of the same enum must use the same underlying type.
- enum class improves type safety and namespace hygiene.



