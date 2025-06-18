#include <iostream>
#include <variant>
#include <string>
using namespace std;

/*
 * Std::variant
 * std::variant is a type-safe replacement for union type
 * just like union, it uses the storage of the largest type
 * The first member is always default initialized if 
 * variant is default constructed
 * Alrternatively, you can intialize any member of the variant
 * during construction
 * Members are destroyed properly
 * Throws std::bad_variant_access on invalid access
 */

struct  Number{
    int value; // data member to store the number
    Number(int num) : value(num) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number() : value(0) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Number(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number(const Number & other) : value(other.value) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number(Number && other) noexcept : value(other.value) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number & operator=(const Number & other){
        std::cout<<__PRETTY_FUNCTION__ << std::endl;
        if (this == &other){
            return *this;
        }
        value = other.value;
        return *this;
    }
    Number & operator=(Number && other) noexcept{
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (this == &other){
            return *this;
        }
        value = other.value;
        return *this;
    }
    friend std::ostream & operator<<(std::ostream & os, const Number & num){
        os << num.value;
        return os;
    }
};

class Visitor{
public:
    void operator()(const std::string & str) const{
        std::cout << "String: " << str << std::endl;
    }
    void operator()(const int & num) const{
        std::cout << "Int: " << num << std::endl;
    }
    void operator()(const Number & num) const{
        std::cout << "Number: " << num << std::endl;
    }
};

class Modifier{
public:
    // rightmost const ensures that it does not modify the
    // data member of the Modifier class
    void operator()(std::string & str) const{
        str += " is a programming language";
    }
    void operator()(int & num) const{
        num += 1000;
    }
    void operator()(Number & num) const{
        num = 1000;
    }
};


int main(){
    try{
        std::variant<std::string, int, Number> v{7};

        // std::visit(Visitor{}, v);
        // v = "C++";
        // std::visit(Modifier{}, v);
        // std::visit(Visitor{}, v);
        
        // v.emplace<Number>(10);
        // std::visit(Modifier{}, v);
        // std::visit(Visitor{}, v);

        v = "using lambda";

        // decltype(x) gives the exact type of x (could be reference, const, etc.)
        // std::decay_t removes references and cv-qualifiers (like const/volatile) from decltype(x),
        // so T becomes the plain type (e.g., std::string, int, Number) for type comparisons
        auto visitor = [](auto &x){
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::string>){
                std::cout << "String: " << x << std::endl;
            }
            else if constexpr (std::is_same_v<T, int>){
                std::cout << "Int: " << x << std::endl;
            }   
            else if constexpr (std::is_same_v<T, Number>){
                std::cout << "Number: " << x << std::endl;
            }
        };
        // std::visit takes a callable (visitor) as the first argument and one or more std::variant objects as the next arguments.
        // It calls the visitor with the currently held value(s) from the variant(s).
        std::visit(visitor, v);
        
        v = 555;

        std::visit(visitor, v);

        v = Number{444};

        std::visit(visitor, v);

        //v = Number{10}; // assigning new value to the variant
        // emplace constructs the object in-place, avoiding unnecessary copies or moves, making it more efficient than assignment
        //v.emplace<Number>(15); // emplace is more efficient than assign
        // get returns the reference to the value so we can use
        // it in LHS of assignment
        //std::get<Number>(v) = 15;

        // auto val = std::get<int>(v);  // may throw std::bad_variant_access
        // // auto val = std::get<std::string>(v);

        // val = std::get<1>(v);

        // auto activeIndex = v.index();
        // auto ptr = std::get_if<int>(&v); // returns a pointer to the value if present, otherwise nullptr
        // if (ptr){
        //     std::cout << "Value: " << *ptr << std::endl;
        // }
        // else{
        //     std::cout << "Value is not an int" << std::endl;
        // }
        // std::cout << "Active index: " << activeIndex << std::endl;
    }catch(const std::bad_variant_access &e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}