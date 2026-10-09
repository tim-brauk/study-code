/**
 * @file old_scale.hpp
 * @brief Legacy-Waage aus dem alten Depotsystem. DARF NICHT VERAENDERT WERDEN.
 */

#ifndef OLD_SCALE_HPP
#define OLD_SCALE_HPP

class OldScale
{
public:
    explicit OldScale(int simulated_grams, bool calibrated = true)
        : grams(simulated_grams), calibrated(calibrated)
    {
    }

    /** @brief Liefert das gemessene Gewicht in Gramm. */
    int read_grams() const
    {
        return grams;
    }

    /** @brief true, wenn die Waage kalibriert ist und die Messung gueltig ist. */
    bool is_calibrated() const
    {
        return calibrated;
    }

private:
    int grams;
    bool calibrated;
};

#endif
