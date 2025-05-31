#include<iostream>
#include<fstream>
#include<mutex>

using namespace std;

class PrettyMenu{
public:
    void changeBackground(istream& imgSrc); // change background image
private:
    mutex cb_m; // mutex for changing background
    Image *bgImage; // current background image
    int bgColor; // current background color
};

void PrettyMenu::changeBackground(istream& imgSrc){
    lock_guard<mutex> lock(cb_m);
    delete bgImage; // delete old background image
    ++changeCount; // increment change count
    bgImage = new Image(imgSrc); // new background image
    bgColor = getColor(imgSrc); // new background color
}

// The above code is exception safe bc it has issues:
// 1. Leak Resources
// 2. allows data structures to become corrupted

// To make it exception safe, we will use copy-and-swap idiom
// also called the Pimpl[Pointer to Implementation] idiom


struct PMImpl{
    std::tr1::shared_ptr<Image> bgImage; // PMimpl = "PrettyMenu Impl"
    int imageChanges; // number of times the background image has been changed
}

class PrettyMenu{
    ...
private:
    Mutex mutex;
    std::tr1::shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackground(istream& imgSrc){
    using std::swap;
    Lock ml(&mutex);  //acquire the mutex
    std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl)); // copy obj.data
    pNew->bgImage.reset(new Image(imgSrc)); // modify the copy
    ++pNew->imageChanges; // increment change count
    swap(pImpl, pNew); // swap the new data into place
    // release the mutex
}
