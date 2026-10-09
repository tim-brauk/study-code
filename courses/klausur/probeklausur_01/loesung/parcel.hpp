/**
 * @file parcel.hpp
 * @brief Abstract Parcel base class and the concrete parcel types.
 */

#ifndef PARCEL_HPP
#define PARCEL_HPP

#include <string>

class Courier; // forward declaration (bidirectional association)

enum class ParcelStatus
{
    IN_DEPOT,
    IN_DELIVERY,
    DELIVERED
};

class Parcel
{
private:
    static int next_tracking_no;

    const int tracking_no;
    double weight_kg;
    std::string postal_code;
    ParcelStatus status;
    Courier* p_courier; // non-owning: the courier only transports the parcel

protected:
    static const int LABEL_WIDTH = 20;

    static void print_row(const std::string& label, const std::string& value);

    // type-specific row in the middle of the table (template method pattern)
    virtual void print_specific_info() const = 0;

public:
    static constexpr double MAX_WEIGHT_KG = 31.5;

    Parcel(double weight_kg, const std::string& postal_code);
    virtual ~Parcel() = default;

    // a copy would duplicate the unique tracking number
    Parcel(const Parcel&) = delete;
    Parcel& operator=(const Parcel&) = delete;

    virtual std::string get_type() const = 0;
    virtual double get_price() const = 0; // derived attribute: calculated, never stored
    void print_info() const;

    int get_tracking_no() const
    {
        return tracking_no;
    }

    double get_weight_kg() const
    {
        return weight_kg;
    }

    void set_weight_kg(double new_weight_kg);

    const std::string& get_postal_code() const
    {
        return postal_code;
    }

    void set_postal_code(const std::string& new_postal_code)
    {
        postal_code = new_postal_code;
    }

    ParcelStatus get_status() const
    {
        return status;
    }

    void set_status(ParcelStatus new_status)
    {
        status = new_status;
    }

    Courier* get_courier() const
    {
        return p_courier;
    }

    void set_courier(Courier* p_new_courier)
    {
        p_courier = p_new_courier;
    }
};

class StandardParcel : public Parcel
{
private:
    bool bulky_goods;

protected:
    void print_specific_info() const override;

public:
    StandardParcel(double weight_kg, const std::string& postal_code, bool bulky_goods);

    std::string get_type() const override;
    double get_price() const override;

    bool is_bulky_goods() const
    {
        return bulky_goods;
    }

    void set_bulky_goods(bool is_bulky)
    {
        bulky_goods = is_bulky;
    }
};

class ExpressParcel : public Parcel
{
private:
    int delivery_time_h;

protected:
    void print_specific_info() const override;

public:
    ExpressParcel(double weight_kg, const std::string& postal_code, int delivery_time_h);

    std::string get_type() const override;
    double get_price() const override;

    int get_delivery_time_h() const
    {
        return delivery_time_h;
    }

    void set_delivery_time_h(int hours);
};

#endif
