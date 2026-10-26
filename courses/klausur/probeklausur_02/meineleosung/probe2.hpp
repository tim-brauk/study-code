#include <iostream>
#include <string>

class Mechanic
{
    private:
        int MechanichID;
    public:
        int getMechanicID()
        {
            return MechanichID;
        }
};
class Werkstatt 
{
    private:
        int Mechanicanzha;
        int anzhalaufträge;
    
};

class Auftrag
{
    private:
        int id;
        std::string Kennzeichen;
        int geArbeitszeit;
        Mechanic::getMechanicID();

};
class Sensor 
{
    private:
         std::string id;
         static int anzahl;
    public:
        Sensor(std::string id) : id(id) {anzahl++;}
        std::string getId(){return id;} const 
        virtual int getAnzahl(){return anzahl;} 
};
int Sensor::anzahl = 0;

class Tempsensor : public Sensor
{
    private:
        double offset;
    public:
        Tempsensor(std::string id, double offset) : Sensor(id), offset(offset) {}
        static double messen() override;
};

class Steuergerät
{
    public:
        Steuergerät();
        double auswerten();
        
};
class Flugzeug 
{
    private:
        std::string kennung;
        static int gesamt;
    public:
        Flugzeug(std::string kennung) : kennung(kennung) {gesamt++;}
};
int Flugzeug::gesamt = 0;
class Sensor 