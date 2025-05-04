# 📘 C++ Streams – Complete Guide

This README is a complete and beginner-to-advanced reference for **C++ Streams**, covering console I/O, file I/O, string streams, formatting, manipulators, error handling, and custom types. Ideal for quick reference or as a GitHub push.

---

## 🔹 What is a Stream?

A **stream** is an abstraction of a sequence of bytes used for input and output (I/O).  
There are different types of streams:

- `istream`: input stream (e.g., `std::cin`)
- `ostream`: output stream (e.g., `std::cout`)
- `ifstream`: input from file
- `ofstream`: output to file
- `stringstream`: I/O operations on strings

---

## 🔹 Standard Console Streams

| Stream     | Type       | Purpose                                 |
|------------|------------|------------------------------------------|
| `std::cin` | `istream`  | Reads input from keyboard                |
| `std::cout`| `ostream`  | Writes output to console (buffered)      |
| `std::cerr`| `ostream`  | Writes error messages (unbuffered)       |
| `std::clog`| `ostream`  | Writes logs/errors (buffered, no newline flush) |

### Example:
```cpp
#include <iostream>
int main() {
    int age;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cerr << "You entered age: " << age << std::endl;
    return 0;
}
```

---

## 🔹 File Streams

Header: `#include <fstream>`

| Class      | Description              |
|------------|--------------------------|
| `ifstream` | Input from file          |
| `ofstream` | Output to file           |
| `fstream`  | Input and output         |

### Write to file:
```cpp
#include <fstream>
int main() {
    std::ofstream out("data.txt");
    out << "Hello, file!";
    out.close();
}
```

### Read from file:
```cpp
#include <fstream>
#include <string>
#include <iostream>
int main() {
    std::ifstream in("data.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
}
```

---

## 🔹 String Streams

Header: `#include <sstream>`

Used to treat strings as input/output streams.

| Class             | Description                   |
|------------------|-------------------------------|
| `istringstream`  | Read from string               |
| `ostringstream`  | Write to string                |
| `stringstream`   | Read/write to string           |

### Example:
```cpp
#include <sstream>
#include <iostream>
int main() {
    std::string input = "42 John";
    std::istringstream iss(input);
    int age;
    std::string name;
    iss >> age >> name;
    std::cout << age << ", " << name << std::endl;
}
```

---

## 🔹 Stream Operators

- `>>` – Extraction (input)
- `<<` – Insertion (output)

### Example:
```cpp
int x;
std::cin >> x;               // input
std::cout << x << std::endl; // output
```

---

## 🔹 Stream Manipulators (`<iomanip>`)

| Manipulator           | Description                              |
|-----------------------|------------------------------------------|
| `std::setw(n)`        | Set width                                |
| `std::setfill(c)`     | Set fill character                       |
| `std::setprecision(n)`| Set decimal precision                    |
| `std::fixed`          | Fixed-point float notation               |
| `std::scientific`     | Scientific notation                      |
| `std::boolalpha`      | Print bools as "true"/"false"            |
| `std::noboolalpha`    | Print bools as 1/0 (default)             |
| `std::left`           | Left align                               |
| `std::right`          | Right align                              |

### Example:
```cpp
#include <iostream>
#include <iomanip>
int main() {
    std::cout << std::setw(5) << 42 << std::endl;               // "   42"
    std::cout << std::setfill('0') << std::setw(5) << 42 << std::endl; // "00042"
    std::cout << std::fixed << std::setprecision(2) << 3.14159 << std::endl; // "3.14"
    std::cout << std::boolalpha << true << std::endl; // "true"
}
```

---

## 🔹 Error Handling with Streams

Use these methods to check stream state:

| Method     | Meaning                                |
|------------|----------------------------------------|
| `.good()`  | Stream is OK                           |
| `.fail()`  | Logical error (e.g., type mismatch)    |
| `.eof()`   | End of file reached                    |
| `.bad()`   | Read/write error                       |
| `.clear()` | Clears all error flags                 |

### Example:
```cpp
int x;
std::cin >> x;
if (std::cin.fail()) {
    std::cerr << "Invalid input!" << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n'); // clear bad input
}
```

---

## 🔹 Custom `<<` / `>>` Operators for User Types

### Example:
```cpp
class Point {
public:
    int x, y;
    Point(int x, int y): x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
```

```cpp
Point p(1, 2);
std::cout << p << std::endl;  // Output: (1, 2)
```

---

## ✅ Summary Table

| Topic           | Key Classes/Functions                       |
|------------------|---------------------------------------------|
| Console I/O      | `std::cin`, `std::cout`, `std::cerr`        |
| File I/O         | `ifstream`, `ofstream`, `fstream`           |
| String Streams   | `istringstream`, `ostringstream`, `stringstream` |
| Formatting       | `setw`, `setfill`, `fixed`, `setprecision`  |
| Error Handling   | `fail()`, `eof()`, `clear()`                |
| Custom Types     | Overload `<<`, `>>`                         |

---

## 📂 Headers to Include

| Header        | Purpose                     |
|---------------|-----------------------------|
| `<iostream>`  | Console I/O                 |
| `<fstream>`   | File stream I/O             |
| `<sstream>`   | String streams              |
| `<iomanip>`   | Formatting manipulators     |

---

## 📎 Best Practices

- Always close file streams after use (`.close()`).
- Check `.fail()` after reading sensitive input.
- Use `std::getline()` for full-line input.
- Use `ostringstream` to build formatted strings.
- Overload `<<` for logging custom objects.
- Chain manipulators for cleaner formatting.

---

## 🧠 Tips

- Use `std::boolalpha` to make boolean prints readable.
- `std::setw()` is only for next value—not persistent.
- You can combine multiple manipulators:
```cpp
std::ostringstream oss;
oss << std::setw(6) << std::setfill('*') << 42; // Output: ****42
```

---
