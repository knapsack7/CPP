#include<iostream>
using namespace std;

int const& max(int const& a, int const& b){
    cout<< "max(a, b)" << endl;
    return a < b ? b:a;
}

template<typename T>
T const& max(T const&a, T const& b){
    cout<< "max(T, T)" << endl;
    return a < b ? b:a;
}

template<typename T>
T const& max(T const&a, T const& b, T const& c){
    cout<< "max(T, T, T)" << endl;
    return max(max(a, b), c);
}

int main(){
    cout<<::max(10.0, 20.0)<<endl;;
    cout<<::max('a', 'b')<<endl;
    cout<<::max(10, 20)<<endl;
    cout<<::max<>(10,20)<<endl;
    cout<<::max<double>(10,20)<<endl;
    cout<<::max(10,20,30)<<endl;
    return 0;
}