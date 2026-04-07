#include "report_utilities.hpp"
#include <iomanip>
#include <limits>

// read in user input from terminal
void read_score(const std::string &text, std::uint_fast16_t &value)
{

    while (true)
    {
        std::cout << text;

        // check if it is a valid number
        if (!(std::cin >> value))
        {
            std::cout << "Error: Not a valid number. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // check if it is larger than 100
        else if (value > 100)
        {
            std::cout << "Error: Not in the valid number range. Try again." << std::endl;
            continue;
        }
        break;
    }
}

// read in user name and all scores
void readStudentData(std::string &name, std::uint_fast16_t &homework, std::uint_fast16_t &midterm, std::uint_fast16_t &finalExam)
{

    std::cout << "Enter the student's name: ";

    if (!(std::getline(std::cin, name)))
    {
        std::cout << "Error while reading input stream." << std::endl;
    }

    read_score("Enter the homework score (0-100): ", homework);
    read_score("Enter the midterm score (0-100): ", midterm);
    read_score("Enter the final exam score (0-100): ", finalExam);
}

// calculate the final grade and also return the grade as letter
void calculateGrade(
    std::uint_fast16_t homework, std::uint_fast16_t midterm,
    std::uint_fast16_t final_exam,
    double &final_grade, std::string &letter_grade)
{

    final_grade = 0.4 * homework + 0.25 * midterm + 0.35 * final_exam;

    if (final_grade >= 90)
    {
        letter_grade = "A";
    }
    else if (final_grade >= 80)
    {
        letter_grade = "B";
    }
    else if (final_grade >= 70)
    {
        letter_grade = "C";
    }
    else if (final_grade >= 60)
    {
        letter_grade = "D";
    }
    else if (final_grade >= 50)
    {
        letter_grade = "E";
    }
    else
    {
        letter_grade = "F";
    }
}

// output report card
void printReport(
    const std::string &name, std::uint_fast16_t homework,
    std::uint_fast16_t midterm, std::uint_fast16_t final_exam,
    double final_grade, const std::string &letter_grade)
{

    std::string status;

    if (letter_grade == "A" || letter_grade == "B" || letter_grade == "C")
    {
        status = "Passed";
    }
    else if (letter_grade == "D" || letter_grade == "E")
    {
        status = "Conditional Pass";
    }
    else
    {
        status = "Fail";
    }

    std::cout << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
    std::cout << std::left << std::setfill(' ') << "Student Report" << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
    std::cout << std::left << std::setfill(' ') << "Name: " << name << std::endl
              << std::endl;
    std::cout << "Scores" << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Homework" << std::right << ": " << std::fixed << std::setprecision(2) << static_cast<double>(homework) << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Midterm" << std::right << ": " << std::fixed << std::setprecision(2) << static_cast<double>(midterm) << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Final Exam" << std::right << ": " << std::fixed << std::setprecision(2) << static_cast<double>(final_exam) << std::endl;
    std::cout << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Final Grade" << std::right << ": " << std::fixed << std::setprecision(2) << final_grade << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Letter Grade" << std::right << ": " << letter_grade << std::endl;
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Status" << std::right << ": " << status << std::endl;
    std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}