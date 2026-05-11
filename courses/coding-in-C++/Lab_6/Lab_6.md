# Lab 6: Exception Handling & Smart Pointer

This lab focuses on **Exception Handling & SMart Pointer in C++**.

You will practice the following concepts:

* `try`, `throw`, and `catch`
* standard exceptions
* custom exception classes
* unique pointer
* shared pointer


All the following sections of this lab are based on the following levels of dificulty:

🟢 __Simple__: A simple coding task that usually guides you step by step through the process and focuses on learning the basics. It should not take more than 15min to finish it. 

🟡 __Moderate__: A coding task that usually states a moderate problem to test your understanding and transfer skills from syntax to real-world applications. These tasks can be solved in about 30mins depending on your knowledge.

🔴 __Complex__: Quite a difficult or lengthy coding task that requires you to use the acquired knowledge of the previous tasks in a broader context or project. Such tasks might take up to a few hours to solve them.

---

## 🟡 Section I: Exception Handling

In this section you will practice exception handling in C++.

You will practice the following concepts:

* `try`, `throw`, and `catch`
* standard exceptions
* custom exception classes
* exception propagation

---

## Task Description

You are part of a software engineering team developing a monitoring system for a smart greenhouse.

The system continuously reads data from different sensors:

* temperature sensors
* humidity sensors
* water level sensors

Normal user input errors should be handled with regular validation logic.

However, some situations indicate severe system problems and should therefore be handled using exceptions:

* a sensor becomes unreachable
* physically impossible measurements are received
* a sensor configuration is corrupted
* irrigation is activated although no water is available

The system should use exceptions to detect and handle these exceptional situations.

---

## 🟢 Part 1: Standard Exceptions

Create a class `Sensor`.

The class should contain:

1. sensor name
2. current value
3. minimum physically possible value
4. maximum physically possible value

Add methods:

1. `update_value(double value)`
2. `get_value()`
3. `print_info()`

Rules:

* impossible sensor values should throw `std::out_of_range`
* invalid sensor configurations should throw `std::invalid_argument`

Examples:

* humidity below `0%`
* humidity above `100%`
* temperature below `-273.15°C`

### Testing Exceptions in `main()`

Create three sensors to measure the above mentioned states and intentionally trigger invalid situations.
Use the what-method to output the catched exception.

---

## Part 2 – Moderate: Multiple Catch Blocks

Extend your program so that different exception types are handled separately.

Example:

```cpp
try
{
    humidity_sensor.update_value(250);
}
catch (const std::invalid_argument& error)
{
    std::cout << "Configuration error: "
              << error.what()
              << std::endl;
}
catch (const std::out_of_range& error)
{
    std::cout << "Impossible sensor value: "
              << error.what()
              << std::endl;
}
catch (const std::exception& error)
{
    std::cout << "General error: "
              << error.what()
              << std::endl;
}
```

Discuss why the order of `catch` blocks matters.

---

## Part 3 – Moderate: Custom Exception Classes

Create a custom exception class:

```cpp
class SensorFailureError : public std::runtime_error
{
public:
    SensorFailureError()
        : std::runtime_error("Sensor is unreachable")
    {
    }
};
```

Add a method:

```cpp
simulate_failure()
```

This method should throw `SensorFailureError`.

Example:

```cpp
void Sensor::simulate_failure()
{
    throw SensorFailureError();
}
```

Catch this exception separately in `main()`.

Example:

```cpp
try
{
    sensor.simulate_failure();
}
catch (const SensorFailureError& error)
{
    std::cout << error.what()
              << std::endl;
}
```

---

## Part 4 – Complex: Greenhouse Controller

Create a class `GreenhouseController`.

The class should manage multiple sensors.

Add methods:

1. `add_sensor(...)`
2. `read_sensor(...)`
3. `check_system_status()`
4. `activate_irrigation()`

Rules:

* invalid sensor indices should throw `std::out_of_range`
* sensor failures should propagate through the system
* irrigation activation without water should throw `std::runtime_error`
* severe sensor errors should not be silently ignored

Handle exceptions at the application level in `main()`.

Example:

```cpp
try
{
    controller.activate_irrigation();
}
catch (const std::runtime_error& error)
{
    std::cout << error.what()
              << std::endl;
}
```

---

## Requirements

Your solution must contain:

1. at least three different standard exceptions
2. at least one custom exception class
3. multiple `catch` blocks
4. exception propagation across multiple function calls
5. exceptions caught as `const` reference
6. no integer error codes

---

## Reflection Questions

1. Why are exceptions preferable to integer error codes in this system?
2. Which situations in this exercise are truly exceptional?
3. Why should exceptions usually be caught by `const` reference?
4. What is the difference between `std::invalid_argument`, `std::runtime_error`, and `std::out_of_range`?
5. When should custom exception classes be used?
6. Why should `catch (const std::exception& e)` usually appear after more specific `catch` blocks?
7. Why should exceptions not be used for normal control flow?
8. What happens if an exception is never caught?