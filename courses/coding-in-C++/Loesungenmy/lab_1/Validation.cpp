#include <iostream>

namespace validation
{
    bool isAdult(int age);
    bool isSenior(int age);
}

int getAge()
{
    std::cout << "Alter eingeben: ";
    int age;
    std::cin >> age;
    return age;
}

bool validation::isAdult(int age)
{
    return (age >= 18 && age < 65);
}

bool validation::isSenior(int age)
{
    return (age >= 65);
}

int main()
{
    int age = getAge();

    if (!validation::isAdult(age) && !validation::isSenior(age))
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist noch ein Kind oder Teenager." << std::endl;
    }
    else if (validation::isAdult(age))
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist ein Erwachsener." << std::endl;
    }
    else
    {
        std::cout << "Du bist " << age << " Jahre alt.\nDas bedeutet, du bist ein Senior." << std::endl;
    }

    return 0;
}