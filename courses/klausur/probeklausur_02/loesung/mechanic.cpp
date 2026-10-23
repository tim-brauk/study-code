/**
 * @file mechanic.cpp
 * @brief Implements the Mechanic class.
 */

#include "mechanic.hpp"
#include "order.hpp"

#include <algorithm>
#include <stdexcept>

namespace
{
double validated_max_hours(double max_hours)
{
    if (max_hours <= 0.0)
    {
        throw std::invalid_argument("Maximale Arbeitszeit muss > 0 h sein");
    }
    return max_hours;
}
} // namespace

int Mechanic::next_id = 1;

Mechanic::Mechanic(const std::string& name, double max_hours)
    : id(next_id++), name(name), max_hours(validated_max_hours(max_hours))
{
}

void Mechanic::set_max_hours(double new_max_hours)
{
    max_hours = validated_max_hours(new_max_hours);
}

void Mechanic::add_qualification(const std::string& qualification)
{
    qualifications.insert(qualification);
}

bool Mechanic::remove_qualification(const std::string& qualification)
{
    return qualifications.erase(qualification) > 0;
}

bool Mechanic::has_qualification(const std::string& qualification) const
{
    return qualifications.find(qualification) != qualifications.end();
}

double Mechanic::get_current_workload_h() const
{
    double workload_h = 0.0;
    for (const Order* p_order : assigned_orders)
    {
        workload_h += p_order->get_work_hours();
    }
    return workload_h;
}

bool Mechanic::assign_order(Order& order)
{
    if (order.get_status() != OrderStatus::OPEN)
    {
        return false;
    }
    if (!has_qualification(order.get_required_qualification()))
    {
        return false;
    }
    if (get_current_workload_h() + order.get_work_hours() > max_hours)
    {
        return false;
    }

    assigned_orders.push_back(&order);
    order.set_mechanic(this);
    order.set_status(OrderStatus::IN_PROGRESS);
    return true;
}

bool Mechanic::finish_order(int order_no)
{
    auto it = std::find_if(assigned_orders.begin(), assigned_orders.end(),
                           [order_no](const Order* p_order)
                           { return p_order->get_order_no() == order_no; });
    if (it == assigned_orders.end())
    {
        return false;
    }

    (*it)->set_status(OrderStatus::DONE); // the order keeps its mechanic ("done by")
    assigned_orders.erase(it);            // only the link is removed, nothing is deleted
    return true;
}
