// Algorithm call with predicate
// Using lambda expression
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};
	int divisor{};
	
	std::cout << "Elements of vector: ";
	
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';

	std::cout << "Enter a divisor: ";
	std::cin >> divisor;
	
	// Call std::count_if() algorithm using a lambda expression as predicate
	auto divisible_count = std::count_if(vec.begin(), vec.end(), 
	
		// The lambda definition goes inside the call!
		[divisor] (int n)
		{ 
			return (divisor != 0) && (n % divisor == 0);
		}
	);

	std::cout << "The vector has " << divisible_count
			  << " element(s) divisible by " << divisor << '\n';
}