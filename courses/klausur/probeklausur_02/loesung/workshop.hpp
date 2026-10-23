/**
 * @file workshop.hpp
 * @brief Workshop class: owns all orders (composition).
 */

#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include "order.hpp"

#include <memory>
#include <string>
#include <vector>

class Workshop
{
private:
    std::string name;
    std::vector<std::unique_ptr<Order>> orders;

public:
    explicit Workshop(const std::string& name);

    void add_order(std::unique_ptr<Order> p_order);
    Order* find_order(int order_no) const; // nullptr if not found

    // Deletes a finished order. Returns false if the number is unknown,
    // throws std::logic_error if the order is not done yet.
    bool remove_order(int order_no);

    double get_total_revenue() const; // derived attribute: sum over all finished orders

    const std::string& get_name() const
    {
        return name;
    }

    void set_name(const std::string& new_name)
    {
        name = new_name;
    }

    const std::vector<std::unique_ptr<Order>>& get_orders() const
    {
        return orders;
    }
};

#endif
