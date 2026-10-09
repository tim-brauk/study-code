/**
 * @file vehicle.hpp
 * @brief Abstract Vehicle base class and the concrete vehicle types of the fleet.
 */

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>

class Driver; // forward declaration: Vehicle and Driver know each other (bidirectional)

class Vehicle
{
private:
    static int next_id;

    const int id;
    std::string brand;
    bool available;
    std::string needed_license;
    Driver* p_assigned_driver; // non-owning: the driver lives independently of the vehicle

protected:
    static const int LABEL_WIDTH = 20;

    static void print_row(const std::string& label, const std::string& value);

    // Hook for the type-specific row(s) in print_info() (template method pattern)
    virtual void print_specific_info() const = 0;

public:
    Vehicle(const std::string& brand, const std::string& needed_license);
    virtual ~Vehicle() = default;

    // a copy would duplicate the unique ID
    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;

    virtual std::string get_type() const = 0;
    void print_info() const;

    int get_id() const
    {
        return id;
    }

    const std::string& get_brand() const
    {
        return brand;
    }

    void set_brand(const std::string& new_brand)
    {
        brand = new_brand;
    }

    bool is_available() const
    {
        return available;
    }

    void set_available(bool is_available)
    {
        available = is_available;
    }

    const std::string& get_needed_license() const
    {
        return needed_license;
    }

    void set_needed_license(const std::string& license)
    {
        needed_license = license;
    }

    Driver* get_assigned_driver() const
    {
        return p_assigned_driver;
    }

    void set_assigned_driver(Driver* p_driver)
    {
        p_assigned_driver = p_driver;
    }
};

class Car : public Vehicle
{
private:
    double consumption_per_100km;

protected:
    void print_specific_info() const override;

public:
    Car(const std::string& brand, const std::string& needed_license,
        double consumption_per_100km);

    std::string get_type() const override;

    double get_consumption_per_100km() const
    {
        return consumption_per_100km;
    }

    void set_consumption_per_100km(double consumption)
    {
        consumption_per_100km = consumption;
    }
};

class ElectricCar : public Vehicle
{
private:
    double battery_capacity_kwh;

protected:
    void print_specific_info() const override;

public:
    ElectricCar(const std::string& brand, const std::string& needed_license,
                double battery_capacity_kwh);

    std::string get_type() const override;

    double get_battery_capacity_kwh() const
    {
        return battery_capacity_kwh;
    }

    void set_battery_capacity_kwh(double capacity_kwh)
    {
        battery_capacity_kwh = capacity_kwh;
    }
};

#endif
