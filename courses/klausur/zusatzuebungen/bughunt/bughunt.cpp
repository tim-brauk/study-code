/**
 * @file bughunt.cpp
 * @brief Sendungsverfolgung fuer SwiftParcel (enthaelt 10 Fehler).
 *
 * Erwartetes Verhalten:
 *  - Jede Sendung speichert Tracking-Events (Ort + Uhrzeit).
 *  - Internationale Sendungen kosten 5.00 EUR + Zollsatz * 10 EUR.
 *  - Alle Sendungen werden polymorph ausgegeben und korrekt freigegeben.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class TrackingEvent
{
public:
    TrackingEvent(const std::string& location, int hour) : location(location), hour(hour)
    {
    }

    std::string get_location()
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

    ~Shipment()
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
        return events[events.size()];
    }

    /** @brief Durchschnittliche Uhrzeit aller Events (mit Nachkommastellen). */
    double average_hour() const
    {
        int sum = 0;
        for (const TrackingEvent& event : events)
        {
            sum += event.get_hour();
        }
        return sum / static_cast<int>(events.size());
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
        : Shipment(id), country(country)
    {
        p_customs_documents = new std::string[3];
    }

    ~InternationalShipment()
    {
        delete p_customs_documents;
        std::cout << "InternationalShipment " << id << " destroyed\n";
    }

    /** @brief Gebuehr inkl. Zoll: 5.00 EUR + Zollsatz * 10 EUR. */
    double fee()
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
    std::string* p_customs_documents;
};

/** @brief Erzeugt ein Versandlabel der Form "LBL-<id>". */
const std::string& make_label(const Shipment& shipment)
{
    std::string label = "LBL-" + shipment.get_id();
    return label;
}

int main()
{
    std::vector<Shipment> shipments;
    shipments.push_back(InternationalShipment("S1", "CH", 0.2));
    shipments.push_back(Shipment("S2"));

    // Erwartet: S1 kostet 7.00 EUR, S2 kostet 5.00 EUR
    for (std::size_t index = 0; index <= shipments.size(); index++)
    {
        shipments[index].print();
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

    std::unique_ptr<Shipment> p_archive = p_shipment;
    p_archive->print();

    return 0;
}
