#include <iostream>
#include <string>
#include <cstdint>

class Notiz
{
    private:
        std::string* text;
        int size;

    public:
        // Constructor (was wrongly named "Note" instead of "Notiz")
        Notiz(std::string initialText)
        {
            size = 1;
            text = new std::string[size];
            text[0] = initialText;
            std::cout << "Memory allocated\n";
        }

        // Destructor (was wrongly named "~Note" instead of "~Notiz")
        ~Notiz()
        {
            delete[] text;
            std::cout << "Memory released\n";
        }

        // Fixed display method
        void display()
        {
            for (int i = 0; i < size; i++)
            {
                std::cout << text[i] << "\n";
            }
        }
};

int main()
{
    Notiz object("Hallo");
    object.display();
    return 0;
    std::int_least64_t y = 5
}
