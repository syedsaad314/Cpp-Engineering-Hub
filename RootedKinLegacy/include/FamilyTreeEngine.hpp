#pragma once
#include "PersonNode.hpp"
#include <unordered_map>
#include <string>
#include <vector>

struct FamilyStats {
    int totalMembers = 0;
    int maleCount = 0;
    int femaleCount = 0;
    int maxGenerations = 0;
};

class FamilyTreeEngine {
private:
    std::unordered_map<std::string, PersonNode*> nodeIndex;

    int calculateDepth(const PersonNode* node) const;

public:
    FamilyTreeEngine() = default;
    ~FamilyTreeEngine();

    PersonNode* addMember(const std::string& name, Gender gender, int birthYear = 0);
    void addChild(const std::string& parentName, const std::string& childName);
    void setSpouse(const std::string& person1, const std::string& person2);
    
    PersonNode* searchPerson(const std::string& name) const;
    const PersonNode* getTopAncestor() const;
    std::vector<const PersonNode*> getAllRoots() const;

    // Analytics & Kinship
    FamilyStats getStatistics() const;
    std::string findRelationship(const std::string& personA, const std::string& personB) const;
    
    // Persistence
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    void clear();
};