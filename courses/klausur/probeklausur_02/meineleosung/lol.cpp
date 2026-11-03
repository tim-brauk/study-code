#include "lol.hpp"
int Drohne::anzahl = 0;
double Lieferdrohne::berecheneReichweite() const
{   
    return getakkustand() * 0.5;

}

double Kamedrohne::berecheneReichweite() const
{
    return getakkustand() * 0.8;
}

int main()
{
    Lieferdrohne lief0(2, 80.0, 5.0);
    Kamedrohne  cam1(2, 60.0, 12.0);
    Flotte flotte;
    flotte.hinzufuegen(&lief0);
    flotte.hinzufuegen(&cam1);

    flotte.zeigeReichweiten();
    std::cout << "Drohnen insgesamt: " << Drohne::getAnzahl() << "\n";
    return 0;

}