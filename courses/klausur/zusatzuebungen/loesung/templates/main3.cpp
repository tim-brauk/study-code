/**
 * @file main3.cpp
 * @brief Tests for Aufgabe 3.
 */

#include "templates.hpp"

#include <iostream>
#include <list>
#include <vector>

int main()
{
    // a)
    std::cout << clamp_value(15, 0, 10) << " " << clamp_value(-2.5, 0.0, 1.0) << " "
              << clamp_value<std::string>("m", "a", "k") << "\n";
    try
    {
        clamp_value(5, 10, 0);
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Fehler: " << error.what() << "\n";
    }

    // b)
    std::vector<int> ints = {1, 2, 3, 4};
    std::array<double, 4> doubles = {1.5, 2.5, 3.5, 4.5};
    std::list<float> floats = {10.0f, 20.0f};
    std::cout << average(ints) << " " << average(doubles) << " " << average(floats) << "\n";
    try
    {
        average(std::vector<int>{});
    }
    catch (const std::domain_error& error)
    {
        std::cout << "Fehler: " << error.what() << "\n";
    }

    // c)
    RingBuffer<int, 3> buffer;
    for (int value = 1; value <= 4; value++)
    {
        buffer.push(value);
    }
    for (std::size_t index = 0; index < buffer.size(); index++)
    {
        std::cout << buffer.at(index) << " ";
    }
    std::cout << "(voll: " << std::boolalpha << buffer.is_full() << ")\n";
    try
    {
        buffer.at(3);
    }
    catch (const std::out_of_range& error)
    {
        std::cout << "Fehler: " << error.what() << "\n";
    }

    // d)
    std::cout << describe(42) << ", " << describe(std::string("Paket")) << ", "
              << describe(true) << ", " << describe(false) << "\n";

    return 0;
}
