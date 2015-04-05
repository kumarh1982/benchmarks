#define USE_EASTL

#ifndef USE_EASTL
#include <vector>
#include <set>
#include <string>
#else
#include <EASTL/vector.h>
#include <EASTL/set.h>
#include <EASTL/string.h>
#endif

#include <iostream>
using namespace std;

#include <chrono>
using namespace std::chrono;

#include <functional>
#include <algorithm>

#define NUM_ITERATIONS_VECTOR 10000*10000
#define NUM_ITERATIONS_SET 100000
#define NUM_ITERATIONS_STRING 100000

#ifdef USE_EASTL
// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	return malloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	// this allocator doesn't support alignment
	EASTL_ASSERT(alignment <= 8);
	return malloc(size);
}

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnprintf(pDestination, n, pFormat, arguments);
#else
	return vsnprintf(pDestination, n, pFormat, arguments);
#endif
}

#endif

void vector_test()
{
	cout << "****************************************" << endl;
	cout << "VECTOR TEST" << endl;

#ifndef USE_EASTL
	std::vector<int> v;
#else
eastl::vector<int> v;
#endif
	////////////////////////////////////////////////////////////////////////////////////////////
	auto start = high_resolution_clock::now();

	for (int i = 0; i < NUM_ITERATIONS_VECTOR; i++)
	{
		v.push_back(i);
	}

	auto end = high_resolution_clock::now();
	auto time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "Pushback took " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	start = high_resolution_clock::now();

	auto i = std::remove_if(v.begin(), v.end(), [](int n){return n % 10; });
	v.erase(i, v.end());

	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "std::remove_if , multiples of 10 " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	start = high_resolution_clock::now();

	for (int i = 0; i < NUM_ITERATIONS_VECTOR; i++)
	{
		v.insert(v.end(), i);
	}

	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "Insert took " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	start = high_resolution_clock::now();

	sort(v.begin(), v.end(), std::greater<int>());

	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "Sort took " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	start = high_resolution_clock::now();

	for (int i = 0; i < NUM_ITERATIONS_VECTOR; i++)
	{
		v[i] = v[i] + 1;
	}

	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "Operator[] and assignment took " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	start = high_resolution_clock::now();

	for (auto& item : v)
	{
		item--;
	}

	end = high_resolution_clock::now();
	time_span = duration_cast<duration<double, milli>>(end - start);
	std::cout << "Iteration and assignment took " << time_span.count() << " milliseconds." << endl;
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "****************************************" << endl;
}

int main(int argc, char** argv)
{
	vector_test();
	return 0;
}