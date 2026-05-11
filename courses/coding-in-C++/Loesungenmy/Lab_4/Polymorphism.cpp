#include <iostream>
#include <cmath>

class Vector2D
{
    private:
        double x;
        double y;
       
    public: 
        Vector2D(double x, double y) : x(x), y(y) {}
         double getx()
         {
            return x;
         }
         double gety()
         {
            return y;
         }
         double length()
         {
            double xsquare = pow(x, 2.0);
            double ysquare = pow(y , 2.0);
            double sumsquaew = xsquare + ysquare;
            double laenge = sqrt(sumsquaew);
            return laenge;
            
         }
         double lenth()
         {
            double xsquare = pow(x, 2.0);
            double ysquare = pow(y , 2.0);
            double sumsquaew = xsquare + ysquare;
            double value = sqrt(sumsquaew);
            int precision = 10;
            double factor = std::pow(10.0, precision);
            return std::round(value * factor) / factor;

         }
         void printco()
         {
            std::cout << x << std :: endl;
            std::cout << y << std :: endl;
            std::cout << length() << std::endl;
         }
    
};


int main()
{
    Vector2D a(5, 3);
    a.length();
    a.printco();
}