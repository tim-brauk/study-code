/**
 * @file test_loesung.cpp
 * @brief Self-contained tests for the Musterloesung of Probeklausur 02.
 *
 * Build (from the loesung folder):
 *   g++ -std=c++17 -Wall -Wextra -pedantic -Werror -I. tests/test_loesung.cpp
 *       order.cpp mechanic.cpp workshop.cpp -o test_loesung
 *
 * Every requirement of the exam sheet is covered by at least one CHECK. The order numbers
 * and mechanic IDs are static counters, so test_print_info_matches_exam() must run first
 * (it needs the numbers 500 and 501 from the exam example).
 */

#include "mechanic.hpp"
#include "order.hpp"
#include "workshop.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace
{
int checks_passed = 0;
int checks_failed = 0;

void report(bool ok, const std::string& description, int line)
{
    if (ok)
    {
        checks_passed++;
    }
    else
    {
        checks_failed++;
        std::cout << "  FAILED (line " << line << "): " << description << "\n";
    }
}

#define CHECK(condition) report((condition), #condition, __LINE__)

#define CHECK_NEAR(actual, expected)                                                           \
    report(std::fabs((actual) - (expected)) < 1e-9, #actual " == " #expected, __LINE__)

// passes only if exactly this exception type (not a subclass/base class) is thrown
#define CHECK_THROWS_EXACT(statement, exception_type)                                          \
    do                                                                                         \
    {                                                                                          \
        bool thrown_exact = false;                                                             \
        try                                                                                    \
        {                                                                                      \
            statement;                                                                         \
        }                                                                                      \
        catch (const std::exception& error)                                                    \
        {                                                                                      \
            thrown_exact = typeid(error) == typeid(exception_type);                            \
        }                                                                                      \
        report(thrown_exact, #statement " throws " #exception_type, __LINE__);                 \
    } while (false)

#define CHECK_NO_THROW(statement)                                                              \
    do                                                                                         \
    {                                                                                          \
        bool thrown = false;                                                                   \
        try                                                                                    \
        {                                                                                      \
            statement;                                                                         \
        }                                                                                      \
        catch (...)                                                                            \
        {                                                                                      \
            thrown = true;                                                                     \
        }                                                                                      \
        report(!thrown, #statement " does not throw", __LINE__);                               \
    } while (false)

std::string captured_print(const Order& order)
{
    std::ostringstream buffer;
    std::streambuf* p_old_buffer = std::cout.rdbuf(buffer.rdbuf());
    order.print_info();
    std::cout.rdbuf(p_old_buffer);
    return buffer.str();
}

// counts destructor calls to prove composition + virtual destructor
class CountingOrder : public Order
{
public:
    static int destroyed;

    CountingOrder() : Order("TEST 1", 1.0)
    {
    }

    ~CountingOrder() override
    {
        destroyed++;
    }

    std::string get_type() const override
    {
        return "Counting";
    }

    std::string get_required_qualification() const override
    {
        return "Maintenance";
    }

    double get_price() const override
    {
        return 0.0;
    }

protected:
    void print_specific_info() const override
    {
    }
};

int CountingOrder::destroyed = 0;

void run(const std::string& name, void (*p_test)())
{
    int failed_before = checks_failed;
    p_test();
    std::cout << (checks_failed == failed_before ? "[ OK ] " : "[FAIL] ") << name << "\n";
}

// ------------------------------------------------------------------------------ tests

void test_print_info_matches_exam()
{
    Inspection inspection("RV-AB 123", 1.5, true);
    Repair repair("FN-XY 42", 10.0, "Engine", 350.0);
    Mechanic lena("Lena Vogt", 11.0);
    lena.add_qualification("Engine");
    CHECK(lena.assign_order(repair));

    // copied literally from Probeklausur_02.md
    const std::string expected_inspection = "Type                Inspection\n"
                                            "Order No            500\n"
                                            "License Plate       RV-AB 123\n"
                                            "Work Hours          1.5 h\n"
                                            "Qualification       Maintenance\n"
                                            "Main Inspection     Yes\n"
                                            "Price               265.50 EUR\n"
                                            "Status              Open\n"
                                            "Mechanic            None\n"
                                            "--------------------------------------------------\n";
    const std::string expected_repair = "Type                Repair\n"
                                        "Order No            501\n"
                                        "License Plate       FN-XY 42\n"
                                        "Work Hours          10 h\n"
                                        "Qualification       Engine\n"
                                        "Parts Cost          350.00 EUR\n"
                                        "Price               935.00 EUR\n"
                                        "Status              In Progress\n"
                                        "Mechanic            Lena Vogt\n"
                                        "--------------------------------------------------\n";

    CHECK(captured_print(inspection) == expected_inspection);
    CHECK(captured_print(repair) == expected_repair);

    // print_info must also work through a base class reference (dynamic dispatch)
    const Order& base = repair;
    CHECK(captured_print(base) == expected_repair);

    CHECK(lena.finish_order(501));
    CHECK(captured_print(repair).find("Status              Done\n") != std::string::npos);
}

void test_class_design()
{
    static_assert(std::is_abstract<Order>::value, "Order must be abstract");
    static_assert(std::has_virtual_destructor<Order>::value, "virtual destructor needed");
    static_assert(!std::is_copy_constructible<Order>::value, "Order copy must be deleted");
    static_assert(!std::is_copy_assignable<Order>::value, "Order assignment must be deleted");
    static_assert(!std::is_copy_constructible<Mechanic>::value, "Mechanic copy deleted");
    static_assert(!std::is_copy_assignable<Mechanic>::value, "Mechanic assignment deleted");
    static_assert(std::is_base_of<Order, Inspection>::value, "Inspection is an Order");
    static_assert(std::is_base_of<Order, Repair>::value, "Repair is an Order");
    static_assert(!std::is_convertible<int, OrderStatus>::value, "status must be type-safe");
    static_assert(!std::is_convertible<OrderStatus, int>::value, "status must be type-safe");
    CHECK_NEAR(Order::MAX_WORK_HOURS, 40.0);
}

void test_order_numbers_are_unique_and_increasing()
{
    Inspection first("A 1", 1.0, false);
    Repair second("A 2", 1.0, "Body", 0.0);
    Inspection third("A 3", 1.0, false);
    CHECK(second.get_order_no() == first.get_order_no() + 1);
    CHECK(third.get_order_no() == second.get_order_no() + 1);
}

void test_new_order_is_open_without_mechanic()
{
    Repair repair("A 1", 2.0, "Engine", 10.0);
    CHECK(repair.get_status() == OrderStatus::OPEN);
    CHECK(repair.get_mechanic() == nullptr);
}

void test_inspection_price()
{
    Inspection without_hu("A 1", 2.0, false);
    CHECK_NEAR(without_hu.get_price(), 49.0 + 2.0 * 65.0); // 179.00

    Inspection with_hu("A 1", 1.5, true);
    CHECK_NEAR(with_hu.get_price(), 265.5);

    // price is derived, not stored: changing an attribute changes the price immediately
    with_hu.set_main_inspection(false);
    CHECK_NEAR(with_hu.get_price(), 146.5);
    with_hu.set_work_hours(3.0);
    CHECK_NEAR(with_hu.get_price(), 49.0 + 195.0);
}

void test_repair_price_and_discount_boundary()
{
    Repair short_repair("A 1", 3.0, "Electrics", 120.0);
    CHECK_NEAR(short_repair.get_price(), 315.0);

    Repair exactly_eight("A 1", 8.0, "Engine", 0.0); // "mehr als 8 h" -> no discount at 8 h
    CHECK_NEAR(exactly_eight.get_price(), 520.0);

    Repair long_repair("A 1", 10.0, "Engine", 350.0); // discount only on labour
    CHECK_NEAR(long_repair.get_price(), 935.0);

    long_repair.set_parts_cost_eur(0.0);
    CHECK_NEAR(long_repair.get_price(), 585.0);
    long_repair.set_work_hours(8.5);
    CHECK_NEAR(long_repair.get_price(), 8.5 * 65.0 * 0.9);
}

void test_required_qualification_is_polymorphic()
{
    std::unique_ptr<Order> p_inspection = std::make_unique<Inspection>("A 1", 1.0, false);
    std::unique_ptr<Order> p_repair = std::make_unique<Repair>("A 2", 1.0, "Body", 0.0);
    CHECK(p_inspection->get_required_qualification() == "Maintenance");
    CHECK(p_repair->get_required_qualification() == "Body");
    CHECK(p_inspection->get_type() == "Inspection");
    CHECK(p_repair->get_type() == "Repair");
}

void test_order_validation()
{
    CHECK_THROWS_EXACT(Inspection("A 1", 0.0, false), std::invalid_argument);
    CHECK_THROWS_EXACT(Inspection("A 1", -1.0, false), std::invalid_argument);
    CHECK_THROWS_EXACT(Inspection("A 1", 40.01, false), std::invalid_argument);
    CHECK_NO_THROW(Inspection("A 1", 40.0, false));
    CHECK_NO_THROW(Inspection("A 1", 0.1, false));
    CHECK_THROWS_EXACT(Inspection("", 1.0, false), std::invalid_argument);
    CHECK_THROWS_EXACT(Repair("A 1", 1.0, "Engine", -0.01), std::invalid_argument);
    CHECK_NO_THROW(Repair("A 1", 1.0, "Engine", 0.0));
    CHECK_THROWS_EXACT(Repair("A 1", 1.0, "", 10.0), std::invalid_argument);
    CHECK_THROWS_EXACT(Repair("A 1", 50.0, "Engine", 10.0), std::invalid_argument);

    // setters must validate too, and keep the old value on failure
    Repair repair("A 1", 2.0, "Engine", 10.0);
    CHECK_THROWS_EXACT(repair.set_work_hours(0.0), std::invalid_argument);
    CHECK_THROWS_EXACT(repair.set_work_hours(41.0), std::invalid_argument);
    CHECK_NEAR(repair.get_work_hours(), 2.0);
    CHECK_THROWS_EXACT(repair.set_parts_cost_eur(-5.0), std::invalid_argument);
    CHECK_NEAR(repair.get_parts_cost_eur(), 10.0);
    CHECK_THROWS_EXACT(repair.set_license_plate(""), std::invalid_argument);
    CHECK(repair.get_license_plate() == "A 1");
    CHECK_THROWS_EXACT(repair.set_qualification(""), std::invalid_argument);
    CHECK(repair.get_required_qualification() == "Engine");
}

void test_mechanic_ids_and_validation()
{
    Mechanic first("A", 8.0);
    Mechanic second("B", 8.0);
    CHECK(second.get_id() == first.get_id() + 1);

    CHECK_THROWS_EXACT(Mechanic("C", 0.0), std::invalid_argument);
    CHECK_THROWS_EXACT(Mechanic("C", -3.0), std::invalid_argument);
    CHECK_THROWS_EXACT(first.set_max_hours(0.0), std::invalid_argument);
    CHECK_NEAR(first.get_max_hours(), 8.0);
    first.set_max_hours(20.0);
    CHECK_NEAR(first.get_max_hours(), 20.0);
}

void test_mechanic_qualifications()
{
    Mechanic mechanic("A", 8.0);
    CHECK(!mechanic.has_qualification("Engine"));
    mechanic.add_qualification("Engine");
    mechanic.add_qualification("Engine"); // no duplicates
    mechanic.add_qualification("Body");
    CHECK(mechanic.has_qualification("Engine"));
    CHECK(mechanic.get_qualifications().size() == 2);
    CHECK(mechanic.remove_qualification("Engine"));
    CHECK(!mechanic.remove_qualification("Engine"));
    CHECK(!mechanic.has_qualification("Engine"));
    CHECK(mechanic.has_qualification("Body"));
}

void test_assign_success_sets_both_sides()
{
    Mechanic mechanic("A", 8.0);
    mechanic.add_qualification("Maintenance");
    Inspection inspection("A 1", 2.0, false);

    CHECK(mechanic.assign_order(inspection));
    CHECK(inspection.get_status() == OrderStatus::IN_PROGRESS);
    CHECK(inspection.get_mechanic() == &mechanic);
    CHECK(mechanic.get_assigned_orders().size() == 1);
    CHECK(mechanic.get_assigned_orders()[0] == &inspection);
    CHECK_NEAR(mechanic.get_current_workload_h(), 2.0);
}

void test_assign_rejections_change_nothing()
{
    Mechanic mechanic("A", 5.0);
    mechanic.add_qualification("Maintenance");

    // 1) missing qualification
    Repair engine_repair("A 1", 1.0, "Engine", 0.0);
    CHECK(!mechanic.assign_order(engine_repair));
    CHECK(engine_repair.get_status() == OrderStatus::OPEN);
    CHECK(engine_repair.get_mechanic() == nullptr);

    // 2) workload exceeded (boundary: exactly max_hours is allowed)
    Inspection four_hours("A 2", 4.0, false);
    Inspection one_hour("A 3", 1.0, false);
    Inspection tiny("A 4", 0.5, false);
    CHECK(mechanic.assign_order(four_hours));
    CHECK(mechanic.assign_order(one_hour)); // 4 + 1 == 5 -> still ok
    CHECK_NEAR(mechanic.get_current_workload_h(), 5.0);
    CHECK(!mechanic.assign_order(tiny));
    CHECK(tiny.get_status() == OrderStatus::OPEN);
    CHECK(tiny.get_mechanic() == nullptr);

    // 3) order not open: already assigned (same or other mechanic) or done
    Mechanic other("B", 40.0);
    other.add_qualification("Maintenance");
    CHECK(!other.assign_order(four_hours));
    CHECK(four_hours.get_mechanic() == &mechanic);
    CHECK(mechanic.finish_order(four_hours.get_order_no()));
    CHECK(!other.assign_order(four_hours));
    CHECK(!mechanic.assign_order(four_hours));
    CHECK(other.get_assigned_orders().empty());
    CHECK(mechanic.get_assigned_orders().size() == 1);
}

void test_finish_order()
{
    Mechanic mechanic("A", 20.0);
    mechanic.add_qualification("Maintenance");
    mechanic.add_qualification("Engine");
    Inspection inspection("A 1", 2.0, false);
    Repair repair("A 2", 3.0, "Engine", 0.0);
    CHECK(mechanic.assign_order(inspection));
    CHECK(mechanic.assign_order(repair));

    CHECK(!mechanic.finish_order(-1)); // unknown order number
    CHECK(mechanic.finish_order(inspection.get_order_no()));
    CHECK(inspection.get_status() == OrderStatus::DONE);
    CHECK(inspection.get_mechanic() == &mechanic); // keeps "done by"
    CHECK(mechanic.get_assigned_orders().size() == 1);
    CHECK(mechanic.get_assigned_orders()[0] == &repair);
    CHECK_NEAR(mechanic.get_current_workload_h(), 3.0);
    CHECK(!mechanic.finish_order(inspection.get_order_no())); // not assigned anymore

    Mechanic other("B", 20.0);
    CHECK(!other.finish_order(repair.get_order_no())); // order of another mechanic
    CHECK(repair.get_status() == OrderStatus::IN_PROGRESS);
}

void test_workshop_add_find_remove()
{
    Workshop workshop("W");
    CHECK(workshop.get_name() == "W");
    CHECK_THROWS_EXACT(workshop.add_order(nullptr), std::invalid_argument);
    CHECK(workshop.get_orders().empty());

    auto p_inspection = std::make_unique<Inspection>("A 1", 1.0, false);
    Inspection* p_raw = p_inspection.get();
    int order_no = p_raw->get_order_no();
    workshop.add_order(std::move(p_inspection));
    CHECK(workshop.find_order(order_no) == p_raw);
    CHECK(workshop.find_order(-1) == nullptr);

    // open and in progress orders must not be removed
    CHECK_THROWS_EXACT(workshop.remove_order(order_no), std::logic_error);
    Mechanic mechanic("A", 8.0);
    mechanic.add_qualification("Maintenance");
    CHECK(mechanic.assign_order(*p_raw));
    CHECK_THROWS_EXACT(workshop.remove_order(order_no), std::logic_error);
    CHECK(workshop.get_orders().size() == 1);

    CHECK(mechanic.finish_order(order_no));
    CHECK(workshop.remove_order(order_no));
    CHECK(workshop.find_order(order_no) == nullptr);
    CHECK(workshop.get_orders().empty());
    CHECK(!workshop.remove_order(order_no)); // unknown -> false, no exception
}

void test_workshop_revenue_only_done_orders()
{
    Workshop workshop("W");
    auto p_inspection = std::make_unique<Inspection>("A 1", 1.5, true); // 265.50
    auto p_repair = std::make_unique<Repair>("A 2", 10.0, "Engine", 350.0); // 935.00
    auto p_open = std::make_unique<Repair>("A 3", 3.0, "Engine", 120.0);   // stays open
    Order& inspection = *p_inspection;
    Order& repair = *p_repair;
    workshop.add_order(std::move(p_inspection));
    workshop.add_order(std::move(p_repair));
    workshop.add_order(std::move(p_open));
    CHECK_NEAR(workshop.get_total_revenue(), 0.0);

    Mechanic mechanic("A", 40.0);
    mechanic.add_qualification("Maintenance");
    mechanic.add_qualification("Engine");
    CHECK(mechanic.assign_order(inspection));
    CHECK(mechanic.assign_order(repair));
    CHECK_NEAR(workshop.get_total_revenue(), 0.0); // in progress does not count

    CHECK(mechanic.finish_order(repair.get_order_no()));
    CHECK_NEAR(workshop.get_total_revenue(), 935.0);
    CHECK(mechanic.finish_order(inspection.get_order_no()));
    CHECK_NEAR(workshop.get_total_revenue(), 1200.5);
}

void test_workshop_composition_deletes_orders()
{
    CountingOrder::destroyed = 0;
    {
        Workshop workshop("W");
        workshop.add_order(std::make_unique<CountingOrder>());
        workshop.add_order(std::make_unique<CountingOrder>());
        CHECK(CountingOrder::destroyed == 0);
    } // workshop destroyed here -> both orders must be destroyed (via Order* -> virtual dtor)
    CHECK(CountingOrder::destroyed == 2);

    // removing a done order deletes exactly that order
    CountingOrder::destroyed = 0;
    Workshop workshop("W");
    auto p_order = std::make_unique<CountingOrder>();
    int order_no = p_order->get_order_no();
    p_order->set_status(OrderStatus::DONE);
    workshop.add_order(std::move(p_order));
    workshop.add_order(std::make_unique<CountingOrder>());
    CHECK(workshop.remove_order(order_no));
    CHECK(CountingOrder::destroyed == 1);
    CHECK(workshop.get_orders().size() == 1);
}
} // namespace

int main()
{
    run("print_info entspricht exakt dem Aufgabenblatt", test_print_info_matches_exam);
    run("Klassendesign (abstrakt, virtueller Dtor, keine Kopie, enum class)", test_class_design);
    run("Auftragsnummern eindeutig und fortlaufend", test_order_numbers_are_unique_and_increasing);
    run("Neuer Auftrag: offen, kein Mechaniker", test_new_order_is_open_without_mechanic);
    run("Preis Inspektion (mit/ohne HU, abgeleitet)", test_inspection_price);
    run("Preis Reparatur inkl. Rabatt-Grenzfall 8 h", test_repair_price_and_discount_boundary);
    run("Benoetigte Qualifikation polymorph", test_required_qualification_is_polymorphic);
    run("Validierung in Konstruktoren und Settern", test_order_validation);
    run("Mechaniker-IDs und Validierung", test_mechanic_ids_and_validation);
    run("Qualifikationen hinzufuegen/entfernen/abfragen", test_mechanic_qualifications);
    run("Zuweisung setzt beide Seiten + Status", test_assign_success_sets_both_sides);
    run("Alle drei Ablehnungsgruende aendern nichts", test_assign_rejections_change_nothing);
    run("Auftrag abschliessen", test_finish_order);
    run("Werkstatt: hinzufuegen, suchen, entfernen", test_workshop_add_find_remove);
    run("Werkstatt: Umsatz nur abgeschlossene Auftraege", test_workshop_revenue_only_done_orders);
    run("Komposition: Werkstatt loescht ihre Auftraege", test_workshop_composition_deletes_orders);

    std::cout << "\n" << checks_passed << " checks passed, " << checks_failed << " failed\n";
    return checks_failed == 0 ? 0 : 1;
}
