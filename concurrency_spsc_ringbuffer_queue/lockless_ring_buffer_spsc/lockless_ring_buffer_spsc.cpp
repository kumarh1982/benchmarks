// USING SEQUENTIAL MEMORY
#include<thread>
#include<atomic>
#include <cinttypes>
using namespace std;

#define RING_BUFFER_SIZE 1000
class lockless_ring_buffer_spsc
{
	public :
		
		lockless_ring_buffer_spsc()
		{
			write.store(0);
			read.store(0);
		}
		
		bool try_push(int64_t val)
		{
			const auto current_tail = write.load();
            const auto next_tail = increment(current_tail);
            if (next_tail != read.load())
            {
                buffer[current_tail] = val;
                write.store(next_tail);
                return true;
            }

            return false;  
		}
		
		void push(int64_t val)
		{
			while( ! try_push(val) );
		}
		
		bool try_pop(int64_t* pval)
		{
			auto currentHead = read.load();
            
            if (currentHead == write.load())
            {
                return false;
            }

            *pval = buffer[currentHead];
            read.store(increment(currentHead));

            return true;
		}
		
		int64_t pop()
		{
			int64_t ret;
			while( ! try_pop(&ret) );
			return ret;
		}
		
	private :
		std::atomic<int64_t> write ;
		std::atomic<int64_t> read;
		int64_t size = RING_BUFFER_SIZE;
		int64_t buffer[RING_BUFFER_SIZE];
		
		int64_t increment(int n)
        {
            return (n + 1) % size;
        }
};

int main (int argc, char** argv)
{
	lockless_ring_buffer_spsc queue;
	
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