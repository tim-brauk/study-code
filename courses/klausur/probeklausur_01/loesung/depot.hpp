/**
 * @file depot.hpp
 * @brief Depot class: owns all parcels (composition).
 */

#ifndef DEPOT_HPP
#define DEPOT_HPP

#include "parcel.hpp"

#include <memory>
#include <string>
#include <vector>

class Depot
{
private:
    std::string name;
    std::vector<std::unique_ptr<Parcel>> parcels;

public:
    explicit Depot(const std::string& name);

    void add_parcel(std::unique_ptr<Parcel> p_parcel);
    Parcel* find_parcel(int tracking_no) const; // nullptr if not found

    const std::string& get_name() const
    {
        return name;
    }

    void set_name(const std::string& new_name)
    {
        name = new_name;
    }

    const std::vector<std::unique_ptr<Parcel>>& get_parcels() const
    {
        return parcels;
    }
};

#endif
