#include <iostream>
#include <string>

class User {
    protected:
        int id; // id ist privat und muss geschützt werden 
        std::string name; // Name muss privat gehalten werden
    public:
        User(std::string name, int id) : name(name), id(id) {}  
        void printInfo();
};

class Student : public User {
    private:
        int year; //alter ist ein senibele information
    public:
        Student(std::string name, int id, int year)  
            : User(name, id), year(year) {}
        
        void printInfo() {
            std::cout << name << " " << id << " " << year << std::endl;  
        }
};

class Instructor : public User {
    private:
        std::string profession; // das könnte auch öffentlich sein 
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

// 1. everything would be private  and with that non accesbible
// 2. because without it would construct a class with diffrent constructar that would be an undefined behavieur
