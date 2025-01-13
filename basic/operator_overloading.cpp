#include <iostream>
using namespace std;

class Complex {
public:
    int real, imag;

    Complex(int r, int i) : real(r), imag(i) {}

    // Overloading the '+' operator
    Complex operator+(const Complex& c) {
        return Complex(real + c.real, imag + c.imag);
    }
};

int main() {
    Complex c1(2, 3);
    Complex c2(4, 5);

    Complex result = c1 + c2; // Translates to: c1.operator+(c2)

    cout << "Result: " << result.real << " + " << result.imag << "i" << endl;
    return 0;
}