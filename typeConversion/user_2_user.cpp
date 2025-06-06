#include <iostream>
#include "integer.h"

class Product{
    Integer m_Id;
public:
    Product(const Integer &id) : m_Id(id){
        std::cout << "Product(const Integer &)called" << std::endl;
    }
    const Integer& GetInteger() const{
        return m_Id;
    }

    operator Integer() const{
        std::cout << "operator Integer() called" << std::endl;
        return m_Id;
    }

    ~Product(){
        std::cout << "~Product() called" << std::endl;
    }
};

int main(){
    Product p{5};
    Integer id{5};
    //id = p; //id = p.operator Integer();
    //std::cout << id.GetValue() << std::endl;

    if (id == p){
        std::cout << "id == p" << std::endl;
    }else{
        std::cout << "id != p" << std::endl;
    }
    return 0;
}