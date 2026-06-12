#include <iostream>
#include <limits>
#include <string>


   struct StudentData 
   {
    std::string name;
    double homework;
    double midTerm;
    double finalExam;
    };

StudentData readStudentData()
{
    StudentData student;

    std::cout << "Wie ist dein Name? ";
    std::getline(std::cin, student.name);

    std::cout << "Welchen Grade hatte dein Homework? ";
    std::cin >> student.homework;

    std::cout << "Welchen Grade hatten deine Midterms? ";
    std::cin >> student.midTerm;

    std::cout << "Welchen Grade hatten deine Finals? ";
    std::cin >> student.finalExam;

    return student;
}


void calculateGrade(const StudentData& student)
{
    double x = student.homework * 0.4 + student.midTerm  * 0.25 + student.finalExam * 0.35;
    if (x < 50)
        std::cout << "Finalgrade: F" << std::endl;
    else if (x < 60)
        std::cout << "Finalgrade: E" << std::endl;
    else if (x < 70)
        std::cout << "Finalgrade: D" << std::endl;
    else if (x < 80)
        std::cout << "Finalgrade: C" << std::endl;
    else if (x < 90)
        std::cout << "Finalgrade: B" << std::endl;
    else
        std::cout << "Finalgrade: A" << std::endl;

        }

int main()
{
    StudentData student = readStudentData();
    calculateGrade(student);
    return 0;
}
