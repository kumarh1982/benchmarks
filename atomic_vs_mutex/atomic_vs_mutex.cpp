#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <atomic>
#include <mutex>

#if defined __MINGW32__ || _WIN32
#include <windows.h>	// For use of CRITICAL_SECTION on Windows
#endif

using namespace std;

#define TEST_RUN 10000

struct AtomicCounter
{
	std::atomic<long> value;

	void increment() {
		++value;
	}

	void decrement() {
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

// Note : the Mutex class below implemented by https://github.com/gekomad
// Original class is on https://gist.github.com/gekomad/267b884dac64d4a4e68d
//
// The idea is basically sticking with std::mutex for non Windows systems 
// as by default they will be using futexes and stay in user mode as much as possible
//
// That applies to GNU Lib C runtime, you can see futex usage if you strace.
//
// However for Windows side, it is not always the case that std::mutex will be implemented
// by using CRITICAL_SECTION 
//
// Use of lightweight syncronisation objects : http://preshing.com/20111124/always-use-a-lightweight-mutex/
// MSVC CRT implementation : http://stackoverflow.com/questions/9997473/stdmutex-performance-compared-to-win32-critical-section
// As Gekad informed , looks like Mingw on Windows does not also use CRITICAL_SECTION
#if defined __MINGW32__ || _WIN32
#include <windows.h>

class Mutex {
public:
	Mutex() { InitializeCriticalSection(&cs); }

	~Mutex() { DeleteCriticalSection(&cs); }

	void lock() { EnterCriticalSection(&cs); }

	void unlock() { LeaveCriticalSection(&cs); }

private:
	CRITICAL_SECTION cs;
};

#else

#include <mutex>

class Mutex : public std::mutex {

};

#endif
struct MutexCounter
{
	Mutex mutex;
	long value;

	void increment()
	{
		std::lock_guard<Mutex> guard(mutex);
		value++;
	}

	void decrement()
	{
		std::lock_guard<Mutex> guard(mutex);
		value--;
	}

	MutexCounter() : value(0) {}
};

template <typename T>
void run_counters()
{
	std::vector<std::thread> threads;
	T counter;

	for (int i = 0; i < TEST_RUN; ++i)
	{
		threads.push_back(std::thread([&]() {
			for (int i = 0; i<100; i++)
			{
				counter.increment();
			}
		})
			);
		;
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	cout << endl << counter.value << endl << endl;
}

int main(int argc, char** argv)
{
	if (argc < 2) return -1;

	string arg(argv[1]);

	if (arg.compare("atomic") == 0)
	{
		run_counters<AtomicCounter>();
	}
	else if (arg.compare("mutex") == 0)
	{
		run_counters<MutexCounter>();
	}

	return 0;
}