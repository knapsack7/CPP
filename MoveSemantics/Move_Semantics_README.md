
# 📦 Move Semantics in Modern C++

## 🔹 What Are Move Semantics?

Move semantics allow the resources of one object to be **transferred** to another, **without copying**. Introduced in C++11, this optimizes performance, especially when dealing with large or non-trivially copyable objects like `std::vector`, `std::string`, etc.

---

## 🔸 Key Concepts

### ✅ Lvalue vs Rvalue
| Type      | Meaning                            | Example            |
|-----------|-------------------------------------|--------------------|
| Lvalue    | Named object, addressable           | `int a = 10;`      |
| Rvalue    | Temporary, not addressable          | `int b = a + 5;`   |

---

### ✅ Reference Types

| Reference Type  | Syntax   | Binds To         | Use Case                        |
|-----------------|----------|------------------|----------------------------------|
| Lvalue Reference| `T&`     | Lvalues          | Access or modify existing object |
| Rvalue Reference| `T&&`    | Rvalues          | Implement move semantics         |

---

## 🔸 Why Move Instead of Copy?

| Operation | RAM Used           | Speed         | Behavior                       |
|-----------|--------------------|---------------|--------------------------------|
| Copy      | Allocates new RAM  | Slower (O(n)) | Deep copy of all data          |
| Move      | Reuses RAM         | Fast (O(1))   | Transfers ownership (pointer swap) |

### Example:
```cpp
std::string a = "hello";
std::string b = std::move(a); // Moves internal buffer to b
```
- `a` becomes empty or unspecified
- `b` now owns the original buffer (heap data)

---

## 🔸 Move Constructor & Move Assignment

```cpp
class MyClass {
    int* data;

public:
    // Move constructor
    MyClass(MyClass&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    // Move assignment
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyClass() {
        delete[] data;
    }
};
```

---

## 🔸 `std::move`

`std::move()` **casts an object to an rvalue**, allowing it to bind to an `T&&` parameter and trigger move semantics.

```cpp
std::string a = "abc";
std::string b = std::move(a); // invokes move constructor
```

---

## 🔸 Does Move Change Memory Section (Stack/Heap)?

❌ **No.** Move semantics:
- **Do not relocate the object** in memory
- Only **transfer ownership of heap-allocated resources**
- The object itself stays on the stack or heap as originally declared

```cpp
std::string a = "hi";          // on stack
std::string b = std::move(a);  // also on stack
```

---

## 🔸 `std::thread` and `std::move`

Since `std::thread` is **non-copyable but movable**, moving is required to:
- Pass thread ownership
- Return a thread
- Store threads in containers

```cpp
std::thread t1(func);
std::thread t2 = std::move(t1); // t1 is now non-joinable
```

---

|--------------------| <- High address
|     Stack          | <-- local variables
|--------------------|
|     Heap           | <-- dynamic memory (new, malloc)
|--------------------|
|   BSS / Data       | <-- globals/static vars
|--------------------|
|     Text (code)    |
|--------------------| <- Low address


## 🔸 Best Practices

- Use `std::move` only **once you're done using** the original object.
- Always implement **move constructors and move assignment operators** for classes that manage resources.
- After a move, **do not rely on the state** of the moved-from object unless documented.

---

## 📘 Further Reading

- [C++ Reference – std::move](https://en.cppreference.com/w/cpp/utility/move)
- [Move Semantics FAQ – Herb Sutter](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointers/)
