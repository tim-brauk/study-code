/**
 * @file driver.hpp
 * @brief Driver class: manages license classes and the currently rented vehicle.
 */

#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <set>
#include <string>

class Vehicle; // forward declaration

class Driver
{
private:
    static int next_id;

    const int id;              // set exactly once in the constructor, unique via next_id
    std::string name;
    std::set<std::string> licenses; // sorted, no duplicates, fast find()
    Vehicle* p_rented_vehicle;      // non-owning, max. one vehicle

public:
    explicit Driver(const std::string& name);

    // a copy would duplicate the unique ID
    Driver(const Driver&) = delete;
    Driver& operator=(const Driver&) = delete;

    void add_license(const std::string& license);
    bool remove_license(const std::string& license);
    bool has_license(const std::string& license) const;

    // Rents the vehicle if it is available, the driver has no other vehicle and owns the
    // needed license. Returns false (and changes nothing) otherwise.
    bool rent_vehicle(Vehicle& vehicle);
    void return_vehicle();

    int get_id() const
    {
        return id;
    }

    const std::string& get_name() const
    {
        return name;
    }

    void set_name(const std::string& new_name)
    {
        name = new_name;
    }

    const std::set<std::string>& get_licenses() const
    {
        return licenses;
    }

    Vehicle* get_rented_vehicle() const
    {
        return p_rented_vehicle;
    }
};

#endif
