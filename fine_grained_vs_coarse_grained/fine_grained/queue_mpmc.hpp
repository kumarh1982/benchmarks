#ifndef __QUEUE_MPMC_H__
#define __QUEUE_MPMC_H__

#include<mutex>
using namespace std;

template<typename T>
class QueueMPMC
{
private:
    
    struct node
    {
        T data;
        node* next;
        
        node(): next(nullptr){}
    };
    
    std::mutex head_mutex;
    std::mutex tail_mutex;

    node* head;
    node* tail;
    
public:
	QueueMPMC()
	{
            // Create a new empty node so we avoid a lock for accessing head in enqueue
            node* dummy = new node;
            
            //Tail and head point to it
            head = tail = dummy;
	}
        
        void enqueue(T data)
        {
            node* new_node = new node;
            new_node->data = data;
            
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->next = new_node;
            tail = new_node;
        }
        
        bool dequeue(T* data)
        {
            head_mutex.lock();
            
            node* current_head = head;
            node* new_head = current_head->next;
            
            if( new_head == nullptr)
            {
                head_mutex.unlock();
                return false;
            }
            
            *data = new_head->data;
            
            head = new_head; // Swapping dummy-initial node so we avoid to update the tail pointer
                             // Therefore no need for protecting the tail
            
            head_mutex.unlock();
            
            free(current_head); // De allocate previous dummy node
            return true;
        }
};
#endif