#include<iostream>

/*
 * 1. std::thread is non-copyable but movable. Using std::move with a thread is essential when you want to
 * transfer ownership of the thread object.
 * Why use std::move with std::thread ?
 * bz std::thread cannot be copied (copy constructor is deleted), if you want to:
 * - pass it to a function
 * - return it from a function
 * - store it in a container
 * - reassign it to another thread variable, ... you must move it using std::move.  
 */

#include<thread>
/*
void task(){
	std::cout<<"Running in thread\n"<<std::endl;
}

int main(){
	std::thread t1(task);
	// std::thread t2 = t1; // Error: copy constructor is deleted
	std::thread t2 = std::move(t1);
	if (t1.joinable()) t1.join(); // false now as t1 is in indeterminate state after the move, t1 does not have thread reference now
	if (t2.joinable()) t2.join(); //true
	return 0;
}
*/

/*
std::thread createWorker(){
	return std::thread([]{
		std::cout<<"Hello from the worker\n";
	});
}

int main(){
	std::thread t = createWorker();
	t.join();
	return 0;
}
*/

/*
int main(){
	std::vector<std::thread> threads;
	for (int i =0 ; i < 4; ++i){
		// std::thread is moved into the vector (internally via emplace_back or push_back with std::move).
		threads.push_back(std::thread([i]{std::cout<<i<< std::endl;}));	
	}
	for(auto & t: threads)	t.join();
	return 0;
}*/


/*
 * Use std::move(thread) when transferring the thread handle/ownership, not when passing thread arguments.
 * After move, the source thread becomes non-joinable.
 */


/*
 * In C++, you can pass std::thread objects as function arguments, but there are some important things to understand
 * Std::Thread is non-copyable but movable. That means, 
 * you cannot pass a std::thread by value
 * You can pass a std::thread by reference or by move.
 */


/*
// 1. Pass by reference (when you want to modify or join it)

void threadHandler(std::thread& t) {
    if (t.joinable())
        t.join();  // join from inside
}

void task() {
    std::cout << "Task running\n";
}

int main() {
    std::thread t(task);
    threadHandler(t);
    return 0;
}
*/

/*

// 2.Pass by Move(transfer ownership)

void threadHandler(std::thread t) {
    if (t.joinable())
        t.join();  // thread is joined here
}

void task() {
    std::cout << "Task running\n";
}

int main() {
    std::thread t(task);
    threadHandler(std::move(t)); // move into function
    return 0;
}

// after std::move(t), the original t in main() becomes non-joinable

*/

/*

// const in mutex world

class Logger {
public:
	void log(const std::string& msg) const{
		std::lock_guard<std::mutex> lock(mtx); // ok bz mtx is mutable
		std::cout<< msg <<std::endl;
	}
private:
	mutable std::mutex mtx;
}

*/
