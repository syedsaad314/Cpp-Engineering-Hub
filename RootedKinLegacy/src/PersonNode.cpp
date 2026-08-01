#include "../include/PersonNode.hpp"
#include <algorithm>

PersonNode::PersonNode(const std::string& name, Gender gender, int birthYear)
    : name(name), gender(gender), birthYear(birthYear),
      father(nullptr), mother(nullptr), spouse(nullptr) {}

void PersonNode::addChild(PersonNode* child) {
    if (child && std::find(children.begin(), children.end(), child) == children.end()) {
        children.push_back(child);
    }
}