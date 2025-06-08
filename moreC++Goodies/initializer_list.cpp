#include <iostream>
#include <initializer_list>
#include <cassert>
using namespace std;

class Bag{
    int arr[10];
    int m_size{};
public:
    Bag(std::initializer_list<int> values){
        assert(values.size() < 10);
        auto it = values.begin();
        while(it != values.end()){
            add(*it);++it;
        }
    }
    void add(int value){
        assert(m_size < 10);
        arr[m_size++] = value;
    }
    void remove() {
        --m_size;
    }
    int operator[](int index){
        return arr[index];
    }
    int getSize() const{
        return m_size;
    }
};


void print(std::initializer_list<int> values){
    for(auto it = values.begin(); it != values.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    int x{0};
    float y{3.1f};
    int arr[5]{3,2,3,7,6};
    std::string s{"Hello C++"};

    std::initializer_list<int> data = {1,2,3,4,5};

    auto values = {1,2,3,4,5};

    Bag b{3,1,8};
    // b.add(3);
    // b.add(1);
    // b.add(8);

    print({1,2,3,4,5});

    for (auto x : {9,5,3,6,3})
        std::cout << x << " ";
    std::cout << endl;
    
    return 0;
}