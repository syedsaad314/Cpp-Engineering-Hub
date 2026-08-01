#pragma once
#include "Common.hpp"
#include <string>
#include <vector>

class PersonNode {
private:
    std::string id;
    std::string name;
    Gender gender;
    int birthYear;
    PersonNode* father;
    PersonNode* mother;
    PersonNode* spouse;
    std::vector<PersonNode*> children;

public:
    PersonNode(const std::string& name, Gender gender, int birthYear = 0);

    // Getters
    std::string getName() const { return name; }
    Gender getGender() const { return gender; }
    int getBirthYear() const { return birthYear; }
    PersonNode* getFather() const { return father; }
    PersonNode* getMother() const { return mother; }
    PersonNode* getSpouse() const { return spouse; }
    const std::vector<PersonNode*>& getChildren() const { return children; }

    // Setters & Linkers
    void setFather(PersonNode* f) { father = f; }
    void setMother(PersonNode* m) { mother = m; }
    void setSpouse(PersonNode* s) { spouse = s; }
    void addChild(PersonNode* child);
};