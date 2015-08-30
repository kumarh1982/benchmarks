#ifndef __QUEUE_MPMC_H__
#define __QUEUE_MPMC_H__

#include<mutex>
#include<condition_variable>
#include<queue>
using namespace std;

template<typename T>
class QueueMPMC
{
private:
    
    queue<T> m_queue;
    mutex m_lock;
    condition_variable m_data_condition;
    
public:
	QueueMPMC() : m_queue(), m_lock(), m_data_condition()
	{
	}

	~QueueMPMC()
	{
	}

	void push(T val)
	{
        std::unique_lock<std::mutex> lock(m_lock);
        m_queue.push(val);
        // when we send the notification immediately, the consumer will try to get the lock , so unlock asap
        lock.unlock(); 
        m_data_condition.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(m_lock);
	    m_data_condition.wait(lock, [this](){return !m_queue.empty(); });
        auto val = m_queue.front();
        m_queue.pop();
        return val;
        // Lock will be released
	}
};


#endif