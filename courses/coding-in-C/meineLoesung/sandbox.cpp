#include <iostream>
#include <memory>
#include <vector>
#include <queue>

/*template <typename T, typename U>
class Pair
{
    private:
        T x;
        U y;
    public: 
        Pair(T x, U y): x(x), y(y) {};
        T getX()
        {
            return x;
        }
        U getY()
        {
            return y;
        }
        void setX(T x)
        {
            this->x = x;
        }
        void setY(U y)
        {
            this->y= y;
        }
        void print()
        {
            std::cout << x << std::endl;
            std::cout << y << std::endl;
        }



};*/

int main()
{
   // Pair p(5, 8);
    //p.print();
    std::vector<int> daten = {5, 1, 9, 3};

    // 1. Normale Queue (FIFO)
    std::queue<int> normaleQueue;
    for (int x : daten) normaleQueue.push(x);

    std::cout << "Normal Queue (FIFO): ";
    while (!normaleQueue.empty()) {
        std::cout << normaleQueue.front() << " "; // Zeigt das vorderste Element
        normaleQueue.pop();
    }
    // Ausgabe: 5 1 9 3 (Genau wie reingesteckt)

    std::cout << "\n---------------------\n";

    // 2. Priority Queue (Standard: Max-Heap)
    std::priority_queue<int> prioQueue;
    for (int x : daten) prioQueue.push(x);

    std::cout << "Priority Queue (Max-Heap): ";
    while (!prioQueue.empty()) {
        std::cout << prioQueue.top() << " "; // Zeigt das priorisierte Element
        prioQueue.pop();
    }
    // Ausgabe: 9 5 3 1 (Immer das Größte zuerst)
    
    return 0;
}
