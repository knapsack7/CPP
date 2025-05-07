# C++ Variable Declarations Keywords: Complete Reference

## 🔹 1. decltype

- declytpe is used to query the type of an expression at compile time. THis is specially
- useful in template programming, auto declarations or type traits.

### ✅ Use Cases
- defining return types of functions when the return expression type is complex or dependent on template arguments.
- implementing perfect forwarding.

```cpp 
template<typename T, typename U>
auto add(T t, U u)  -> decltype(t + u) {
	return t + u;
}

## 🔹 2. volatile

-The volatile keyword tells the compiler not to optimize access to a variable because its value may change uncexpectedly (e.g,
- by hardware, another thread, or signal handler).

```cpp

volatile int flag = 0;
while (flag ==0 ) {
	// Do Something
}

without volatile, the compiler might optimize this into an infinite loop because it assumes flag doesn't change (no write
seen in current thread)


## 🔹 3. const


### ✅ 1. constant variables

```cpp
const int x = 10;
x = 20; // ❌ Error: cannot modify a const variable


### ✅ 2. constant pointers

```cpp Pointer to constant value(data cant change, pointer can change)
const int* ptr = &x;
*ptr = 5;     // ❌ Error
ptr = &y;     // ✅ OK


```cpp Constant Pointer to Value (data can change, pointer can't)
int* const ptr = &x;
*ptr = 5;     // ✅ OK
ptr = &y;     // ❌ Error


```cpp Constant Pointer to Constant Value
const int* const ptr = &x;
*ptr = 5;     // ❌ Error
ptr = &y;     // ❌ Error


### ✅ 3. const in fucntion parameters

```cpp Pass by Const reference tp avoid copy and ensure no modifications
void print(const std::string& str);

```cpp Const value in parameter(has no real effect)
void foo(const int x); // 'x' is copied anyway, 'const' only protects within function


### ✅ 4. const Return Type

```cpp Used to prevent modification of returned object/reference.
const std::string& getName() const {
    return name;
}


### ✅ 5. const Member Function

```cpp These functions promise not to modify the object.
class A {
    int x;
public:
    int getX() const { return x; } // Cannot modify any member inside
};


### ✅ 6. const with class Data Members

```cpp Declares immutable members. Must be initialsed via constructor initializer list.
class MyClass {
    const int value;
public:
    MyClass(int v) : value(v) {}
};


### ✅ 7. const Iterators

```cpp used to iterate over containers without modifying the elements.
std::vector<int> v{1, 2, 3};
for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it;
    // *it = 4; ❌ Error: can't modify
}









