/**
 * @file main.cpp
 * @brief Workshop demo (Aufgabe c) and answers to Aufgabe e).
 */

#include "mechanic.hpp"
#include "order.hpp"
#include "workshop.hpp"

#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

/*
 * Aufgabe e1) Geloeschter Kopierkonstruktor / Zuweisungsoperator
 * Der vom Compiler erzeugte Kopierkonstruktor kopiert alle Attribute 1:1 (flache Kopie).
 * Die Kopie haette dieselbe Auftragsnummer -> die Nummer waere nicht mehr eindeutig.
 * Ausserdem wuerde p_mechanic mitkopiert: Die Kopie "glaubt", sie gehoere zu einem
 * Mechaniker, der Mechaniker kennt aber nur das Original -> die bidirektionale
 * Assoziation waere inkonsistent. Mit "= delete" meldet schon der Compiler einen Fehler.
 * (Bei Order kommt noch Slicing dazu: Kopiert man ueber eine Order&, ginge der
 * Repair-/Inspection-Teil verloren.)
 *
 * Aufgabe e2) virtual / rein virtuell / override
 * - virtual: Die Methode wird dynamisch gebunden. Ueber einen Order* wird zur Laufzeit
 *   die Version des tatsaechlichen Objekts (Repair oder Inspection) aufgerufen.
 * - rein virtuell (= 0): Die Basisklasse hat keine Implementierung. Die Klasse wird
 *   dadurch abstrakt, jede konkrete Unterklasse MUSS die Methode ueberschreiben.
 *   Deshalb ist "Order o("RV-X 1", 2.0);" ein Compilerfehler: Von einer abstrakten
 *   Klasse kann man keine Objekte anlegen (Zeiger und Referenzen gehen aber).
 * - override: Der Compiler prueft, dass wirklich eine virtuelle Methode der Basisklasse
 *   ueberschrieben wird. Ein Tippfehler oder ein fehlendes const fuehrt dann zu einem
 *   Compilerfehler statt zu einer neuen, nie aufgerufenen Methode.
 *
 * Aufgabe e3) Warum darf remove_order nur abgeschlossene Auftraege loeschen?
 * Ein Auftrag "In Progress" steht noch in assigned_orders eines Mechanikers (roher,
 * nicht-besitzender Zeiger). Loescht die Werkstatt ihn, zeigt dieser Zeiger auf
 * freigegebenen Speicher (dangling pointer). Der naechste Aufruf von
 * get_current_workload_h() oder finish_order() waere undefiniertes Verhalten.
 * Ein abgeschlossener Auftrag wurde in finish_order() bereits aus der Liste des
 * Mechanikers entfernt -> niemand zeigt mehr auf ihn, Loeschen ist sicher.
 */

namespace
{
void print_all_orders(const Workshop& workshop)
{
    for (const std::unique_ptr<Order>& p_order : workshop.get_orders())
    {
        const Order* p_base = p_order.get(); // base class pointer -> dynamic dispatch
        p_base->print_info();
    }
}

void print_revenue(const Workshop& workshop)
{
    std::cout << "Umsatz " << workshop.get_name() << ": " << std::fixed << std::setprecision(2)
              << workshop.get_total_revenue() << " EUR\n";
    std::cout << std::defaultfloat;
}
} // namespace

int main()
{
    std::cout << std::boolalpha;
    Workshop workshop("Autohaus Schmid");
    workshop.add_order(std::make_unique<Inspection>("RV-AB 123", 1.5, true));          // 500
    workshop.add_order(std::make_unique<Repair>("FN-XY 42", 10.0, "Engine", 350.0));   // 501
    workshop.add_order(std::make_unique<Inspection>("RV-CD 7", 1.0, false));           // 502
    workshop.add_order(std::make_unique<Repair>("RV-EF 99", 3.0, "Electrics", 120.0)); // 503

    try
    {
        workshop.add_order(std::make_unique<Repair>("RV-GH 1", 0.0, "Engine", 50.0));
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Auftrag abgelehnt: " << error.what() << "\n";
    }

    std::vector<std::unique_ptr<Mechanic>> mechanics;
    mechanics.push_back(std::make_unique<Mechanic>("Lena Vogt", 11.0));
    mechanics.push_back(std::make_unique<Mechanic>("Max Huber", 8.0));
    mechanics[0]->add_qualification("Maintenance");
    mechanics[0]->add_qualification("Engine");
    mechanics[1]->add_qualification("Maintenance");
    mechanics[1]->add_qualification("Electrics");

    Mechanic& lena = *mechanics[0];
    Mechanic& max = *mechanics[1];

    std::cout << "Zuweisung 501 (Lena): " << lena.assign_order(*workshop.find_order(501))
              << "\n";
    std::cout << "Zuweisung 500 (Lena, zu viele Stunden: " << lena.get_current_workload_h()
              << " h + 1.5 h > " << lena.get_max_hours()
              << " h): " << lena.assign_order(*workshop.find_order(500)) << "\n";
    std::cout << "Zuweisung 503 (Lena, keine Qualifikation Electrics): "
              << lena.assign_order(*workshop.find_order(503)) << "\n";
    std::cout << "Zuweisung 503 (Max): " << max.assign_order(*workshop.find_order(503)) << "\n";
    std::cout << "Zuweisung 501 (Max, nicht mehr offen): "
              << max.assign_order(*workshop.find_order(501)) << "\n";
    std::cout << "Zuweisung 502 (Max): " << max.assign_order(*workshop.find_order(502))
              << "\n\n";

    print_all_orders(workshop);
    print_revenue(workshop);

    std::cout << "\nMax schliesst 503 ab: " << max.finish_order(503) << "\n";
    std::cout << "Max schliesst 501 ab (gehoert Lena): " << max.finish_order(501) << "\n";
    std::cout << "Lena schliesst 501 ab: " << lena.finish_order(501) << "\n";
    std::cout << "Auslastung Lena: " << lena.get_current_workload_h() << " h\n";
    print_revenue(workshop);

    try
    {
        workshop.remove_order(502);
    }
    catch (const std::logic_error& error)
    {
        std::cout << "Entfernen abgelehnt: " << error.what() << "\n";
    }
    std::cout << "Entferne 503: " << workshop.remove_order(503) << "\n";
    std::cout << "Entferne 999 (unbekannt): " << workshop.remove_order(999) << "\n";
    print_revenue(workshop);

    std::cout << "\nNach Abschluss und Archivierung:\n";
    print_all_orders(workshop);

    return 0;
}
