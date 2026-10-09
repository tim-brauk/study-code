/**
 * @file scale_adapter.cpp
 * @brief Object adapter that makes the legacy OldScale usable as WeightSensor (Aufgabe 5c).
 *
 * In der Klausur gehoeren WeightSensor und ScaleAdapter in eigene .hpp-Dateien; hier
 * kompakt in einer Datei, damit die Loesung uebersichtlich bleibt.
 */

#include "../../design/old_scale.hpp"

#include <iostream>
#include <stdexcept>

/** @brief Target interface expected by the new depot system. */
class WeightSensor
{
public:
    virtual ~WeightSensor() = default;

    /** @return Measured weight in kg */
    virtual double weight_kg() const = 0;
};

/**
 * @brief Object adapter: implements WeightSensor and delegates to a wrapped OldScale.
 *
 * Composition instead of inheriting from OldScale, so the adapter does not expose the
 * legacy interface and works with any existing OldScale object.
 */
class ScaleAdapter : public WeightSensor
{
private:
    const OldScale& scale;

    static constexpr double GRAMS_PER_KG = 1000.0;

public:
    explicit ScaleAdapter(const OldScale& scale) : scale(scale)
    {
    }

    /** @throws std::runtime_error if the legacy scale is not calibrated */
    double weight_kg() const override
    {
        if (!scale.is_calibrated())
        {
            throw std::runtime_error("Waage nicht kalibriert");
        }
        return scale.read_grams() / GRAMS_PER_KG;
    }
};

void weigh(const WeightSensor& sensor)
{
    double weight = sensor.weight_kg(); // may throw before anything is printed
    std::cout << "Gewicht: " << weight << " kg\n";
}

int main()
{
    OldScale good_scale(2350);
    OldScale broken_scale(500, false);

    ScaleAdapter good_adapter(good_scale);
    ScaleAdapter broken_adapter(broken_scale);

    weigh(good_adapter);
    try
    {
        weigh(broken_adapter);
    }
    catch (const std::runtime_error& error)
    {
        std::cout << "Fehler: " << error.what() << "\n";
    }
    return 0;
}
