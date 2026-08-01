#pragma once
#include "FamilyTreeEngine.hpp"
#include "PDFExporter.hpp"

class ConsoleUI {
public:
    static void displayHeader();
    static void runMainMenu(FamilyTreeEngine& engine);
    
    // Interactive Wizards
    static void runBottomUpWizard(FamilyTreeEngine& engine);
    static void runTopDownWizard(FamilyTreeEngine& engine);
    
    // Tree Visualizer & Analytics
    static void displayTreeFromTopAncestor(const FamilyTreeEngine& engine);
    static void displayAnalytics(const FamilyTreeEngine& engine);
    static void queryKinship(const FamilyTreeEngine& engine);
    static void exportPDFMenu(const FamilyTreeEngine& engine);

private:
    static void renderSubTree(const PersonNode* node, const std::string& prefix, bool isLast);
    static void processTopDownBranch(FamilyTreeEngine& engine, const std::string& fatherName);
};