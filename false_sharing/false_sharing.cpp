#include <cstdint>
#include <cstdlib>
#include <memory>
#include <pthread.h>
using namespace std;

#define CACHE_LINE_ALIGNED

#define THREAD_1_CORE 0
#define THREAD_2_CORE 2
#define THREAD_3_CORE 4

#define CACHE_LINE_SIZE 64
#define ITERATION 10000

struct dummy 
{
   #ifdef CACHE_LINE_ALIGNED
   alignas(CACHE_LINE_SIZE) uint32_t d1;
   alignas(CACHE_LINE_SIZE) uint32_t d2;
   alignas(CACHE_LINE_SIZE) uint32_t d3;
   #else
   uint32_t d1;
   uint32_t d2;
   uint32_t d3;
   #endif
};

static  dummy  data;

void* thread1(void* arg)
{
    for( int i(0); i<ITERATION; i++)
    {		
		for( int j(0); j<ITERATION; j++)
		{
			data.d1++;
		}
    }
}

void* thread2(void* arg)
{
    for( int i(0); i<ITERATION; i++)
    {
		for( int j(0); j<ITERATION; j++)
		{
			data.d2++;
		}
    }
}

void* thread3(void* arg)
{
    for( int i(0); i<ITERATION; i++)
    {
		for( int j(0); j<ITERATION; j++)
		{
			data.d3++;
		}
    }
}

int main (int argc, char** argv)
{
    cpu_set_t cpuset;
    // Start Thread 1 and bind to core 0
    CPU_ZERO(&cpuset);
    CPU_SET(THREAD_1_CORE, &cpuset);
    
    pthread_t t1 ;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_setaffinity_np(t1, sizeof(cpu_set_t), &cpuset);
    
    // Start Thread 2 and bind to core 2
    CPU_ZERO(&cpuset);
    CPU_SET(THREAD_2_CORE, &cpuset);
    
    pthread_t t2 ;
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_setaffinity_np(t2, sizeof(cpu_set_t), &cpuset);
	
    // Start Thread 3 and bind to core 4
    CPU_ZERO(&cpuset);
    CPU_SET(THREAD_3_CORE, &cpuset);
    
    pthread_t t3 ;
    pthread_create(&t3, NULL, thread3, NULL);
    pthread_setaffinity_np(t3, sizeof(cpu_set_t), &cpuset);
	
    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}