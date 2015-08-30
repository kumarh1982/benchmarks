#include"queue_mpmc.hpp"
#include<iostream>
using namespace std;

#include <pthread.h>
pthread_barrier_t thread_barrier;

#define ITERATION_TIMES 1000
#define NUM_WRITE_THREADS 50
#define NUM_READ_THREADS 50

// Coarse grained queue
QueueMPMC<int> g_fine_grained_queue;

void* thread_coarse_grained_write(void* arg)
{
    pthread_barrier_wait(&thread_barrier);
    //cout << "write_thread is starting" << endl;
    for(int i(0); i< ITERATION_TIMES; i++)
    {
        g_fine_grained_queue.push(1);
    }
}

void* thread_coarse_grained_read(void* arg)
{
    pthread_barrier_wait(&thread_barrier);
    //cout << "read_thread is starting" << endl;
    for(int i(0); i< ITERATION_TIMES; i++)
    {
        g_fine_grained_queue.pop();
    }
}

void run_fine_grained()
{
   pthread_t write_threads[NUM_WRITE_THREADS];
   pthread_t read_threads[NUM_WRITE_THREADS];
   pthread_barrier_init(&thread_barrier,NULL,NUM_READ_THREADS+NUM_WRITE_THREADS);
   
   // Create threads
   
   for(int i(0); i< NUM_WRITE_THREADS; i++)
   {
       pthread_create(&(write_threads[i]), NULL, thread_coarse_grained_write, NULL);
   }
   
   for(int i(0); i< NUM_READ_THREADS; i++)
   {
       pthread_create(&(read_threads[i]), NULL, thread_coarse_grained_read, (void*) NULL);
   }
   
   // Threads will only start when they reach the desired number
   
   // Wait for threads
   
   for(int i(0); i< NUM_WRITE_THREADS; i++)
   {
       pthread_join((write_threads[i]), NULL);
   }
   
   for(int i(0); i< NUM_READ_THREADS; i++)
   {
       pthread_join((read_threads[i]), NULL);
   }
   
   // Destroy the barrier
   pthread_barrier_destroy(&thread_barrier);
}

int main (int argc, char** argv)
{
    run_fine_grained();
    return 0;
}