#include <iostream>
using namespace std;

/*
 * Some of the literals can be modified through prefixes or suffixes
 * 14u, 14U -> unsigned
 * 14l, 14L -> long
 * 14ll, 14LL -> long long
 * 14.0f, 14.0F -> float
 * 14.0 -> double
 * 14.0l -> long double
 * 14.0f -> float
 * In C++, we can define our own suffixes
 * can be applied to integer, floating point, character and string literals
 * Creating custom literals provides syntactic shortcuts and increase type safety
 * Temperature temp{82.5}; // fahrenheit or celsius??
 * Temperature temp{82.5_F}; // fahrenheit
 * 
 * Syntax:
 * <return type> operator "" _<literal>(<arguments>)
 * operator "" : defines a literal operator function
 * <return type> : can be any type, including void
 * _<literal> : always starts with _ followed by a name
 * <arguments> : can be of the following types:
 * 1. integer - unsigned long long
 * 2. floating point - long double
 * 3. character - char, wchar_t, char16_t, char32_t
 * 4. string - const char*
 */


class Distance{
    long double m_kilometers;
public:
    Distance(long double kms) : m_kilometers(kms){}
    long double getKm() const{
        return m_kilometers;
    }
    void setKm(long double val){
        m_kilometers = val;
    }
};

Distance operator"" _metres(long double val){
    return Distance(val / 1000);
}

Distance operator"" _mi(long double val){
    return Distance(val * 1.6);
}

int main(){
    Distance d1{32.0_mi};
    cout << d1.getKm() << endl;
    Distance d2{1640.0_metres};
    cout << d2.getKm() << endl;
    return 0;
}

/*
 * Custom literals should begin with underscore
 * literals without underscore are reserved for the standard library
 * You cannot redefine the meaning of built-in literal suffixes
 * Only following types can be suffixed to make a user-defined literal
 *  unsigned long long, long double, const char*, char
 * Literal operator functions cant be member functions. They will always
 * be global functions
 */
