#include <iostream>
#include <memory>

class Printer{
    std::weak_ptr<int> m_pValue{};
public:
    void setValue(std::weak_ptr<int> p){
        m_pValue = p;
    }
    void print(){
        if(m_pValue.expired() == true){
            std::cout<<"Resource is no longer available" << std::endl;
            return;
        }
        auto sp = m_pValue.lock();
        std::cout<<"Value is : " << *sp << std::endl;
        std::cout<<"Ref count : " << sp.use_count() << std::endl;
    }
};

/*
Note that weak_ptr always shared with the shared_ptr
*/

int main(){
    Printer prn;
    int num{};
    std::cin>> num;
    std::shared_ptr<int> p{new int{num}};
    prn.setValue(p);
    if(*p > 10){
        p = nullptr;
    }
    prn.print();
    return 0;
}