#include "concurrencpp/concurrencpp.h"

#include <thread>
#include <mutex>


int main(){
	std::mutex mtx;
	int c = 0;
	
	std::thread t[8];
	
	for(auto& thread : t ){
		thread = std::thread([&] () mutable {
			std::unique_lock<std::mutex> lock(mtx);
			++c;
		});
	}
	
	for(auto& thread : t ){
		thread.join();
	}
	
	return 0;
}