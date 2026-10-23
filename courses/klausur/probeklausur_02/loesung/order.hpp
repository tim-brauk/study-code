/**
 * @file order.hpp
 * @brief Abstract Order base class and the concrete order types.
 */

#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>

class Mechanic; // forward declaration (bidirectional association)

enum class OrderStatus
{
    OPEN,
    IN_PROGRESS,
    DONE
};

class Order
{
private:
    static int next_order_no;

    const int order_no;
    std::string license_plate;
    double work_hours;
    OrderStatus status;
    Mechanic* p_mechanic; // non-owning: the mechanic only works on the order

protected:
    static const int LABEL_WIDTH = 20;

    static void print_row(const std::string& label, const std::string& value);

    // type-specific rows in the middle of the table (template method pattern)
    virtual void print_specific_info() const = 0;

public:
    static constexpr double MAX_WORK_HOURS = 40.0;

    Order(const std::string& license_plate, double work_hours);
    virtual ~Order() = default;

    // a copy would duplicate the unique order number and the mechanic assignment
    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;

    virtual std::string get_type() const = 0;
    virtual std::string get_required_qualification() const = 0;
    virtual double get_price() const = 0; // derived attribute: calculated, never stored
    void print_info() const;

    int get_order_no() const
    {
        return order_no;
    }

    const std::string& get_license_plate() const
    {
        return license_plate;
    }

    void set_license_plate(const std::string& new_license_plate);

    double get_work_hours() const
    {
        return work_hours;
    }

    void set_work_hours(double new_work_hours);

    OrderStatus get_status() const
    {
        return status;
    }

    void set_status(OrderStatus new_status)
    {
        status = new_status;
    }

    Mechanic* get_mechanic() const
    {
        return p_mechanic;
    }

    void set_mechanic(Mechanic* p_new_mechanic)
    {
        p_mechanic = p_new_mechanic;
    }
};

class Inspection : public Order
{
private:
    bool main_inspection;

protected:
    void print_specific_info() const override;

public:
    Inspection(const std::string& license_plate, double work_hours, bool main_inspection);

    std::string get_type() const override;
    std::string get_required_qualification() const override;
    double get_price() const override;

    bool has_main_inspection() const
    {
        return main_inspection;
    }

    void set_main_inspection(bool with_main_inspection)
    {
        main_inspection = with_main_inspection;
    }
};

class Repair : public Order
{
private:
    std::string qualification;
    double parts_cost_eur;

protected:
    void print_specific_info() const override;

public:
    Repair(const std::string& license_plate, double work_hours, const std::string& qualification,
           double parts_cost_eur);

    std::string get_type() const override;
    std::string get_required_qualification() const override;
    double get_price() const override;

    void set_qualification(const std::string& new_qualification);

    double get_parts_cost_eur() const
    {
        return parts_cost_eur;
    }

    void set_parts_cost_eur(double new_parts_cost_eur);
};

#endif
