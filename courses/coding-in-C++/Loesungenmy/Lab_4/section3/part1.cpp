#include <iostream>
#include <cmath>

class shape 
{
    
    public:
        virtual double area() const { return 0.0;}
        virtual ~shape() {}


};

class rectancle : public shape 
{
    private:
        double le;
        double wide;
        double area;
    public:
        virtual double area() override
        {
            area = wide * le;
            return area;
        }
        virtual ~rectancle() {}


};

class circle : public shape
{
    private:
        double r;
        double pi = 3.14;
    public:
        virtual double area()
        {
            return pi;
        }


};