#include <iostream>
#include <string>

class User
{
    protected: 
        int id;
        std::string name;
    public:
        User(std::string name, int id);
        void printInfo();
};

class Student : protected User 
{
    private: 
        int year;
    public:
        void printInfo()
        {
            std::cout << name, id, year  << std::endl;
        }

};

class Instructor : protected User
{
    private: 
        std::string profession;

    public:
        void printInfo()
        {
            std::cout << name, id, profession << std::endl;
        }

};

int main()
{
    return 0;
}