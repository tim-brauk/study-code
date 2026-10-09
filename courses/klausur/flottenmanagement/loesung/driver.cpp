/**
 * @file driver.cpp
 * @brief Implements the Driver class.
 */

#include "driver.hpp"
#include "vehicle.hpp"

int Driver::next_id = 1;

Driver::Driver(const std::string& name) : id(next_id++), name(name), p_rented_vehicle(nullptr)
{
}

void Driver::add_license(const std::string& license)
{
    licenses.insert(license); // std::set ignores duplicates automatically
}

bool Driver::remove_license(const std::string& license)
{
    return licenses.erase(license) > 0;
}

bool Driver::has_license(const std::string& license) const
{
    return licenses.find(license) != licenses.end();
}

bool Driver::rent_vehicle(Vehicle& vehicle)
{
    if (!vehicle.is_available())
    {
        return false;
    }
    if (p_rented_vehicle != nullptr)
    {
        return false;
    }
    if (!has_license(vehicle.get_needed_license()))
    {
        return false;
    }

    // keep both sides of the bidirectional association consistent
    p_rented_vehicle = &vehicle;
    vehicle.set_assigned_driver(this);
    vehicle.set_available(false);
    return true;
}

void Driver::return_vehicle()
{
    if (p_rented_vehicle == nullptr)
    {
        return;
    }
    p_rented_vehicle->set_assigned_driver(nullptr);
    p_rented_vehicle->set_available(true);
    p_rented_vehicle = nullptr;
}
