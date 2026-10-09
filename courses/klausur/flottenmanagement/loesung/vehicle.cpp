/**
 * @file vehicle.cpp
 * @brief Implements Vehicle, Car and ElectricCar.
 */

#include "vehicle.hpp"
#include "driver.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

int Vehicle::next_id = 1;

Vehicle::Vehicle(const std::string& brand, const std::string& needed_license)
    : id(next_id++), brand(brand), available(true), needed_license(needed_license),
      p_assigned_driver(nullptr)
{
}

void Vehicle::print_row(const std::string& label, const std::string& value)
{
    std::cout << std::left << std::setw(LABEL_WIDTH) << label << value << "\n";
}

void Vehicle::print_info() const
{
    std::string driver_name = "None";
    if (p_assigned_driver != nullptr)
    {
        driver_name = p_assigned_driver->get_name();
    }

    print_row("Type", get_type());
    print_row("Brand", brand);
    print_specific_info();
    print_row("Available", available ? "Yes" : "No");
    print_row("Needed License", needed_license);
    print_row("Assigned Driver", driver_name);
    std::cout << std::string(50, '-') << "\n";
}

// ---------------------------------------------------------------- Car

Car::Car(const std::string& brand, const std::string& needed_license,
         double consumption_per_100km)
    : Vehicle(brand, needed_license), consumption_per_100km(consumption_per_100km)
{
}

std::string Car::get_type() const
{
    return "PKW";
}

void Car::print_specific_info() const
{
    std::ostringstream value;
    value << consumption_per_100km;
    print_row("Consumption", value.str());
}

// ---------------------------------------------------------------- ElectricCar

ElectricCar::ElectricCar(const std::string& brand, const std::string& needed_license,
                         double battery_capacity_kwh)
    : Vehicle(brand, needed_license), battery_capacity_kwh(battery_capacity_kwh)
{
}

std::string ElectricCar::get_type() const
{
    return "Electric Car";
}

void ElectricCar::print_specific_info() const
{
    std::ostringstream value;
    value << battery_capacity_kwh << " kWh";
    print_row("Battery Capacity", value.str());
}
