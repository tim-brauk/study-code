#include "drone_test_bench.hpp"

int main()
{
    const int SIZE = 5;
    char testFrame[SIZE] = {'1', '2', '3', '4', '5'};

    if (SIZE <= 0)
    {
        std::cout << "Error: SIZE is zero or negative." << std::endl;
        return 1;
    }
    printFrame(testFrame, SIZE);
    std::cout << min(testFrame, SIZE) << std::endl;

    return 0;
}