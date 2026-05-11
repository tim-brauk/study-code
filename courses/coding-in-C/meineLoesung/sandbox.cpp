#include <iostream>
#include <memory>

template <typename T, typename U>
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



};

int main()
{
    Pair p(5, 8);
    p.print();
}