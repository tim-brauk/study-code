#include <iostream>
#include <string>

class User {
    protected:
        int id;
        std::string name;
    public:
        User(std::string name, int id) : name(name), id(id) {}  
        void printInfo();
};

class Student : public User {
    private:
        int year;
    public:
        Student(std::string name, int id, int year)  
            : User(name, id), year(year) {}
        
        void printInfo() {
            std::cout << name << " " << id << " " << year << std::endl;  
        }
};

class Instructor : public User {
    private:
        std::string profession;
    public:
        Instructor(std::string name, int id, std::string profession)  
            : User(name, id), profession(profession) {}
        
        void printInfo() {
            std::cout << name << " " << id << " " << profession << std::endl;  
        }
};

int main() {
    Student tim("tim", 12, 8);       
    Instructor john("john", 23, "math"); 
    tim.printInfo();                 
    john.printInfo();
    return 0;
}