#include<iostream>
#include <functional>
using namespace std;

/*

typedef void (*CallBack)(void *);


void intCallback(void *data){
    int *intData = static_cast<int *>(data);
    cout << "intCallback: " << *intData << endl;
}

void stringCallback(void *data){
    string *strData = static_cast<string *>(data);
    cout << "stringCallback: " << *strData << endl;
}


void usecase(CallBack callback, void *data){
    callback(data);
}

int main(){
    int d1 = 10;
    string str1={"Hello"};
    usecase(&intCallback, &d1);
    usecase(&stringCallback, &str1);
    return 0;
};
*/


using namespace std;

// Using std::function for callbacks
void usecase(function<void(void*)> callback, void* data) {
    callback(data);
}

int main() {
    int d1 = 10;
    string str1 = "Hello";
    
    // Using lambda functions
    usecase([](void* data) {
        int* intData = static_cast<int*>(data);
        cout << "intCallback: " << *intData << endl;
    }, &d1);
    
    usecase([](void* data) {
        string* strData = static_cast<string*>(data);
        cout << "stringCallback: " << *strData << endl;
    }, &str1);
    
    return 0;
}