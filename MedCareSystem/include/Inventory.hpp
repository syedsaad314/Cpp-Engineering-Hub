#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>

class InventoryItem {
private:
    int id;
    std::string name;
    int stock;
    double unitPrice;

public:
    InventoryItem();
    InventoryItem(int id, std::string name, int stock, double price);

    int getID() const;
    std::string getName() const;
    int getStock() const;
    double getUnitPrice() const;

    void setStock(int qty);
    void setUnitPrice(double price);

    std::string serialize() const;
    static InventoryItem deserialize(const std::string& line);
};

#endif

//Maintains dynamic pharmacological stock thresholds. Tracks clinical formulas and updates billing ledgers upon dispense.