/**
 * @file main.cpp
 * @brief Fleet management demo (Aufgabe c) and answer to Aufgabe e).
 */

#include "driver.hpp"
#include "vehicle.hpp"

#include <iostream>
#include <memory>
#include <vector>

/*
 * Aufgabe e) Wie stellt man bei polymorphen Klassen sicher, dass die korrekte virtuelle
 * Funktion ueberschrieben wird?
 *
 * - In der Basisklasse wird die Funktion als "virtual" deklariert (bzw. "= 0" fuer rein
 *   virtuell), sonst gibt es keinen dynamischen Aufruf ueber Basisklassenzeiger.
 * - In der abgeleiteten Klasse schreibt man das Schluesselwort "override" hinter die
 *   Signatur. Dann prueft der Compiler, ob es in der Basisklasse wirklich eine virtuelle
 *   Funktion mit exakt gleicher Signatur (Name, Parameter, const, Referenz-Qualifier) gibt.
 *   Ein Tippfehler oder ein fehlendes "const" wuerde sonst still eine NEUE Funktion
 *   anlegen, die die Basisfunktion nur verdeckt -> mit override ist das ein Compilerfehler.
 * - Mit "final" kann man zusaetzlich verhindern, dass eine Funktion/Klasse weiter
 *   ueberschrieben wird.
 * - Die Basisklasse braucht einen virtuellen Destruktor, damit beim Loeschen ueber einen
 *   Basisklassenzeiger auch der Destruktor der abgeleiteten Klasse aufgerufen wird.
 */

int main()
{
    // unique_ptr: polymorphic storage (abstract base class) + automatic cleanup.
    // Objects on the heap keep their address, so the raw pointers between Driver and
    // Vehicle stay valid even if the vectors grow.
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Car>("Volkswagen", "B", 6.5));
    vehicles.push_back(std::make_unique<ElectricCar>("Tesla", "B", 75.0));

    std::vector<std::unique_ptr<Driver>> drivers;
    drivers.push_back(std::make_unique<Driver>("Michael Schumacher"));
    drivers[0]->add_license("B");
    drivers[0]->add_license("BE");

    if (drivers[0]->rent_vehicle(*vehicles[1]))
    {
        std::cout << drivers[0]->get_name() << " hat Fahrzeug " << vehicles[1]->get_id()
                  << " ausgeliehen.\n";
    }
    if (!drivers[0]->rent_vehicle(*vehicles[0]))
    {
        std::cout << drivers[0]->get_name()
                  << " kann kein zweites Fahrzeug ausleihen.\n";
    }
    std::cout << "\n";

    for (const std::unique_ptr<Vehicle>& p_vehicle : vehicles)
    {
        Vehicle* p_base = p_vehicle.get(); // base class pointer -> dynamic dispatch
        p_base->print_info();
    }

    return 0;
}
