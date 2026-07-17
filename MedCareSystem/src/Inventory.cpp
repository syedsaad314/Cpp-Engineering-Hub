#include "../include/Inventory.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

InventoryItem::InventoryItem() : id(0), stock(0), unitPrice(0.0) {}

InventoryItem::InventoryItem(int id, std::string name, int stock, double price)
    : id(id), name(name), stock(stock), unitPrice(price) {}

int InventoryItem::getID() const { return id; }
std::string InventoryItem::getName() const { return name; }
int InventoryItem::getStock() const { return stock; }
double InventoryItem::getUnitPrice() const { return unitPrice; }

void InventoryItem::setStock(int qty) { stock = qty; }
void InventoryItem::setUnitPrice(double price) { unitPrice = price; }

std::string InventoryItem::serialize() const {
    std::stringstream ss;
    ss << id << "|"
       << name << "|"
       << stock << "|"
       << std::fixed << std::setprecision(2) << unitPrice;
    return ss.str();
}

InventoryItem InventoryItem::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 4) return InventoryItem();

    return InventoryItem(
        std::stoi(tokens[0]),
        tokens[1],
        std::stoi(tokens[2]),
        std::stod(tokens[3])
    );
}

//Maintains dynamic pharmacological stock thresholds. Tracks clinical formulas and updates billing ledgers upon dispense.