/**
 * @file parcel.cpp
 * @brief Implements Parcel, StandardParcel and ExpressParcel.
 */

#include "parcel.hpp"
#include "courier.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
const double BASE_PRICE_EUR = 4.99;
const double PRICE_PER_KG_EUR = 0.50;
const double BULKY_SURCHARGE_EUR = 10.00;
const double EXPRESS_FACTOR = 2.0;
const int EXPRESS_FAST_LIMIT_H = 12;
const double EXPRESS_FAST_SURCHARGE_EUR = 5.00;

double validated_weight(double weight_kg)
{
    if (weight_kg <= 0.0 || weight_kg > Parcel::MAX_WEIGHT_KG)
    {
        throw std::invalid_argument("Ungueltiges Gewicht: " + std::to_string(weight_kg) + " kg");
    }
    return weight_kg;
}

int validated_delivery_time(int hours)
{
    if (hours <= 0)
    {
        throw std::invalid_argument("Zustellzeit muss > 0 h sein");
    }
    return hours;
}

std::string status_to_string(ParcelStatus status)
{
    switch (status)
    {
    case ParcelStatus::IN_DEPOT:
        return "In Depot";
    case ParcelStatus::IN_DELIVERY:
        return "In Delivery";
    case ParcelStatus::DELIVERED:
        return "Delivered";
    }
    return "Unknown";
}

template <typename T>
std::string to_text(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
} // namespace

int Parcel::next_tracking_no = 1000;

Parcel::Parcel(double weight_kg, const std::string& postal_code)
    : tracking_no(next_tracking_no++), weight_kg(validated_weight(weight_kg)),
      postal_code(postal_code), status(ParcelStatus::IN_DEPOT), p_courier(nullptr)
{
}

void Parcel::set_weight_kg(double new_weight_kg)
{
    weight_kg = validated_weight(new_weight_kg);
}

void Parcel::print_row(const std::string& label, const std::string& value)
{
    std::cout << std::left << std::setw(LABEL_WIDTH) << label << value << "\n";
}

void Parcel::print_info() const
{
    std::ostringstream price;
    price << std::fixed << std::setprecision(2) << get_price() << " EUR";

    std::string courier_name = "None";
    if (p_courier != nullptr)
    {
        courier_name = p_courier->get_name();
    }

    print_row("Type", get_type());
    print_row("Tracking No", to_text(tracking_no));
    print_row("Weight", to_text(weight_kg) + " kg");
    print_row("Postal Code", postal_code);
    print_specific_info();
    print_row("Price", price.str());
    print_row("Status", status_to_string(status));
    print_row("Courier", courier_name);
    std::cout << std::string(50, '-') << "\n";
}

// ---------------------------------------------------------------- StandardParcel

StandardParcel::StandardParcel(double weight_kg, const std::string& postal_code, bool bulky_goods)
    : Parcel(weight_kg, postal_code), bulky_goods(bulky_goods)
{
}

std::string StandardParcel::get_type() const
{
    return "Standard";
}

double StandardParcel::get_price() const
{
    double price = BASE_PRICE_EUR + PRICE_PER_KG_EUR * get_weight_kg();
    if (bulky_goods)
    {
        price += BULKY_SURCHARGE_EUR;
    }
    return price;
}

void StandardParcel::print_specific_info() const
{
    print_row("Bulky Goods", bulky_goods ? "Yes" : "No");
}

// ---------------------------------------------------------------- ExpressParcel

ExpressParcel::ExpressParcel(double weight_kg, const std::string& postal_code,
                             int delivery_time_h)
    : Parcel(weight_kg, postal_code), delivery_time_h(validated_delivery_time(delivery_time_h))
{
}

void ExpressParcel::set_delivery_time_h(int hours)
{
    delivery_time_h = validated_delivery_time(hours);
}

std::string ExpressParcel::get_type() const
{
    return "Express";
}

double ExpressParcel::get_price() const
{
    double price = EXPRESS_FACTOR * (BASE_PRICE_EUR + PRICE_PER_KG_EUR * get_weight_kg());
    if (delivery_time_h <= EXPRESS_FAST_LIMIT_H)
    {
        price += EXPRESS_FAST_SURCHARGE_EUR;
    }
    return price;
}

void ExpressParcel::print_specific_info() const
{
    print_row("Delivery Time", to_text(delivery_time_h) + " h");
}
