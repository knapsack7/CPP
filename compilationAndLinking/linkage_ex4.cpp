#include<iostream>
#include "header_ex3.h"

using namespace std;

void function_E()
{

	cout<<"In ex4.cpp counter value "
		<< counter
		<< " static variable's address "
		<< &counter << std::endl;
	counter = counter * 2;
	return;
}
