#include "concurrencpp/concurrencpp.h"

#include "utils/object_observer.h"

#include <thread>
#include <mutex>

using namespace concurrencpp::tests;

int main(){
    object_observer observer;
	std::thread threads[8];
	
    for (auto& thread : threads) {
		thread = std::thread([stub = observer.get_testing_stub()] () mutable {
			for(size_t i =0; i< 10'000; i ++){
				stub();
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
