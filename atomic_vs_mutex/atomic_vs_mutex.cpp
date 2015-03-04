#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

#define TEST_RUN 10000

struct AtomicCounter 
{
    std::atomic<long> value;

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get()
	{
        return value.load();
    }
	
	AtomicCounter()
	{
		value.store(0);
	}
};

struct MutexCounter 
{
    std::mutex mutex;
    long value;

    void increment()
	{
        std::lock_guard<std::mutex> guard(mutex);
        value++;
    }

    void decrement()
	{
        std::lock_guard<std::mutex> guard(mutex);
        value--;
    }
	
	MutexCounter() : value(0) {}
};

template <typename T>
void run_counters()
{
	std::vector<std::thread> threads;
	T counter;
	
	 for(int i = 0; i < TEST_RUN; ++i)
	 {
	   threads.push_back( std::thread( [&] () {
											for(int i = 0; i<100; i++)
											{
												counter.increment();
											}
											} )
						);
						;
	 }
	 
	for(auto& thread : threads)
	{
      thread.join();
    }
	
	cout << endl << counter.value << endl << endl;
}

int main(int argc, char** argv)
{
	if( argc < 2 ) return -1;
	
	string arg(argv[1]);
	
	if( arg.compare("atomic") == 0 )
	{
		run_counters<AtomicCounter>();
	}
	else if ( arg.compare("mutex") == 0 ) 
	{
		run_counters<MutexCounter>();
	}
	
	return 0;
}