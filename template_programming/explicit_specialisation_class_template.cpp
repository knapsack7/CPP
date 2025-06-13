#include <iostream>


template<typename T>
class PrettyPrinter{
    T *m_pData;
public:
    PrettyPrinter(T* data) : m_pData(data){}
    void print(){
        std::cout << " { " << *m_pData << " } " << std::endl;
    }
    T* getData() const{
        return m_pData;
    }
};

// specialised class template
template<>
class PrettyPrinter<const char*>{
    const char* m_pData;
public:
    PrettyPrinter(const char* data) : m_pData(data){}
    void print(){
        std::cout << " { " << m_pData << " } " << std::endl;
    }
    const char* getData() const{
        return m_pData;
    }
};


// explicit specialisation of a class template
// we had to write only for the print since 
// only the print method is different for the vector<int>
// so we can write the explicit specialisation for the print method
// and the other methods will be inherited from the base class
template<>
void PrettyPrinter<std::vector<int>>::print(){
    std::cout << " { ";
    for(const auto &item : *m_pData){
        std::cout << item << " ";
    }
    std::cout << " } " << std::endl;
}

template<>
void PrettyPrinter<std::vector<std::vector<int>>>::print(){
    std::cout << " { " << std::endl;
    for(const auto &item : *m_pData){
        std::cout << " \t{ ";
        for(const auto &item2 : item){
            std::cout << item2 << " ";
        }
        std::cout << " }, ";
        std::cout << std::endl;
    }
    std::cout << " } " << std::endl;
}

int main(){
    int data = 5;
    float f = 8.2f;
    PrettyPrinter<int> p1(&data);
    PrettyPrinter<float> p2(&f);
    // p1.print();
    // p2.print();
    // std::cout << "Data: " << *p1.getData() << std::endl;
    // std::cout << "Float: " << *p2.getData() << std::endl;
    // const char *str = "Hello";
    // PrettyPrinter<const char*> p3(str);
    // p3.print();
    // std::cout << "String: " << p3.getData() << std::endl;


    // std::vector<int> v = {1, 2, 3, 4, 5};
    // PrettyPrinter<std::vector<int>> p4(&v);
    // p4.print();

    std::vector<std::vector<int>> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    PrettyPrinter<std::vector<std::vector<int>>> p5(&v);
    p5.print();


    return 0;
}