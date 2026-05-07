#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class Character;
class Inventory;

// ─────────────────────────────────────────
//  Weapon
// ─────────────────────────────────────────
class Weapon
{
private:
    const std::string name;
    const int         damage;

public:
    Weapon(const std::string& name, int damage)
        : name(name), damage(damage) {}

    const std::string& getName()   const { return name;   }
    int                getDamage() const { return damage;  }
};

// ─────────────────────────────────────────
//  Inventory
// ─────────────────────────────────────────
class Inventory
{
private:
    std::vector<std::string> items;
    int maxSlots;

public:
    explicit Inventory(int maxSlots = 10) : maxSlots(maxSlots) {}

    bool isEmpty() const { return items.empty(); }
    bool isFull()  const { return static_cast<int>(items.size()) >= maxSlots; }

    int size()    const { return static_cast<int>(items.size()); }
    int getMax()  const { return maxSlots; }

    bool addItem(const std::string& item)
    {
        if (isFull()) return false;
        items.push_back(item);
        return true;
    }

    // Removes last item and writes it into `item`. Returns false if empty.
    bool removeLastItem(std::string& item)
    {
        if (isEmpty()) return false;
        item = items.back();
        items.pop_back();
        return true;
    }

    void print() const
    {
        std::cout << "  Inventory (" << items.size() << "/" << maxSlots << "): ";
        for (const auto& i : items) std::cout << "[" << i << "] ";
        std::cout << "\n";
    }
};

// ─────────────────────────────────────────
//  Character  (abstract base)
// ─────────────────────────────────────────
class Character
{
    // Healer needs access to private healthPoints
    friend class Healer;

private:
    int healthPoints;

public:
    static const int MIN_LEVEL = 1;
    static const int MAX_LEVEL = 10;

    const std::string name;
    int               level;
    Weapon*           weapon;  // 0..1 — character may have no weapon

protected:
    Inventory inventory;
    int       experiencePoints;

    // Experience needed to reach each level (index = target level)
    static const int XP_TABLE[11];

public:
    Character(const std::string& name, int hp = 100, int inventorySlots = 10)
        : healthPoints(hp), name(name), level(MIN_LEVEL),
          weapon(nullptr), inventory(inventorySlots), experiencePoints(0) {}

    virtual ~Character() = default;

    // ── Inventory access ──────────────────
    Inventory& getInventory() { return inventory; }

    // ── Health (read-only for outside) ────
    int getHealthPoints() const { return healthPoints; }

    // ── Experience / levelling ────────────
    void addExperience(int xp)
    {
        if (level >= MAX_LEVEL) return;
        experiencePoints += xp;
        while (level < MAX_LEVEL && experiencePoints >= XP_TABLE[level + 1])
            levelUp();
    }

    void levelUp()
    {
        if (level >= MAX_LEVEL) return;
        ++level;
        std::cout << name << " levelled up to " << level << "!\n";
    }

    // ── Abstract interface ────────────────
    virtual void regenerate()    = 0;
    virtual void displayStatus() = 0;

protected:
    // Helper used by Healer via friend
    void applyHealing(int amount) { healthPoints += amount; }

    // Shared display lines for subclasses
    void printBaseStatus() const
    {
        std::cout << "  Name   : " << name         << "\n"
                  << "  HP     : " << healthPoints  << "\n"
                  << "  Level  : " << level
                  << " (" << experiencePoints << " XP)\n"
                  << "  Weapon : "
                  << (weapon ? weapon->getName() : "none") << "\n";
        inventory.print();
    }
};

const int Character::XP_TABLE[11] = { 0, 0, 100, 250, 450, 700,
                                        1000, 1350, 1750, 2200, 2700 };

// ─────────────────────────────────────────
//  Warrior
// ─────────────────────────────────────────
class Warrior : public Character
{
private:
    int weaponSkill;

public:
    Warrior(const std::string& name, int weaponSkill = 10)
        : Character(name), weaponSkill(weaponSkill) {}

    int getWeaponSkill() const { return weaponSkill; }

    void regenerate() override
    {
        weaponSkill += 5;
        std::cout << name << " sharpens skills. Weapon skill: " << weaponSkill << "\n";
    }

    void displayStatus() override
    {
        std::cout << "── Warrior ─────────────────\n";
        printBaseStatus();
        std::cout << "  W.Skill: " << weaponSkill << "\n";
    }
};

