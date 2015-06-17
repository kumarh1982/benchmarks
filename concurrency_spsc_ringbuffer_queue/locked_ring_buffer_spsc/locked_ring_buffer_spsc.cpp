#include<thread>
#include <cinttypes>
#include<mutex>
using namespace std;

#define RING_BUFFER_SIZE 1000
class lockled_ring_buffer_spsc
{
	private :
		int64_t write = 0;
		int64_t read = 0;
		int64_t size = RING_BUFFER_SIZE;
		int64_t buffer[RING_BUFFER_SIZE];
		std::mutex lock;
	public :
		
		void push(int64_t val)
		{
			lock.lock();
			buffer[write%size] = val;
			write++;
			lock.unlock();
		}
		
		int64_t pop()
		{
			lock.lock();
			int64_t ret = buffer[read%size];
			read++;	
			lock.unlock();
			return ret;
		}
};

int main (int argc, char** argv)
{
	lockled_ring_buffer_spsc queue;
	
	std::thread write_thread( [&] () {
			 for(int i = 0; i<1000000; i++)
			 {
					queue.push(i);
			 }
		 }  // End of lambda expression
												);
	std::thread read_thread( [&] () {
			 for(int i = 0; i<1000000; i++)
			 {
					queue.pop();
			 }
		 }  // End of lambda expression
												);
	write_thread.join();
	read_thread.join();
	 
	 return 0;
}