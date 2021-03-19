#include "concurrencpp/concurrencpp.h"

#include "utils/object_observer.h"

#include <thread>
#include <mutex>

using namespace concurrencpp::tests;

int main(){
	object_observer observer;	
	concurrencpp::runtime runtime;
	
	for(size_t i = 0; i< 8 ; i++){
		runtime.thread_pool_executor()->post([stub = observer.get_testing_stub()] () mutable {
			stub();	
		});
	}
	
	std::this_thread::sleep_for(std::chrono::second(10));
	
	return 0;
}