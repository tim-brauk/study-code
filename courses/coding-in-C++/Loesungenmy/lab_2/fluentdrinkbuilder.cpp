#include <iostream>
#include <string>

class DrinkBuilder
{
private:
    std::string name;
    int sugar;
    bool withMilk;
    int temperature;

    static constexpr int DEFAULT_TEMPERATURE = 20;  // Standardwert
    static constexpr int MAX_SUGAR = 100;           // Maximum

public:
    DrinkBuilder& setName()
    {
        std::cout << "Gib den Namen ein: ";
        std::cin >> name;
        return *this;
    }

    DrinkBuilder() : temperature(DEFAULT_TEMPERATURE), sugar(0), withMilk(false) {}

    DrinkBuilder& setTemperature()
    {
        std::cout << "Wie warm soll dein Getraenk sein? (Standard: " 
                  << DEFAULT_TEMPERATURE << " Grad): ";
        std::cin >> temperature;
        return *this;
    }

    DrinkBuilder& setSugar()
    {
        std::cout << "Wie viel Gramm Zucker? (max. " << MAX_SUGAR << "g): ";
        std::cin >> sugar;

        if (sugar > MAX_SUGAR) {
            std::cout << "Zu viel! Zucker wird auf " << MAX_SUGAR << "g begrenzt.\n";
            sugar = MAX_SUGAR;
        }

        return *this;
    }

    DrinkBuilder& setTemperature()
    {
        std::cout << "Wie warm soll dein Getraenk sein? ";
        std::cin >> temperature;
        return *this;
    }

    DrinkBuilder& setWithMilk()
    {
        std::cout << "1 fuer mit Milch, 0 fuer ohne Milch: ";
        std::cin >> withMilk;
        return *this;
    }
};

int main()
{
    DrinkBuilder drink;
    drink.setName()
         .setSugar()
         .setTemperature()
         .setWithMilk();
}