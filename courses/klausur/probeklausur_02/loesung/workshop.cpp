/**
 * @file workshop.cpp
 * @brief Implements the Workshop class.
 */

#include "workshop.hpp"

#include <algorithm>
#include <stdexcept>

Workshop::Workshop(const std::string& name) : name(name)
{
}

void Workshop::add_order(std::unique_ptr<Order> p_order)
{
    if (p_order == nullptr)
    {
        throw std::invalid_argument("Leerer Auftrag kann nicht hinzugefuegt werden");
    }
    orders.push_back(std::move(p_order)); // the workshop takes the ownership
}

Order* Workshop::find_order(int order_no) const
{
    for (const std::unique_ptr<Order>& p_order : orders)
    {
        if (p_order->get_order_no() == order_no)
        {
            return p_order.get();
        }
    }
    return nullptr;
}

bool Workshop::remove_order(int order_no)
{
    auto it = std::find_if(orders.begin(), orders.end(),
                           [order_no](const std::unique_ptr<Order>& p_order)
                           { return p_order->get_order_no() == order_no; });
    if (it == orders.end())
    {
        return false;
    }
    if ((*it)->get_status() != OrderStatus::DONE)
    {
        // a mechanic may still point to this order -> deleting it would leave a dangling pointer
        throw std::logic_error("Auftrag " + std::to_string(order_no) +
                               " ist noch nicht abgeschlossen");
    }

    orders.erase(it); // unique_ptr deletes the order (composition)
    return true;
}

double Workshop::get_total_revenue() const
{
    double revenue_eur = 0.0;
    for (const std::unique_ptr<Order>& p_order : orders)
    {
        if (p_order->get_status() == OrderStatus::DONE)
        {
            revenue_eur += p_order->get_price(); // dynamic dispatch: Inspection or Repair
        }
    }
    return revenue_eur;
}
