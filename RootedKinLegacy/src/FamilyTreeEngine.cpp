#include "../include/FamilyTreeEngine.hpp"
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

FamilyTreeEngine::~FamilyTreeEngine() {
    clear();
}

void FamilyTreeEngine::clear() {
    for (auto& pair : nodeIndex) {
        delete pair.second;
    }
    nodeIndex.clear();
}

PersonNode* FamilyTreeEngine::addMember(const std::string& name, Gender gender, int birthYear) {
    auto it = nodeIndex.find(name);
    if (it != nodeIndex.end()) {
        return it->second;
    }
    PersonNode* newNode = new PersonNode(name, gender, birthYear);
    nodeIndex[name] = newNode;
    return newNode;
}

PersonNode* FamilyTreeEngine::searchPerson(const std::string& name) const {
    auto it = nodeIndex.find(name);
    return (it != nodeIndex.end()) ? it->second : nullptr;
}

void FamilyTreeEngine::addChild(const std::string& parentName, const std::string& childName) {
    PersonNode* parent = searchPerson(parentName);
    PersonNode* child = searchPerson(childName);

    if (parent && child) {
        parent->addChild(child);
        if (parent->getGender() == Gender::Male) {
            child->setFather(parent);
        } else {
            child->setMother(parent);
        }
    }
}

void FamilyTreeEngine::setSpouse(const std::string& person1, const std::string& person2) {
    PersonNode* p1 = searchPerson(person1);
    PersonNode* p2 = searchPerson(person2);

    if (p1 && p2) {
        p1->setSpouse(p2);
        p2->setSpouse(p1);
    }
}

const PersonNode* FamilyTreeEngine::getTopAncestor() const {
    if (nodeIndex.empty()) return nullptr;

    const PersonNode* curr = nodeIndex.begin()->second;
    while (curr->getFather() != nullptr) {
        curr = curr->getFather();
    }
    return curr;
}

std::vector<const PersonNode*> FamilyTreeEngine::getAllRoots() const {
    std::vector<const PersonNode*> roots;
    for (const auto& pair : nodeIndex) {
        const PersonNode* node = pair.second;
        if (node->getFather() == nullptr && node->getMother() == nullptr) {
            roots.push_back(node);
        }
    }
    return roots;
}

int FamilyTreeEngine::calculateDepth(const PersonNode* node) const {
    if (!node) return 0;
    int maxChildDepth = 0;
    for (const auto* child : node->getChildren()) {
        maxChildDepth = std::max(maxChildDepth, calculateDepth(child));
    }
    return 1 + maxChildDepth;
}

FamilyStats FamilyTreeEngine::getStatistics() const {
    FamilyStats stats;
    stats.totalMembers = nodeIndex.size();

    for (const auto& pair : nodeIndex) {
        if (pair.second->getGender() == Gender::Male) stats.maleCount++;
        else if (pair.second->getGender() == Gender::Female) stats.femaleCount++;
    }

    auto roots = getAllRoots();
    for (const auto* root : roots) {
        stats.maxGenerations = std::max(stats.maxGenerations, calculateDepth(root));
    }
    return stats;
}

std::string FamilyTreeEngine::findRelationship(const std::string& personA, const std::string& personB) const {
    PersonNode* pA = searchPerson(personA);
    PersonNode* pB = searchPerson(personB);

    if (!pA || !pB) return "One or both individuals not found in tree.";
    if (pA == pB) return "Same person.";

    if (pA->getFather() == pB || pA->getMother() == pB) return personB + " is the Parent of " + personA;
    if (pB->getFather() == pA || pB->getMother() == pA) return personA + " is the Parent of " + personB;
    if (pA->getSpouse() == pB) return personA + " and " + personB + " are Spouses.";

    // Check Grandparent relationship
    if (pA->getFather() && (pA->getFather()->getFather() == pB || pA->getFather()->getMother() == pB)) {
        return personB + " is the Grandparent of " + personA;
    }
    if (pB->getFather() && (pB->getFather()->getFather() == pA || pB->getFather()->getMother() == pA)) {
        return personA + " is the Grandparent of " + personB;
    }

    // Check Sibling relationship
    if (pA->getFather() && pB->getFather() && (pA->getFather() == pB->getFather())) {
        return personA + " and " + personB + " are Siblings.";
    }

    return "Lineage Link: Direct or Collateral Relatives in Kinship Graph.";
}

bool FamilyTreeEngine::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    for (const auto& pair : nodeIndex) {
        const PersonNode* n = pair.second;
        out << "MEMBER|" << n->getName() << "|" << (n->getGender() == Gender::Male ? "M" : "F") << "|" << n->getBirthYear() << "\n";
    }

    for (const auto& pair : nodeIndex) {
        const PersonNode* n = pair.second;
        if (n->getSpouse()) {
            if (n->getGender() == Gender::Male) { // Write spouse once
                out << "SPOUSE|" << n->getName() << "|" << n->getSpouse()->getName() << "\n";
            }
        }
        for (const auto* child : n->getChildren()) {
            out << "CHILD|" << n->getName() << "|" << child->getName() << "\n";
        }
    }

    out.close();
    return true;
}

bool FamilyTreeEngine::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    clear();
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tag, arg1, arg2, arg3;

        std::getline(ss, tag, '|');
        if (tag == "MEMBER") {
            std::getline(ss, arg1, '|');
            std::getline(ss, arg2, '|');
            std::getline(ss, arg3, '|');
            Gender g = (arg2 == "F") ? Gender::Female : Gender::Male;
            int yr = arg3.empty() ? 0 : std::stoi(arg3);
            addMember(arg1, g, yr);
        } else if (tag == "SPOUSE") {
            std::getline(ss, arg1, '|');
            std::getline(ss, arg2, '|');
            setSpouse(arg1, arg2);
        } else if (tag == "CHILD") {
            std::getline(ss, arg1, '|');
            std::getline(ss, arg2, '|');
            addChild(arg1, arg2);
        }
    }

    in.close();
    return true;
}