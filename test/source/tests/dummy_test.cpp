#include "concurrencpp/concurrencpp.h"

#include "utils/object_observer.h"

#include <thread>
#include <mutex>

using namespace concurrencpp::tests;

int main(){
	object_observer observer;	
	std::thread t[8];
	
	for(auto& thread : t ){
		thread = std::thread([stub = observer.get_testing_stub()] () mutable {
			stub();
		});
	}
	
	for(auto& thread : t ){
		thread.join();
	}
	
	return 0;
}