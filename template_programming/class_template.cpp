#include <iostream>

template<typename T, int size>
class Stack {
    T m_buffer[size];
    T m_top{-1};
public:
    Stack() = default;
    // Stack(const Stack &obj){
    //     m_top = obj.m_top;
    //     for (int i = 0; i < size; i++){
    //         m_buffer[i] = obj.m_buffer[i];
    //     }
    // }
    void push(T ele){
        m_buffer[++m_top] = ele;
    }
    void pop();
    const int top() const{
        return m_buffer[m_top];
    }
    bool isEmpty() const{
        return m_top == -1;
    }
    bool isFull() const{
        return m_top == 511;
    }
    static Stack<T, size> create();
    Stack(const Stack<T, size> &obj);

};

template<typename T, int size>
Stack<T, size> Stack<T, size>::create(){
    return Stack<T, size>();
}

template<typename T, int size>
void Stack<T,size>::pop(){
    m_buffer[m_top--];
}

template<typename T, int size>
Stack<T, size>::Stack(const Stack<T, size> &obj){
    m_top = obj.m_top;
    for (int i = 0; i < size; i++){
        m_buffer[i] = obj.m_buffer[i];
    }
}

int main(){
    Stack<int,10> s = Stack<int, 10>::create();
    s.push(1);s.push(2);s.push(3);
    auto s2 = s;
    while(!s2.isEmpty()){
        std::cout << s2.top() <<"," << std::endl;
        s2.pop();
    }

    return 0;
}