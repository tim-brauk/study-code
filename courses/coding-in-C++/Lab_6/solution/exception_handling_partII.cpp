#include <iostream>
#include <stdexcept>
#include <string>

class Sensor
{
private:
    std::string name;
    double current_value;
    const double min_value;
    const double max_value;

public:
    // if an exception is thrown from within a constructor
    // the object in creation is automatically deleted
    Sensor(const std::string &sensor_name,
           double initial_value,
           double minimum_value,
           double maximum_value)
        : name(sensor_name),
          current_value(initial_value),
          min_value(minimum_value),
          max_value(maximum_value)
    {
        if (minimum_value > maximum_value)
        {
            throw std::invalid_argument("Invalid sensor configuration: minimum value is greater than maximum value");
        }

        update_value(initial_value);
    }

    void update_value(double value)
    {
        if (value < min_value || value > max_value)
        {
            throw std::out_of_range("Impossible sensor value detected");
        }

        current_value = value;
    }

    double get_value() const
    {
        return current_value;
    }

    void print_info() const
    {
        std::cout << "Sensor: " << name << std::endl;
        std::cout << "Current value: " << current_value << std::endl;
        std::cout << "Allowed range: "
                  << min_value << " to "
                  << max_value << std::endl;
    }
};

int main()
{
    try
    {
        Sensor temperature_sensor("Temperature Sensor", 20.0, -273.15, 80.0);
        temperature_sensor.update_value(-500.0);

        Sensor humidity_sensor("Humidity Sensor", 50.0, 0.0, 100.0);
        humidity_sensor.update_value(150.0);

        Sensor water_level_sensor("Water Level Sensor", 30.0, 0.0, 100.0);
        water_level_sensor.update_value(-10.0);
    }

    catch (const std::out_of_range &error)
    {
        std::cout << "Water level error: "
                  << error.what()
                  << std::endl;
    }

    catch (const std::invalid_argument &error)
    {
        std::cout << "Temperature error: "
                  << error.what()
                  << std::endl;
    }

    catch (const std::exception &error)
    {
        std::cout << "Humidity error: "
                  << error.what()
                  << std::endl;
    }

    return 0;
}