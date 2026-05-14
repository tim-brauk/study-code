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

Some situations indicate severe system problems and should therefore be handled using exceptions:

* a sensor becomes unreachable
* physically impossible measurements are received
* a sensor configuration is corrupted (i.e. minimum limits > maximum limits)
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

Use catch blocks directly after the try statements in the main. The catch-statement should use a parameter of type ```std::exception```.

Use the what-method to output the catched exception message.

### Question
- What would happen to an object if you throw an exception within its constructor?

---

## 🟢 Part 2: Multiple Catch Blocks

Extend your program so that different exception types are handled separately. Moreover, use only one try block for all tests.

Also, all catch-statements should be located together - not being called directly after a try-block.

- Discuss why the order of `catch` blocks matters.
- What is the difference between calling every test case in a separate try block or in one common try block.

---

## 🟡 Part 3: Custom Exception Classes

Create a custom exception class called __SensorFailureError__ representing a specialized form of a runtime error.

It should return the error message ```Sensor is unreachable```.

Then add a method:

```cpp
simulate_failure()
```

This method should throw `SensorFailureError`.
Catch this exception in `main()`.

---

## Reflection Questions

1. Why are exceptions preferable to integer error codes in this system?
2. Why should exceptions usually be caught by `const` reference?
3. What is the difference between `std::invalid_argument`, `std::runtime_error`, and `std::out_of_range`?
4. When should custom exception classes be used?
5. Why should `catch (const std::exception& e)` usually appear after more specific `catch` blocks?
6. Why should exceptions not be used for normal control flow?
7. What happens if an exception is never caught?

## Section II: Smart Pointers

In this section you will practice memory management using smart pointers in C++.

You will practice the following concepts:

* `std::unique_ptr`
* `std::shared_ptr`
* `make_unique` and `make_shared`

---

## Task Description

You are part of a software engineering team developing a streaming platform.

The platform manages different types of media devices:

* speakers
* displays
* microphones

Devices can either:

* belong exclusively to one room
* or be shared between multiple rooms

The system should use smart pointers instead of raw pointers for memory management.

---

## 🟡 Part 1: `std::unique_ptr`

Create a class `Device`.

The class should contain:

1. device name
2. device type
3. power status

Add methods:

1. `turn_on()`
2. `turn_off()`
3. `print_info()`

Add a destructor that outputs a message when a device is destroyed.

---

Create a class `Room`.

The class should contain:

1. room name
2. a collection of devices

Rules:

* each device belongs to exactly one room
* devices must be managed using `std::unique_ptr`
* use `std::make_unique` when creating devices

Add methods:

1. `add_device(...)`
2. `remove_device(...)`
3. `print_devices()`

---

### Testing in `main()`

Create multiple rooms and devices.

Move devices into rooms using:

```cpp
std::move(...)
```

After moving, test whether the original pointer became `nullptr`.

---

## 🟡 Part 2: Ownership Semantics

Answer the following questions by experimenting with code:

1. What happens if you try to copy a `std::unique_ptr`?
2. Why is `std::move(...)` required?
3. What happens to the original pointer after moving?
4. When is the destructor automatically called?

---

## 🟠 Part 3: `std::shared_ptr`

Some devices should be shareable between multiple rooms.

Example:

* a central music server
* a network storage device

Create a class `SharedDevice`.

The class should contain:

1. device name
2. device type

Use:

```cpp
std::shared_ptr
```

to manage these devices.

---

Modify the `Room` class so that rooms may also contain shared devices.

Add methods:

1. `add_shared_device(...)`
2. `print_shared_devices()`

Use:

```cpp
std::make_shared(...)
```

when creating shared devices.

---

### Example

```cpp
std::shared_ptr<SharedDevice> server =
    std::make_shared<SharedDevice>(
        "Main Server",
        "Streaming"
    );
```

Add the same shared device to multiple rooms.

---

### Testing in `main()`

Use:

```cpp
use_count()
```

to observe shared ownership.

Example:

```cpp
std::cout << server.use_count()
          << std::endl;
```

Check the reference counter:

1. after creation
2. after adding to rooms
3. after rooms are destroyed

---

## 🔴 Part 4: Comparing `unique_ptr` and `shared_ptr`

Experiment with both smart pointer types and answer the following questions:

1. Which pointer type supports exclusive ownership?
2. Which pointer type supports shared ownership?
3. Which pointer type has less overhead?
4. Why can `shared_ptr` be more expensive?
5. In which situations should `unique_ptr` be preferred?
6. When is `shared_ptr` appropriate?

---

## Requirements

Your solution must contain:

1. at least one `std::unique_ptr`
2. at least one `std::shared_ptr`
3. usage of `std::move(...)`
4. usage of `make_unique`
5. usage of `make_shared`
6. at least one destructor output
7. at least one `use_count()` test

---

## Reflection Questions

1. Why are smart pointers safer than raw pointers?
2. What problem does `std::unique_ptr` solve?
3. Why can `std::unique_ptr` not be copied?
4. What problem does `std::shared_ptr` solve?
5. What does `use_count()` represent?
6. Why can cyclic references become problematic with `std::shared_ptr`?
7. Which smart pointer should usually be preferred in modern C++?