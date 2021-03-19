#include "concurrencpp/concurrencpp.h"

#include "utils/object_observer.h"

#include <thread>
#include <mutex>

using namespace concurrencpp::tests;

int main(){
	const auto worker_count = thread::hardware_concurrency();
    const auto task_count = worker_count * 10'000;

    object_observer observer;
    auto executor = std::make_shared<thread_pool_executor>("threadpool", worker_count, std::chrono::seconds(10));
    
    for (size_t i = 0; i < task_count; i++) {
        executor->post(observer.get_testing_stub());
    }

    assert_true(observer.wait_execution_count(task_count, std::chrono::minutes(2)));
    assert_true(observer.wait_destruction_count(task_count, std::chrono::minutes(2)));
	
	executor->shutdown();
	
	return 0;
}