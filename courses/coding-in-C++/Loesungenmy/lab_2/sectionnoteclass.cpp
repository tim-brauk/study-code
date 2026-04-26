#include <iostream>
#include <string>
#include <cstdint>

class Notiz
{
    private:
        std::string* text;
        int size;

    public:
        Notiz(std::string initialText)
        {
            size = 1;
            text = new std::string[size];
            text[0] = initialText;
            std::cout << "Memory allocated\n";
        }

        Notiz(const Notiz &other)
        {
            size = other.size;
            text = new std::string[size];  
            for (int i = 0; i < size; i++)
            {
                text[i] = other.text[i];   
            }
            std::cout << "Memory allocated (copy)\n";
        }

        ~Notiz()
        {
            delete[] text;
            std::cout << "Memory released\n";
        }

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
    Notiz object1("Hallo");
    object1.display();
    Notiz object2 = object1;
    object2.display();
    return 0;
}
