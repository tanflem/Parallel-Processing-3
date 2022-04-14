#include <iostream>
#include <unistd.h>
#include <atomic>
#include <memory>
#include <thread>
#include <random>
#include <chrono>
#include <random>
#include <functional>

#define PRESENTS 500000


// Linked list implementation from C++ Concurrency in Action
template<typename T>
class queue
{
    private:
        struct node
        {
            T data;
            std::unique_ptr<node> next;
            node(T data_):
                data(std::move(data_))
            {}
        };
        
        std::unique_ptr<node> head;
        node* tail;
    
    public:

        queue(): tail(nullptr)
        {}

        queue(const queue& other)=delete;

        queue& operator=(const queue& other)=delete;

        std::shared_ptr<T> try_pop()
        {
            if(!head)
            {
                return std::shared_ptr<T>();
            }

            std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
            std::unique_ptr<node> const old_head = std::move(head);
            
            head = std::move(old_head->next);
            
            if(!head)
                tail = nullptr;
            return res;
        }
        void push(T new_value)
        {
        std::unique_ptr<node> p(new node(std::move(new_value)));
        node* const new_tail=p.get();
        if(tail)
        {
            tail->next=std::move(p);
        }
        else
        {
            head=std::move(p);
        }
            tail=new_tail;
        }
};


// Minotaur random selection
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, PRESENTS - 1);
auto randomPresent = std::bind ( distribution, generator);

// Set the starting value of the presents
std::atomic<int> presents(PRESENTS);

// Birthday handling function
void presentHandler()
{
    queue<int> ll;

    // while their are presents left
    while(presents){
        
        if(rand() % 2 && presents != 0)
        {
            
            ll.push(randomPresent());
            //std::cout << "Pushed " << i << '\n';

            presents--;
        }
        else if (ll.try_pop())
        {
            //write the thank you letter
            
        }
            
        std::cout << "Presents = " << presents;
        //std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    // Escaped

}

int main()
{
    std::thread servants[8];
    for (int i=0; i<10; i+=2) 
    {
        servants[i] = std::thread(presentHandler);
    }
    for (auto& s : servants) {
        s.join();
    }

    
    return 0;
}
