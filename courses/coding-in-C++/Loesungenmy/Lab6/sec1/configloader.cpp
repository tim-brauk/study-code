#include <iostream>
#include <stdexcept>


class ConfigLoad : public logic_error
{
    private:
        std::string filename;
        
    public:
        void load(std::string filename)
        {   if(filename.empty())

                throw std::invalid_argument("Empty Filename");
        }

};

int main()
{
    ConfigLoad a();
    try 

}