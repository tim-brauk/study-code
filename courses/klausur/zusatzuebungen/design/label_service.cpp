/**
 * @file label_service.cpp
 * @brief Versandlabel-Service von SwiftParcel (Analyseobjekt fuer Aufgabe 5a).
 */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Smtp
{
public:
    void send(const std::string& to, const std::string& text)
    {
        std::cout << "[SMTP an " << to << "] " << text << "\n";
    }
};

class LabelService
{
public:
    double calculate_price(const std::string& type, double weight_kg)
    {
        if (type == "standard")
        {
            return 4.99 + 0.5 * weight_kg;
        }
        else if (type == "express")
        {
            return 2 * (4.99 + 0.5 * weight_kg);
        }
        else if (type == "fragile")
        {
            return 6.99 + 0.8 * weight_kg;
        }
        return 0.0;
    }

    void create_label(const std::string& type, double weight_kg, const std::string& recipient,
                      const std::string& email)
    {
        double price = calculate_price(type, weight_kg);
        std::string label = recipient + " | " + type + " | " + std::to_string(price) + " EUR";

        // Ausgabe auf Konsole
        std::cout << label << "\n";

        // Speichern in Datei
        std::ofstream file("labels.txt", std::ios::app);
        file << label << "\n";

        // E-Mail-Benachrichtigung, fest verdrahtet
        Smtp smtp;
        smtp.send(email, "Ihr Label: " + label);
    }
};

/** @brief Interface fuer alle Geraete im Depot. */
class DepotDevice
{
public:
    virtual ~DepotDevice() = default;
    virtual void print_label(const std::string& label) = 0;
    virtual void scan_barcode() = 0;
    virtual void weigh() = 0;
};

/** @brief Ein einfacher Etikettendrucker. Kann nur drucken. */
class LabelPrinter : public DepotDevice
{
public:
    void print_label(const std::string& label) override
    {
        std::cout << "Drucke: " << label << "\n";
    }

    void scan_barcode() override
    {
        throw std::logic_error("Drucker kann nicht scannen");
    }

    void weigh() override
    {
        throw std::logic_error("Drucker kann nicht wiegen");
    }
};

int main()
{
    LabelService service;
    service.create_label("express", 2.0, "Hauptstr. 1, Stuttgart", "kunde@example.com");

    LabelPrinter printer;
    printer.print_label("TEST");
    return 0;
}
