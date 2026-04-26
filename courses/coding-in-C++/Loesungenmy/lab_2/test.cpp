#include <iostream>
#include <string>
#include <limits>

int main()
{
    double x = 3;
    double y = x * 0.1;
    if(x == 0.3)
    {
        std::cout<<"No error";
    }
    else 
    {
        std::cout<<"Error";
        std::cout<<y;
    }

}
