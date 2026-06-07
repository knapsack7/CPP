#include<iostream>
#include "header_ex3.h"

using namespace std;

int counter = 7;

int main()
{

	int itr = 0;
	function_E();
	for(; itr < numIterations;++itr){
		counter++;	
	}
	cout<<"In ex3.cpp counter value "
		<< counter
		<< " static variable's address "
		<< &counter << std::endl;
	function_E();
	return 0;
}
