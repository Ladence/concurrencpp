#include "concurrencpp/concurrencpp.h"

#include "utils/object_observer.h"

#include <thread>
#include <mutex>

using namespace concurrencpp::tests;

struct data{
	std::mutex lock;
	size_t counter = 0;
};

int main(){
	object_observer observer;
	std::thread threads[8];

	auto ptr = std::make_shared<data>();
	
    for (auto& thread : threads) {
		thread = std::thread([ptr] () mutable {
			for(size_t i =0; i< 10'000; i ++){
				auto& lock = ptr->lock;
				auto& counter = ptr->counter;
				{
					std::unique_lock<std::mutex> _lock(lock);
					++counter;	
				}	
			}
		});
     }

   observer.wait_execution_count(80'000, std::chrono::minutes(2));
   observer.wait_destruction_count(80'000, std::chrono::minutes(2));

    for (auto& thread : threads) {
		thread.join();
	}	
		
	return 0;
}
