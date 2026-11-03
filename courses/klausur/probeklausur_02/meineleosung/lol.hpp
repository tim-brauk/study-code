#include <iostream>
#include <string>
#include <vector>

class Drohne
{
    private:
        int id;
        double akkustand;
        static int anzahl;
    public:
        Drohne(int id, double akkustand) : id(id), akkustand(akkustand) {anzahl++;}
        virtual ~Drohne() = default;
        int getID() const {return id;}
        virtual double berecheneReichweite() const = 0;
        static int getAnzahl() {return anzahl;}
        double getakkustand() const {return akkustand;}

};

class Lieferdrohne : public Drohne
{
    private: 
        int maxZuladung;
    public:
        Lieferdrohne(int id, double akkustand, double maxZuladug) : Drohne(id, akkustand), maxZuladung(maxZuladung){}
        double berecheneReichweite() const override;

};

class Kamedrohne : public Drohne
{
    private:
        int Aufloesung;
    public:
        Kamedrohne(int id, double akkustand, double Aufloesung) : Drohne(id, akkustand), Aufloesung(Aufloesung){}
        double berecheneReichweite() const override;
 
};
class Flotte
{
    private:
        std::vector<Drohne*> drohnen;
    public:
        void hinzufuegen(Drohne* d) { drohnen.push_back(d); }
        void zeigeReichweiten() const
        {
            for (Drohne* d : drohnen)
                std::cout << "Drohne " << d->getID() << ": " << d->berecheneReichweite() << " km\n";
        }
};