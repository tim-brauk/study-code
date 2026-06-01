#include <iostream>
#include <thread>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

void producer()
{
    int item = 0;
    while (true)
    {
        if (count < BUFFER_SIZE)
        {
            item++;
            buffer[in] = item;
            in = (in + 1) % BUFFER_SIZE;
            count++;
            std::cout << "[Producer]  produziert Gut #" << item 
                      << "  (count=" << count << ")\n";
            usleep(100);
        }
    }
}

void consumer(int id)
{
    while (true)
    {
        if (count > 0)
        {
            int item = buffer[out];
            out = (out + 1) % BUFFER_SIZE;
            count--;
            std::cout << "[Consumer " << id << "] verbraucht Gut #" << item 
                      << "  (count=" << count << ")\n";
            usleep(150);
        }
    }
}

int main()
{
    std::thread prod(producer);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();

    return 0;
}