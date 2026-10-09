/**
 * @file depot.cpp
 * @brief Implements the Depot class.
 */

#include "depot.hpp"

#include <stdexcept>

Depot::Depot(const std::string& name) : name(name)
{
}

void Depot::add_parcel(std::unique_ptr<Parcel> p_parcel)
{
    if (p_parcel == nullptr)
    {
        throw std::invalid_argument("Leeres Paket kann nicht hinzugefuegt werden");
    }
    parcels.push_back(std::move(p_parcel)); // the depot takes the ownership
}

Parcel* Depot::find_parcel(int tracking_no) const
{
    for (const std::unique_ptr<Parcel>& p_parcel : parcels)
    {
        if (p_parcel->get_tracking_no() == tracking_no)
        {
            return p_parcel.get();
        }
    }
    return nullptr;
}
