#include <iostream>
#include <string>
#include <limits>
#include <cstdint>


namespace validation
{
    bool isAdult(uint8_t age);
    bool isSenior(uint8_t age);
}

 int getAge()
{
    std::cout << "Alter eingeben: ";
    int age;
    std::cin >> age;
    if(age < 0)
    {
        std::cout << "Bitte keine negativen Zahlen eingeben" << std::endl;
    }
    else if (age > 100)
    {
        std::cout << "So alt bist du nicht" << std::endl;
    }
    else 
    {
        return age;
    }
    
    return age;
}

bool validation::isAdult(uint8_t age)
{
    return (age >= 18 && age < 65);
}

bool validation::isSenior(uint8_t age)
{
    return (age >= 65);
}

int main()
{
   uint16_t age = getAge();

    if (!validation::isAdult(age) && !validation::isSenior(age))
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist noch ein Kind oder Teenager." << std::endl;
    }
    else if (validation::isAdult(age) && !validation::isSenior(age))
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist ein Erwachsener." << std::endl;
    }
    else
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist ein Senior." << std::endl;
    }

    return 0;
}