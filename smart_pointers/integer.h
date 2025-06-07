#pragma once
#include <iostream>

class Integer {
    int *m_pInt;  // Pointer to dynamically allocated integer
public:
    //Default constructor - creates an Integer with value 0
    Integer();
    
    //Parameterized constructor - creates an Integer with given value
    Integer(int value);
    
    //Copy constructor - creates a new Integer as a copy of another Integer
    Integer(const Integer &obj);
    
    
    //Move constructor - transfers ownership of resources from another Integer
    Integer(Integer &&obj) noexcept;

    // copy assignment operator
    Integer& operator=(const Integer &);

    // move assignment operator
    Integer& operator=(Integer &&) noexcept;

    
    //Getter - returns the value of the Integer
    int GetValue() const;
    
    //Setter - sets the value of the Integer
    void SetValue(int value);
    
    //Destructor - cleans up dynamically allocated memory

    //Integer operator+(const Integer &obj) const;

    Integer& operator++();  // Preincrement operator
    Integer operator++(int);  // Postincrement operator - returns by value

    bool operator==(const Integer &obj) const;


    friend std::istream& operator>>(std::istream& is, Integer &obj);
    void operator()();

    ~Integer();
};
