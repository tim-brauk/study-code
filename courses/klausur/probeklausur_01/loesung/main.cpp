/**
 * @file main.cpp
 * @brief Parcel delivery demo (Aufgabe c) and answers to Aufgabe e).
 */

#include "courier.hpp"
#include "depot.hpp"
#include "parcel.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

/*
 * Aufgabe e1) Virtueller Destruktor
 * Wird ein Objekt ueber einen Basisklassenzeiger geloescht (z.B. std::unique_ptr<Parcel>,
 * der ein ExpressParcel haelt), entscheidet ohne "virtual" der STATISCHE Typ, welcher
 * Destruktor laeuft: nur ~Parcel(). Der Destruktor der abgeleiteten Klasse wird nicht
 * aufgerufen -> undefiniertes Verhalten, Ressourcen der abgeleiteten Klasse (Speicher,
 * Dateien, ...) werden nicht freigegeben. Mit "virtual ~Parcel()" wird dynamisch
 * gebunden: erst ~ExpressParcel(), dann ~Parcel().
 *
 * Aufgabe e2) Depot - Paket vs. Zusteller - Paket
 * - Depot <>-- Paket ist eine KOMPOSITION: Das Depot besitzt die Pakete, ihre Lebensdauer
 *   haengt am Depot. Im Code: std::vector<std::unique_ptr<Parcel>> in Depot. Wird das
 *   Depot zerstoert, zerstoeren die unique_ptr automatisch alle Pakete.
 * - Zusteller --> Paket ist eine (bidirektionale) ASSOZIATION: Der Zusteller transportiert
 *   die Pakete nur, besitzt sie aber nicht. Im Code: std::vector<Parcel*> (nicht-besitzende
 *   rohe Zeiger) in Courier und Courier* in Parcel; deliver_all() leert nur die Liste,
 *   geloescht wird nichts.
 */

int main()
{
    std::cout << std::boolalpha;
    Depot depot("Ravensburg");
    depot.add_parcel(std::make_unique<StandardParcel>(4.0, "88212", false));
    depot.add_parcel(std::make_unique<ExpressParcel>(2.5, "88214", 8));
    depot.add_parcel(std::make_unique<StandardParcel>(20.0, "88250", true));
    depot.add_parcel(std::make_unique<ExpressParcel>(15.0, "88212", 24));

    try
    {
        depot.add_parcel(std::make_unique<StandardParcel>(40.0, "88212", false));
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Paket abgelehnt: " << error.what() << "\n";
    }

    std::vector<std::unique_ptr<Courier>> couriers;
    couriers.push_back(std::make_unique<Courier>("Anna Berger", 20.0));
    couriers.push_back(std::make_unique<Courier>("Tom Keller", 100.0));
    couriers[0]->add_postal_code("88212");
    couriers[0]->add_postal_code("88214");
    couriers[1]->add_postal_code("88250");

    Courier& anna = *couriers[0];
    Courier& tom = *couriers[1];

    std::cout << "Lade 1001 (Anna): " << anna.load_parcel(*depot.find_parcel(1001)) << "\n";
    std::cout << "Lade 1003 (Anna): " << anna.load_parcel(*depot.find_parcel(1003)) << "\n";
    std::cout << "Lade 1002 (Anna, falsche PLZ): " << anna.load_parcel(*depot.find_parcel(1002))
              << "\n";
    std::cout << "Lade 1002 (Tom): " << tom.load_parcel(*depot.find_parcel(1002)) << "\n";
    std::cout << "Lade 1002 (Tom, schon geladen): " << tom.load_parcel(*depot.find_parcel(1002))
              << "\n";
    std::cout << "Lade 1000 (Anna, zu schwer: " << anna.get_current_load_kg() << " kg + 4 kg > "
              << anna.get_max_load_kg() << " kg): " << anna.load_parcel(*depot.find_parcel(1000))
              << "\n\n";

    for (const std::unique_ptr<Parcel>& p_parcel : depot.get_parcels())
    {
        const Parcel* p_base = p_parcel.get(); // base class pointer -> dynamic dispatch
        p_base->print_info();
    }

    anna.deliver_all();
    std::cout << "\nNach der Zustellung durch " << anna.get_name() << ":\n";
    for (const std::unique_ptr<Parcel>& p_parcel : depot.get_parcels())
    {
        const Parcel* p_base = p_parcel.get();
        p_base->print_info();
    }

    return 0;
}
