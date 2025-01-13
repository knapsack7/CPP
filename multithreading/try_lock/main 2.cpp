#include<iostream>
#include<thread>
#include<chrono>

std::mutex g_lock;

void job1(){
	g_lock.lock();
	std::cout<<"job1 is executed\n";
	g_lock.unlock();
}

void job2(){
	if(g_lock.try_lock()){
		std::cout<<"job2 is executed\n";
		g_lock.unlock();
	}else{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		if(g_lock.try_lock()){
			std::cout<<"job 2 is executed on 2nd try\n";
			g_lock.unlock();
		}
	}
}


int main(){
	std::thread thread1(job1);
	std::thread thread2(job2);

	thread1.join();
	thread2.join();

	return 0;
}

