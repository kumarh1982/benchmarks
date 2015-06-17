#include<thread>
#include<atomic>
#include <cinttypes>
using namespace std;

#define RING_BUFFER_SIZE 1000
class lockless_ring_buffer_spsc
{
	private :
		std::atomic<int64_t> write ;
		std::atomic<int64_t> read;
		int64_t size = RING_BUFFER_SIZE;
		int64_t buffer[RING_BUFFER_SIZE];
	public :
		
		lockless_ring_buffer_spsc()
		{
			write.store(0);
			read.store(0);
		}
		
		bool try_push(int64_t val)
		{
			int64_t read_limit = write - size + 1;
			
			if( read_limit == read.load() )
			{
				return false;
			}
			
			buffer[write%size] = val;
			write.fetch_add(1);
			
			return true;
		}
		
		void push(int64_t val)
		{
			while( ! try_push(val) );
		}
		
		bool try_pop(int64_t* pval)
		{
			int64_t write_limit = read - size + 1;
			
			if( write_limit == write.load() )
			{
				return false;
			}
			
			*pval = buffer[read%size];
			read.fetch_add(1);
			
			return true;
		}
		
		int64_t pop()
		{
			int64_t ret;
			while( ! try_pop(&ret) );
			return ret;
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