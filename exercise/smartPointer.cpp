#include<iostream>

class RefCounter{
    int ref_count;
    RefCounter(const RefCounter& refCnt) = delete;
    RefCounter& operator=(const RefCounter& refCnt) = delete;
public:
    RefCounter() : ref_count(0) {
        std::cout << "RefCounter created" << std::endl;
    }
    int getRefCount() const { return ref_count; }
    void operator++() { ++ref_count; std::cout << "RefCounter incremented" << std::endl; }
    void operator--() { --ref_count; std::cout << "RefCounter decremented" << std::endl; }
    // The dummy int in operator++(int) 
    // doesn’t mean you’re passing an integer — it’s just a syntactic trick to 
    // distinguish the overloads.
    void operator++(int) { ref_count++; std::cout << "RefCounter incremented" << std::endl; } // post-increment
    void operator--(int) { ref_count--; std::cout << "RefCounter decremented" << std::endl; } // post-decrement
    ~RefCounter() { std::cout << "RefCounter destroyed" << " now no of referrences are: " << ref_count << std::endl; }
};

template<typename T>
class SmartPtr{
    T* ptr;
    RefCounter* ref_cnt_obj;
public:
    SmartPtr(T* rawPtr){
        ptr = rawPtr;
        ref_cnt_obj = new RefCounter();
        if(ptr){
            ++(*ref_cnt_obj); // increment the reference count using the operator++
        }
        std::cout << "SmartPtr created" << std::endl;
    }
    SmartPtr(const SmartPtr<T>& other){
        if (this != &other){
            ptr = other.ptr;
            ref_cnt_obj = other.ref_cnt_obj;
            // // We need to dereference ref_cnt_obj to get the RefCounter object
            ++(*ref_cnt_obj); // increment the referrence count using the operator++
            std::cout << "SmartPtr copied" << " now no of referrences are: " << ref_cnt_obj->getRefCount() << std::endl;
        }
    }
    // The assignment operator is used when you reassign one smart pointer to point to 
    // a different resource - possibly releasing the old one, and
    // now sharing ownership of the new one.
    SmartPtr<T>& operator=(SmartPtr<T>& other){
        // other    -> gives us the SmartPtr object itself
        // &other   -> gives us the address of the SmartPtr object (SmartPtr*)
        // this     -> gives us the address of current object (SmartPtr*)
        // *this    -> gives us the current object itself
        if(this != &other){
            if (ref_cnt_obj->getRefCount() == 0){
                delete ptr;
                delete ref_cnt_obj;
                std::cout<<"Old object deleted" << std::endl;
            }
            (*ref_cnt_obj)--;
            ptr = other.ptr;
            ref_cnt_obj = other.ref_cnt_obj;
            ++(*ref_cnt_obj); // increment the reference count using the operator++
        }
        std::cout << "SmartPtr assigned" << std::endl;
        return *this;
    }
    ~SmartPtr(){
        --(*ref_cnt_obj); // decrement the reference count using the operator--
        if(ref_cnt_obj->getRefCount() == 0){
            delete ptr;
            delete ref_cnt_obj;
            std::cout << "SmartPtr destroyed" << " as ref_cnt decremented to 0" << std::endl;
        }
        std::cout << "now no of referrences are: " << ref_cnt_obj->getRefCount() << std::endl;
    }
};

int main(){
    SmartPtr<int> ptr1(new int(10));
    // SmartPtr<int> ptr2(ptr1); // direct copy constructor
    // SmartPtr<int> ptr3 = ptr2; // copy assignemnt operator (copy constructor)
    SmartPtr<int> ptr4 = nullptr; // default constructor
    ptr4 = ptr1; // assignemnt operator (copy constructor)
    SmartPtr<int> ptr5 = nullptr;
    ptr5 = ptr4; // assignemnt operator (copy constructor)
    return 0;
}