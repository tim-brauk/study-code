#ifndef DRONE_TEST_BENCH_HPP
#define DRONE_TEST_BENCH_HPP

#include <iostream>

template <typename T>
void swap(T &firstValue, T &secondValue)
{
    std::cout << "Input" << '\n';
    std::cout << "First value: " << firstValue << '\n';
    std::cout << "Second value: " << secondValue << '\n';

    T tmp = firstValue;
    firstValue = secondValue;
    secondValue = tmp;

    std::cout << "Output" << '\n';
    std::cout << "First value: " << firstValue << '\n';
    std::cout << "Second value: " << secondValue << '\n';
}

// Question Task 1: Why a template is better here than writing three separate functions?
// Answer: There are multiple reasons why templates should be chosen over three separate functions:
// 1. Less effort for the programmer when writing the code
// 2. Less error-prone and better to maintain because there is only one implementation
// 3. Only instantiated when used so it can potentially reduce the binary size of the exe
// 4. Templates are perfect for reusability since each type can be used as long as the operations are defined.

template <typename T>
void printFrame(T frame, int size)
{
    std::cout << "[";
    for (int i = 0; i < size - 1; i++)
    {
        std::cout << frame[i] << ", ";
    }
    std::cout << frame[size - 1] << "]" << '\n';
}

template <typename T>
T min(T frame[], int size)
{

    T minValue = frame[0];
    for (int i = 1; i < size; i++)
    {
        if (frame[i] < minValue)
        {
            minValue = frame[i];
        }
    }
    return minValue;
}

#endif