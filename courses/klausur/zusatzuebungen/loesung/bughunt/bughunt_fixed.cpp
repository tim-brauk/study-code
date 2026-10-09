/**
 * @file bughunt_fixed.cpp
 * @brief Korrigierte Sendungsverfolgung. Jede Korrektur ist mit FIX <Nr> markiert
 *        (Nummern wie in fehlerliste.md).
 */

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class TrackingEvent
{
public:
    TrackingEvent(const std::string& location, int hour) : location(location), hour(hour)
    {
    }

    const std::string& get_location() const // FIX 1
    {
        return location;
    }

    int get_hour() const
    {
        return hour;
    }

private:
    std::string location;
    int hour;
};

class Shipment
{
public:
    explicit Shipment(const std::string& id) : id(id)
    {
    }

    virtual ~Shipment() // FIX 2
    {
        std::cout << "Shipment " << id << " destroyed\n";
    }

    /** @brief Grundgebuehr einer Sendung in EUR. */
    virtual double fee() const
    {
        return 5.0;
    }

    void add_event(const TrackingEvent& event)
    {
        events.push_back(event);
    }

    /** @brief Liefert das zuletzt hinzugefuegte Event. */
    const TrackingEvent& last_event() const
    {
        if (events.empty())
        {
            throw std::out_of_range("Keine Events vorhanden");
        }
        return events.back(); // FIX 3
    }

    /** @brief Durchschnittliche Uhrzeit aller Events (mit Nachkommastellen). */
    double average_hour() const
    {
        if (events.empty())
        {
            return 0.0;
        }
        int sum = 0;
        for (const TrackingEvent& event : events)
        {
            sum += event.get_hour();
        }
        return static_cast<double>(sum) / static_cast<double>(events.size()); // FIX 4
    }

    virtual void print() const
    {
        std::cout << "Sendung " << id << ", Gebuehr " << fee() << " EUR\n";
        for (const TrackingEvent& event : events)
        {
            std::cout << "  " << event.get_hour() << " Uhr: " << event.get_location() << "\n";
        }
    }

    const std::string& get_id() const
    {
        return id;
    }

protected:
    std::string id;
    std::vector<TrackingEvent> events;
};

class InternationalShipment : public Shipment
{
public:
    InternationalShipment(const std::string& id, const std::string& country, double customs_rate)
        : Shipment(id), country(country), customs_rate(customs_rate) // FIX 5
    {
    }

    ~InternationalShipment() override
    {
        // FIX 6: vorher "delete" statt "delete[]" auf new[]. Besser: gar kein new,
        // sondern std::vector -> kein manuelles Freigeben, keine Rule-of-Three-Probleme.
        std::cout << "InternationalShipment " << id << " destroyed\n";
    }

    /** @brief Gebuehr inkl. Zoll: 5.00 EUR + Zollsatz * 10 EUR. */
    double fee() const override // FIX 7
    {
        return Shipment::fee() + customs_rate * 10.0;
    }

    void print() const override
    {
        Shipment::print();
        std::cout << "  Zielland: " << country << "\n";
    }

private:
    std::string country;
    double customs_rate;
    std::vector<std::string> customs_documents = std::vector<std::string>(3); // FIX 6
};

/** @brief Erzeugt ein Versandlabel der Form "LBL-<id>". */
std::string make_label(const Shipment& shipment) // FIX 8: Rueckgabe per Wert
{
    return "LBL-" + shipment.get_id();
}

int main()
{
    std::vector<std::unique_ptr<Shipment>> shipments; // FIX 9: kein Slicing
    shipments.push_back(std::make_unique<InternationalShipment>("S1", "CH", 0.2));
    shipments.push_back(std::make_unique<Shipment>("S2"));

    // Erwartet: S1 kostet 7.00 EUR, S2 kostet 5.00 EUR
    for (std::size_t index = 0; index < shipments.size(); index++) // FIX 10
    {
        shipments[index]->print();
    }

    std::unique_ptr<Shipment> p_shipment = std::make_unique<InternationalShipment>("S3", "AT", 0.5);
    p_shipment->add_event(TrackingEvent("Stuttgart", 8));
    p_shipment->add_event(TrackingEvent("Muenchen", 13));
    p_shipment->add_event(TrackingEvent("Salzburg", 17));

    // Erwartet: Durchschnitt 12.6667, letztes Event Salzburg, Gebuehr 10 EUR
    std::cout << "Durchschnitt: " << p_shipment->average_hour() << "\n";
    std::cout << "Letztes Event: " << p_shipment->last_event().get_location() << "\n";
    std::cout << "Label: " << make_label(*p_shipment) << "\n";
    p_shipment->print();

    std::unique_ptr<Shipment> p_archive = std::move(p_shipment); // FIX 11
    p_archive->print();

    return 0;
}
