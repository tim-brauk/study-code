/**
 * @file courier.cpp
 * @brief Implements the Courier class.
 */

#include "courier.hpp"
#include "parcel.hpp"

int Courier::next_id = 1;

Courier::Courier(const std::string& name, double max_load_kg)
    : id(next_id++), name(name), max_load_kg(max_load_kg)
{
}

void Courier::add_postal_code(const std::string& postal_code)
{
    postal_codes.insert(postal_code);
}

bool Courier::remove_postal_code(const std::string& postal_code)
{
    return postal_codes.erase(postal_code) > 0;
}

bool Courier::serves(const std::string& postal_code) const
{
    return postal_codes.find(postal_code) != postal_codes.end();
}

double Courier::get_current_load_kg() const
{
    double load_kg = 0.0;
    for (const Parcel* p_parcel : loaded_parcels)
    {
        load_kg += p_parcel->get_weight_kg();
    }
    return load_kg;
}

bool Courier::load_parcel(Parcel& parcel)
{
    if (parcel.get_status() != ParcelStatus::IN_DEPOT)
    {
        return false;
    }
    if (!serves(parcel.get_postal_code()))
    {
        return false;
    }
    if (get_current_load_kg() + parcel.get_weight_kg() > max_load_kg)
    {
        return false;
    }

    loaded_parcels.push_back(&parcel);
    parcel.set_courier(this);
    parcel.set_status(ParcelStatus::IN_DELIVERY);
    return true;
}

void Courier::deliver_all()
{
    for (Parcel* p_parcel : loaded_parcels)
    {
        p_parcel->set_status(ParcelStatus::DELIVERED);
    }
    loaded_parcels.clear();
}
