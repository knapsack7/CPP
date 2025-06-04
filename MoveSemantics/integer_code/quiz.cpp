#include <iostream>

int Square(int &&x){
    return x*x;
}
 
int main(){
    int &&res1 = Square(8) ;             //Line 1
    const int &res2 = Square(20) ;       //Line 2
    int res3 = Square(Square(5)) ;       //Line 3
    return 0 ;
}

/*
WHich line has error?
There is no error.
*/