// ─────────────────────────────────────────
//  Mage
// ─────────────────────────────────────────
class Mage : public Character
{
private:
    int manaPoints;

public:
    Mage(const std::string& name, int mana = 80)
        : Character(name), manaPoints(mana) {}

    int getMana() const { return manaPoints; }

    void regenerate() override
    {
        manaPoints += 20;
        std::cout << name << " meditates. Mana: " << manaPoints << "\n";
    }

    void displayStatus() override
    {
        std::cout << "── Mage ────────────────────\n";
        printBaseStatus();
        std::cout << "  Mana   : " << manaPoints << "\n";
    }
};

// ─────────────────────────────────────────
//  Thief  (derived from Warrior)
// ─────────────────────────────────────────
class Thief : public Warrior
{
public:
    Thief(const std::string& name, int weaponSkill = 15)
        : Warrior(name, weaponSkill) {}

    // Returns *this for method chaining
    Thief& steal(Character& target)
    {
        Inventory& targetInv = target.getInventory();
        Inventory& thiefInv  = getInventory();

        if (targetInv.isEmpty())
        {
            std::cout << name << " tried to steal from " << target.name
                      << " — nothing to steal!\n";
            return *this;
        }
        if (thiefInv.isFull())
        {
            std::cout << name << " tried to steal — inventory is full!\n";
            return *this;
        }

        // Success condition: weaponSkill > target level * 5
        bool success = getWeaponSkill() > target.level * 5;

        if (success)
        {
            std::string stolenItem;
            targetInv.removeLastItem(stolenItem);
            thiefInv.addItem(stolenItem);
            std::cout << name << " stole [" << stolenItem
                      << "] from " << target.name << "!\n";
        }
        else
        {
            std::cout << name << " failed to steal from " << target.name << ".\n";
        }

        return *this;
    }

    void displayStatus() override
    {
        std::cout << "── Thief ───────────────────\n";
        printBaseStatus();
        std::cout << "  W.Skill: " << getWeaponSkill() << "\n";
    }
};

// ─────────────────────────────────────────
//  Healer  (derived from Mage)
// ─────────────────────────────────────────
class Healer : public Mage
{
private:
    int healingPower;

public:
    Healer(const std::string& name, int healingPower = 30)
        : Mage(name), healingPower(healingPower) {}

    // Heals another character — uses friend access to private healthPoints
    Healer& heal(Character& target)
    {
        target.applyHealing(healingPower);  // friend-accessible helper
        std::cout << name << " heals " << target.name
                  << " for " << healingPower << " HP. "
                  << "(HP now: " << target.getHealthPoints() << ")\n";
        return *this;
    }

    // Heals itself — same mechanism
    Healer& healSelf()
    {
        return heal(*this);
    }

    void displayStatus() override
    {
        std::cout << "── Healer ──────────────────\n";
        printBaseStatus();
        std::cout << "  Mana   : " << getMana()      << "\n"
                  << "  HealPow: " << healingPower    << "\n";
    }
};

// ─────────────────────────────────────────
//  main — quick demo
// ─────────────────────────────────────────
int main()
{
    // --- Setup ---
    Weapon sword("Iron Sword", 25);
    Weapon staff("Magic Staff", 15);

    Warrior thor("Thor", 20);
    thor.weapon = &sword;
    thor.getInventory().addItem("Health Potion");
    thor.getInventory().addItem("Shield");
    thor.getInventory().addItem("Gold Coin");

    Mage merlin("Merlin");
    merlin.weapon = &staff;

    Thief shadow("Shadow", 18);
    shadow.getInventory().addItem("Rope");

    Healer aria("Aria");

    // --- Status ---
    std::cout << "\n=== Initial Status ===\n";
    thor.displayStatus();
    merlin.displayStatus();
    shadow.displayStatus();
    aria.displayStatus();

    // --- Stealing (method chaining) ---
    std::cout << "\n=== Thief Actions ===\n";
    shadow.steal(thor).steal(thor);   // method chaining

    std::cout << "\n=== After Stealing ===\n";
    thor.displayStatus();
    shadow.displayStatus();

    // --- Healing (method chaining) ---
    std::cout << "\n=== Healer Actions ===\n";
    aria.heal(thor).heal(merlin).healSelf();

    // --- Levelling ---
    std::cout << "\n=== Levelling ===\n";
    thor.addExperience(150);
    thor.displayStatus();

    return 0;
}