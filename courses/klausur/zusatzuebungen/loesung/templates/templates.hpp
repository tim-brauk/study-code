/**
 * @file templates.hpp
 * @brief Generic helper functions and the RingBuffer class template (Aufgabe 3).
 *
 * Templates must be fully defined in the header, because the compiler needs the
 * complete definition to instantiate them for each used type.
 */

#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <array>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * @brief Limits value to [low, high].
 * @throws std::invalid_argument if low > high
 */
template <typename T>
T clamp_value(const T& value, const T& low, const T& high)
{
    if (high < low)
    {
        throw std::invalid_argument("clamp_value: low > high");
    }
    if (value < low)
    {
        return low;
    }
    if (high < value)
    {
        return high;
    }
    return value;
}

/**
 * @brief Arithmetic mean of any container with begin()/end() and size().
 * @throws std::domain_error if the container is empty
 */
template <typename Container>
double average(const Container& values)
{
    if (values.empty())
    {
        throw std::domain_error("average: leerer Container");
    }
    double sum = 0.0;
    for (const auto& value : values)
    {
        sum += static_cast<double>(value);
    }
    return sum / static_cast<double>(values.size());
}

/**
 * @brief Fixed-size circular buffer that overwrites the oldest value when full.
 */
template <typename T, std::size_t N>
class RingBuffer
{
private:
    std::array<T, N> data{};
    std::size_t start = 0; // index of the oldest element
    std::size_t count = 0;

public:
    void push(const T& value)
    {
        if (count < N)
        {
            data[(start + count) % N] = value;
            count++;
        }
        else
        {
            data[start] = value; // overwrite the oldest one
            start = (start + 1) % N;
        }
    }

    /**
     * @param[in] index 0 = oldest stored value
     * @throws std::out_of_range if index >= size()
     */
    const T& at(std::size_t index) const
    {
        if (index >= count)
        {
            throw std::out_of_range("RingBuffer::at: Index ausserhalb");
        }
        return data[(start + index) % N];
    }

    std::size_t size() const
    {
        return count;
    }

    bool is_full() const
    {
        return count == N;
    }
};

/**
 * @brief Generic description "Wert: <value>".
 */
template <typename T>
std::string describe(const T& value)
{
    std::ostringstream stream;
    stream << "Wert: " << value;
    return stream.str();
}

/**
 * @brief Explicit specialization for bool: "Wert: ja" / "Wert: nein".
 *
 * `inline` is required because a full specialization is a normal function and would
 * otherwise violate the one-definition rule if the header is included twice.
 */
template <>
inline std::string describe<bool>(const bool& value)
{
    return value ? "Wert: ja" : "Wert: nein";
}

#endif
