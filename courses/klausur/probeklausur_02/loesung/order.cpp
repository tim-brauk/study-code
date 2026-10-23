/**
 * @file order.cpp
 * @brief Implements Order, Inspection and Repair.
 */

#include "order.hpp"
#include "mechanic.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
const double HOURLY_RATE_EUR = 65.00;
const double INSPECTION_BASE_FEE_EUR = 49.00;
const double MAIN_INSPECTION_FEE_EUR = 119.00;
const double LONG_REPAIR_LIMIT_H = 8.0;
const double LONG_REPAIR_LABOUR_FACTOR = 0.90; // 10 % discount on the labour costs only
const std::string MAINTENANCE_QUALIFICATION = "Maintenance";

double validated_work_hours(double work_hours)
{
    if (work_hours <= 0.0 || work_hours > Order::MAX_WORK_HOURS)
    {
        throw std::invalid_argument("Ungueltige Arbeitszeit: " + std::to_string(work_hours) +
                                    " h");
    }
    return work_hours;
}

std::string validated_text(const std::string& text, const std::string& field_name)
{
    if (text.empty())
    {
        throw std::invalid_argument(field_name + " darf nicht leer sein");
    }
    return text;
}

double validated_parts_cost(double parts_cost_eur)
{
    if (parts_cost_eur < 0.0)
    {
        throw std::invalid_argument("Materialkosten duerfen nicht negativ sein");
    }
    return parts_cost_eur;
}

std::string status_to_string(OrderStatus status)
{
    switch (status)
    {
    case OrderStatus::OPEN:
        return "Open";
    case OrderStatus::IN_PROGRESS:
        return "In Progress";
    case OrderStatus::DONE:
        return "Done";
    }
    return "Unknown";
}

std::string euro_text(double amount_eur)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << amount_eur << " EUR";
    return stream.str();
}

template <typename T>
std::string to_text(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}
} // namespace

int Order::next_order_no = 500;

Order::Order(const std::string& license_plate, double work_hours)
    : order_no(next_order_no++), license_plate(validated_text(license_plate, "Kennzeichen")),
      work_hours(validated_work_hours(work_hours)), status(OrderStatus::OPEN),
      p_mechanic(nullptr)
{
}

void Order::set_license_plate(const std::string& new_license_plate)
{
    license_plate = validated_text(new_license_plate, "Kennzeichen");
}

void Order::set_work_hours(double new_work_hours)
{
    work_hours = validated_work_hours(new_work_hours);
}

void Order::print_row(const std::string& label, const std::string& value)
{
    std::cout << std::left << std::setw(LABEL_WIDTH) << label << value << "\n";
}

void Order::print_info() const
{
    std::string mechanic_name = "None";
    if (p_mechanic != nullptr)
    {
        mechanic_name = p_mechanic->get_name();
    }

    print_row("Type", get_type());
    print_row("Order No", to_text(order_no));
    print_row("License Plate", license_plate);
    print_row("Work Hours", to_text(work_hours) + " h");
    print_row("Qualification", get_required_qualification());
    print_specific_info();
    print_row("Price", euro_text(get_price()));
    print_row("Status", status_to_string(status));
    print_row("Mechanic", mechanic_name);
    std::cout << std::string(50, '-') << "\n";
}

// ---------------------------------------------------------------- Inspection

Inspection::Inspection(const std::string& license_plate, double work_hours, bool main_inspection)
    : Order(license_plate, work_hours), main_inspection(main_inspection)
{
}

std::string Inspection::get_type() const
{
    return "Inspection";
}

std::string Inspection::get_required_qualification() const
{
    return MAINTENANCE_QUALIFICATION; // every inspection needs the same qualification
}

double Inspection::get_price() const
{
    double price = INSPECTION_BASE_FEE_EUR + HOURLY_RATE_EUR * get_work_hours();
    if (main_inspection)
    {
        price += MAIN_INSPECTION_FEE_EUR;
    }
    return price;
}

void Inspection::print_specific_info() const
{
    print_row("Main Inspection", main_inspection ? "Yes" : "No");
}

// ---------------------------------------------------------------- Repair

Repair::Repair(const std::string& license_plate, double work_hours,
               const std::string& qualification, double parts_cost_eur)
    : Order(license_plate, work_hours),
      qualification(validated_text(qualification, "Qualifikation")),
      parts_cost_eur(validated_parts_cost(parts_cost_eur))
{
}

void Repair::set_qualification(const std::string& new_qualification)
{
    qualification = validated_text(new_qualification, "Qualifikation");
}

void Repair::set_parts_cost_eur(double new_parts_cost_eur)
{
    parts_cost_eur = validated_parts_cost(new_parts_cost_eur);
}

std::string Repair::get_type() const
{
    return "Repair";
}

std::string Repair::get_required_qualification() const
{
    return qualification;
}

double Repair::get_price() const
{
    double labour_cost = HOURLY_RATE_EUR * get_work_hours();
    if (get_work_hours() > LONG_REPAIR_LIMIT_H)
    {
        labour_cost *= LONG_REPAIR_LABOUR_FACTOR;
    }
    return labour_cost + parts_cost_eur;
}

void Repair::print_specific_info() const
{
    print_row("Parts Cost", euro_text(parts_cost_eur));
}
