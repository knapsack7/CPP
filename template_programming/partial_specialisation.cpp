#include <iostream>

// IN partial specialisation we specialise only few of the 
// template parameters
template<typename T, int columns>
class PrettyPrinter{
    T *m_pData;
public:
    PrettyPrinter(T* data) : m_pData(data){}
    void print(){
        std::cout << "Columns: " << columns << std::endl;
        std::cout << " { " << *m_pData << " } " << std::endl;
    }
    T* getData() const{
        return m_pData;
    }
};

// we want to partial specialise the class template for the case
// when columns is 10
template<typename T>
class PrettyPrinter<T, 80>{
    T *m_pData;
public:
    PrettyPrinter(T* data) : m_pData(data){}
    void print(){
        std::cout << "Using 80 Columns: " << std::endl;
        std::cout << " { " << *m_pData << " } " << std::endl;
    }
    T* getData() const{
        return m_pData;
    }
};


template<typename T>
class SmartPointer{
    T *m_ptr;
public:
    SmartPointer(T *ptr) : m_ptr(ptr){}
    T* operator->(){
        return m_ptr;
    }
    T& operator*(){
        return *m_ptr;
    }
    ~SmartPointer(){
        delete m_ptr;
    }
};


template<typename T>
class SmartPointer<T[]>{
    T *m_ptr;
public:
    SmartPointer(T *ptr) : m_ptr(ptr){}
    T& operator[](int index){
        return m_ptr[index];
    }
    ~SmartPointer(){
        delete[] m_ptr;
    }
};

int main(){
    // int data = 5;

    // PrettyPrinter<int, 80> p{&data};
    // p.print();
    SmartPointer<int[]> s1{new int[5]{1,2,3,4,5}};
    std::cout << "s1[0]: " << s1[0] << std::endl;
    std::cout << "s1[1]: " << s1[1] << std::endl;
    std::cout << "s1[2]: " << s1[2] << std::endl;
    std::cout << "s1[3]: " << s1[3] << std::endl;
    std::cout << "s1[4]: " << s1[4] << std::endl;
    return 0;
}