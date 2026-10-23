/**
 * @file mechanic.hpp
 * @brief Mechanic class: qualifications and assigned orders.
 */

#ifndef MECHANIC_HPP
#define MECHANIC_HPP

#include <set>
#include <string>
#include <vector>

class Order; // forward declaration

class Mechanic
{
private:
    static int next_id;

    const int id;
    std::string name;
    double max_hours;
    std::set<std::string> qualifications; // searchable, no duplicates
    std::vector<Order*> assigned_orders;  // non-owning: the workshop owns the orders

public:
    Mechanic(const std::string& name, double max_hours);

    // a copy would duplicate the unique ID and the order assignments
    Mechanic(const Mechanic&) = delete;
    Mechanic& operator=(const Mechanic&) = delete;

    void add_qualification(const std::string& qualification);
    bool remove_qualification(const std::string& qualification);
    bool has_qualification(const std::string& qualification) const;

    double get_current_workload_h() const; // derived attribute

    // Assigns the order if it is open, the mechanic has the required qualification and the
    // max. hours are not exceeded. Returns false (and changes nothing) otherwise.
    bool assign_order(Order& order);

    // Marks the assigned order as done and removes it from the list.
    // Returns false if the order is not assigned to this mechanic.
    bool finish_order(int order_no);

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

    double get_max_hours() const
    {
        return max_hours;
    }

    void set_max_hours(double new_max_hours);

    const std::set<std::string>& get_qualifications() const
    {
        return qualifications;
    }

    const std::vector<Order*>& get_assigned_orders() const
    {
        return assigned_orders;
    }
};

#endif
