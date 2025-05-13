#include<iostream>
#include<thread>
using namespace std;

void print(){
    cout<<"Hello from thread1"<<endl;
}

void print1(){
    cout<<"Hello from thread2"<<endl;
}

int main(){
    thread *t1 = new thread(print);
    thread *t2 = new thread(print1);

    if (t1->joinable())
        t1->join();
    if (t2->joinable())
        t2->join();
    cout<<"Program Terminated\n";
    return 0;
}