/**
 * @file courier.hpp
 * @brief Courier class: delivery areas and loaded parcels.
 */

#ifndef COURIER_HPP
#define COURIER_HPP

#include <set>
#include <string>
#include <vector>

class Parcel; // forward declaration

class Courier
{
private:
    static int next_id;

    const int id;
    std::string name;
    double max_load_kg;
    std::set<std::string> postal_codes;   // searchable, no duplicates
    std::vector<Parcel*> loaded_parcels;  // non-owning: the depot owns the parcels

public:
    Courier(const std::string& name, double max_load_kg);

    // a copy would duplicate the unique ID and the parcel assignments
    Courier(const Courier&) = delete;
    Courier& operator=(const Courier&) = delete;

    void add_postal_code(const std::string& postal_code);
    bool remove_postal_code(const std::string& postal_code);
    bool serves(const std::string& postal_code) const;

    double get_current_load_kg() const; // derived attribute

    // Loads the parcel if it is in the depot, its postal code is served and the max. load
    // is not exceeded. Returns false (and changes nothing) otherwise.
    bool load_parcel(Parcel& parcel);
    void deliver_all();

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

    double get_max_load_kg() const
    {
        return max_load_kg;
    }

    void set_max_load_kg(double new_max_load_kg)
    {
        max_load_kg = new_max_load_kg;
    }

    const std::set<std::string>& get_postal_codes() const
    {
        return postal_codes;
    }

    const std::vector<Parcel*>& get_loaded_parcels() const
    {
        return loaded_parcels;
    }
};

#endif
