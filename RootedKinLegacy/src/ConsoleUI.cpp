#include "../include/ConsoleUI.hpp"
#include "../include/Common.hpp"
#include <iostream>
#include <vector>
#include <string>

void ConsoleUI::displayHeader() {
    std::cout << Colors::CYAN << Colors::BOLD;
    std::cout << R"(
  ██████╗  ██████╗  ██████╗ ████████╗███████╗██████╗     ██╗  ██╗██╗███╗   ██╗
  ██╔══██╗██╔═══██╗██╔═══██╗╚══██╔══╝██╔════╝██╔══██╗    ██║ ██╔╝██║████╗  ██║
  ██████╔╝██║   ██║██║   ██║   ██║   █████╗  ██║  ██║    █████╔╝ ██║██╔██╗ ██║
  ██╔══██╗██║   ██║██║   ██║   ██║   ██╔══╝  ██║  ██║    ██╔═██╗ ██║██║╚██╗██║
  ██║  ██║╚██████╔╝╚██████╔╝   ██║   ███████╗██████╔╝    ██║  ██╗██║██║ ╚████║
  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚═════╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
  ██╗     ███████╗ ██████╗  █████╗  ██████╗ ██╗  ██╗
  ██║     ██╔════╝██╔════╝ ██╔══██╗██╔════╝ ╚██╗██╔╝
  ██║     █████╗  ██║  ███╗███████║██║       ╚███╔╝ 
  ██║     ██╔══╝  ██║   ██║██╔══██║██║        ██║   
  ███████╗███████╗╚██████╔╝██║  ██║╚██████╗   ██║   
  ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝   ╚═╝  
)";
    std::cout << Colors::RESET << Colors::YELLOW << Colors::BOLD
              << "      --- KINSHIP GRAPH & DENSE GENERATION ENGINE ---\n" << Colors::RESET << "\n";
}

// ============================================================================
// MODE 1: BOTTOM-UP WIZARD (Context-Aware: Self -> Parents -> Ancestors)
// ============================================================================
void ConsoleUI::runBottomUpWizard(FamilyTreeEngine& engine) {
    std::cout << "\n" << Colors::B_YELLOW 
              << "=====================================================================\n"
              << "  ⬆️ GUIDED INPUT WIZARD: BOTTOM-UP ANCESTRAL LINEAGE\n"
              << "=====================================================================\n" << Colors::RESET;
    std::cout << "Starting from YOURSELF and building upward generation by generation.\n\n";

    std::string selfName;
    char selfGenderChar;

    std::cout << Colors::B_GREEN << "[STEP 1: ENTRY FOR YOURSELF]" << Colors::RESET << "\n";
    std::cout << "Enter Your Name: ";
    std::cin >> selfName;
    std::cout << "Enter Your Gender (M/F): ";
    std::cin >> selfGenderChar;

    Gender selfGender = (selfGenderChar == 'F' || selfGenderChar == 'f') ? Gender::Female : Gender::Male;
    engine.addMember(selfName, selfGender);

    PersonNode* currentChildNode = engine.searchPerson(selfName);
    int genCounter = 1;

    while (currentChildNode) {
        std::cout << "\n" << Colors::B_CYAN 
                  << "[GENERATION " << genCounter << " -> PARENTS OF: " << currentChildNode->getName() << "]" 
                  << Colors::RESET << "\n";

        std::string fatherName, motherName;
        std::cout << "Enter Father's Name for " << Colors::BOLD << currentChildNode->getName() << Colors::RESET << ": ";
        std::cin >> fatherName;
        
        std::cout << "Is " << fatherName << "'s Wife (Mother) known? (Y/N): ";
        char motherKnown;
        std::cin >> motherKnown;

        engine.addMember(fatherName, Gender::Male);
        engine.addChild(fatherName, currentChildNode->getName());

        if (motherKnown == 'Y' || motherKnown == 'y') {
            std::cout << "Enter Mother's Name: ";
            std::cin >> motherName;
            engine.addMember(motherName, Gender::Female);
            engine.setSpouse(fatherName, motherName);
        }

        // Lineage Check: Ask for Brothers of Father
        std::cout << "\nDoes " << fatherName << " have BROTHERS (Male heirs of his father)? (Y/N): ";
        char hasBrothers;
        std::cin >> hasBrothers;

        if (hasBrothers == 'Y' || hasBrothers == 'y') {
            int brotherCount = 0;
            std::cout << "How many brothers does " << fatherName << " have? ";
            std::cin >> brotherCount;
            for (int i = 0; i < brotherCount; ++i) {
                std::string broName;
                std::cout << "  Enter Brother #" << (i + 1) << " Name: ";
                std::cin >> broName;
                engine.addMember(broName, Gender::Male);
            }
        } else {
            // Lineage Fallback: Prompt for sisters if no male heir exists
            std::cout << Colors::YELLOW << "└─ [Lineage Notice] No male heirs found for " << fatherName 
                      << "'s line. Enter Sisters to preserve branch? (Y/N): " << Colors::RESET;
            char hasSisters;
            std::cin >> hasSisters;
            if (hasSisters == 'Y' || hasSisters == 'y') {
                int sisterCount = 0;
                std::cout << "How many sisters does " << fatherName << " have? ";
                std::cin >> sisterCount;
                for (int i = 0; i < sisterCount; ++i) {
                    std::string sisName;
                    std::cout << "  Enter Sister #" << (i + 1) << " Name: ";
                    std::cin >> sisName;
                    engine.addMember(sisName, Gender::Female);
                }
            }
        }

        std::cout << "\nDo you know " << fatherName << "'s Father (Grandfather level)? (Y/N): ";
        char goUp;
        std::cin >> goUp;

        if (goUp == 'Y' || goUp == 'y') {
            currentChildNode = engine.searchPerson(fatherName);
            genCounter++;
        } else {
            std::cout << Colors::B_GREEN << "\n✓ Top Ancestor established at: " << fatherName << Colors::RESET << "\n";
            break;
        }
    }
}

// ============================================================================
// MODE 2: TOP-DOWN WIZARD (Context-Aware: Top Ancestor -> Children)
// ============================================================================
void ConsoleUI::runTopDownWizard(FamilyTreeEngine& engine) {
    std::cout << "\n" << Colors::B_YELLOW 
              << "=====================================================================\n"
              << "  ⬇️ GUIDED INPUT WIZARD: TOP-DOWN PATRILINEAL LINEAGE\n"
              << "=====================================================================\n" << Colors::RESET;

    std::string topAncestorName, spouseName;
    std::cout << Colors::B_GREEN << "[STEP 1: TOP ANCESTOR REGISTRATION]" << Colors::RESET << "\n";
    std::cout << "Enter the Name of the Top Ancestor: ";
    std::cin >> topAncestorName;

    engine.addMember(topAncestorName, Gender::Male);

    std::cout << "Enter Spouse/Wife Name for " << topAncestorName << " (or 'NONE'): ";
    std::cin >> spouseName;
    if (spouseName != "NONE" && spouseName != "none") {
        engine.addMember(spouseName, Gender::Female);
        engine.setSpouse(topAncestorName, spouseName);
    }

    processTopDownBranch(engine, topAncestorName);
}

void ConsoleUI::processTopDownBranch(FamilyTreeEngine& engine, const std::string& fatherName) {
    std::cout << "\n" << Colors::B_CYAN 
              << "[CHILDREN REGISTRATION FOR: " << fatherName << "]" << Colors::RESET << "\n";

    std::cout << "Does " << fatherName << " have any SONS (Male Heirs)? (Y/N): ";
    char hasSons;
    std::cin >> hasSons;

    std::vector<std::string> maleHeirs;

    if (hasSons == 'Y' || hasSons == 'y') {
        int sonCount = 0;
        std::cout << "How many sons does " << fatherName << " have? ";
        std::cin >> sonCount;
        for (int i = 0; i < sonCount; ++i) {
            std::string sonName;
            std::cout << "  Enter Son #" << (i + 1) << " Name: ";
            std::cin >> sonName;
            engine.addMember(sonName, Gender::Male);
            engine.addChild(fatherName, sonName);
            maleHeirs.push_back(sonName);
        }
    } else {
        std::cout << Colors::YELLOW << "└─ [Lineage Fallback] No male heir for " << fatherName 
                  << ". Register daughters to preserve lineage branch? (Y/N): " << Colors::RESET;
        char hasDaughters;
        std::cin >> hasDaughters;
        if (hasDaughters == 'Y' || hasDaughters == 'y') {
            int daughterCount = 0;
            std::cout << "How many daughters does " << fatherName << " have? ";
            std::cin >> daughterCount;
            for (int i = 0; i < daughterCount; ++i) {
                std::string dName;
                std::cout << "  Enter Daughter #" << (i + 1) << " Name: ";
                std::cin >> dName;
                engine.addMember(dName, Gender::Female);
                engine.addChild(fatherName, dName);
            }
        }
    }

    // Branch traversal into sons
    for (const auto& son : maleHeirs) {
        std::cout << "\nDoes " << son << " have a Spouse/Wife? (Y/N): ";
        char hasWife;
        std::cin >> hasWife;
        if (hasWife == 'Y' || hasWife == 'y') {
            std::string wifeName;
            std::cout << "  Enter Wife's Name for " << son << ": ";
            std::cin >> wifeName;
            engine.addMember(wifeName, Gender::Female);
            engine.setSpouse(son, wifeName);
        }

        std::cout << "Do you want to enter the next generation (Children) for " << son << "? (Y/N): ";
        char nextGen;
        std::cin >> nextGen;
        if (nextGen == 'Y' || nextGen == 'y') {
            processTopDownBranch(engine, son);
        }
    }
}

// ============================================================================
// VISUALIZATION & ANALYTICS UI
// ============================================================================
void ConsoleUI::displayTreeFromTopAncestor(const FamilyTreeEngine& engine) {
    const PersonNode* root = engine.getTopAncestor();
    if (!root) {
        std::cout << Colors::RED << "\n[!] No family tree data registered yet." << Colors::RESET << "\n";
        return;
    }

    std::cout << "\n" << Colors::B_YELLOW << "=====================================================================\n";
    std::cout << "         STRUCTURED DENSE FAMILY TREE VISUALIZER (TOP-DOWN)          \n";
    std::cout << "=====================================================================\n" << Colors::RESET;
    std::cout << Colors::B_CYAN << "👑 TOP ANCESTOR ROOT: " << root->getName() << Colors::RESET << "\n\n";

    renderSubTree(root, "", true);
    std::cout << "\n";
}

void ConsoleUI::renderSubTree(const PersonNode* node, const std::string& prefix, bool isLast) {
    if (!node) return;

    std::cout << prefix << (isLast ? "└── " : "├── ")
              << Colors::B_GREEN << node->getName() << Colors::RESET
              << ((node->getGender() == Gender::Male) ? Colors::CYAN + " [M]" : Colors::MAGENTA + " [F]") << Colors::RESET;

    if (node->getSpouse() != nullptr) {
        std::cout << Colors::RED << " <♥> Spouse: " << Colors::YELLOW << node->getSpouse()->getName() << Colors::RESET;
    }
    std::cout << "\n";

    const auto& children = node->getChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        renderSubTree(children[i], prefix + (isLast ? "    " : "│   "), i == children.size() - 1);
    }
}

void ConsoleUI::displayAnalytics(const FamilyTreeEngine& engine) {
    FamilyStats stats = engine.getStatistics();
    std::cout << "\n" << Colors::B_CYAN << "=====================================================================\n";
    std::cout << "                 📊 KINSHIP GRAPH ENGINE ANALYTICS                   \n";
    std::cout << "=====================================================================\n" << Colors::RESET;
    std::cout << "  • Total Members Tracked : " << Colors::BOLD << stats.totalMembers << Colors::RESET << "\n";
    std::cout << "  • Male Lineage Count   : " << Colors::CYAN << stats.maleCount << Colors::RESET << "\n";
    std::cout << "  • Female Lineage Count : " << Colors::MAGENTA << stats.femaleCount << Colors::RESET << "\n";
    std::cout << "  • Maximum Tree Depth    : " << Colors::YELLOW << stats.maxGenerations << " Generations" << Colors::RESET << "\n";
    std::cout << "=====================================================================\n\n";
}

void ConsoleUI::queryKinship(const FamilyTreeEngine& engine) {
    std::string p1, p2;
    std::cout << "\n" << Colors::B_YELLOW << "=== 🔍 KINSHIP & RELATIONSHIP PATH CALCULATOR ===" << Colors::RESET << "\n";
    std::cout << "Enter First Person Name: ";
    std::cin >> p1;
    std::cout << "Enter Second Person Name: ";
    std::cin >> p2;

    std::string rel = engine.findRelationship(p1, p2);
    std::cout << Colors::B_GREEN << "\n[Kinship Result]: " << Colors::RESET << rel << "\n\n";
}

void ConsoleUI::exportPDFMenu(const FamilyTreeEngine& engine) {
    const PersonNode* root = engine.getTopAncestor();
    if (!root) {
        std::cout << Colors::RED << "\n[!] Cannot export empty family tree." << Colors::RESET << "\n";
        return;
    }

    std::string filename = "FamilyTree_Report.html";
    if (PDFExporter::exportToPrintableHTML(root, filename)) {
        std::cout << Colors::B_GREEN << "\n✓ Successfully generated print report: " << filename << Colors::RESET << "\n";
        std::cout << "  1. Open '" << filename << "' in Chrome, Edge, or Firefox.\n";
        std::cout << "  2. Press " << Colors::BOLD << "Ctrl + P" << Colors::RESET << " and select " << Colors::BOLD << "'Save as PDF'" << Colors::RESET << ".\n\n";
    }
}

void ConsoleUI::runMainMenu(FamilyTreeEngine& engine) {
    int choice = 0;
    while (choice != 8) {
        displayHeader();
        std::cout << "  [1] ⬆️ Guided Input: Bottom-Up (You -> Father -> Ancestor)\n";
        std::cout << "  [2] ⬇️ Guided Input: Top-Down (Ancestor -> Children -> Descendants)\n";
        std::cout << "  [3] 🌳 View Structured Dense Family Tree\n";
        std::cout << "  [4] 🔍 Kinship & Relationship Path Calculator\n";
        std::cout << "  [5] 📊 Family Analytics & Generation Statistics\n";
        std::cout << "  [6] 🖨️ Export Vector HTML / Printable PDF Report\n";
        std::cout << "  [7] 💾 Save / Load Family Database File\n";
        std::cout << "  [8] ❌ Exit Application\n";
        std::cout << "=====================================================================\n";
        std::cout << "Enter choice (1-8): ";
        std::cin >> choice;

        switch (choice) {
            case 1: runBottomUpWizard(engine); break;
            case 2: runTopDownWizard(engine); break;
            case 3: displayTreeFromTopAncestor(engine); break;
            case 4: queryKinship(engine); break;
            case 5: displayAnalytics(engine); break;
            case 6: exportPDFMenu(engine); break;
            case 7: {
                std::cout << "\n  [A] Save Database\n  [B] Load Database\nSelect: ";
                char sub; std::cin >> sub;
                if (sub == 'A' || sub == 'a') {
                    if (engine.saveToFile("data/family_database.txt"))
                        std::cout << Colors::GREEN << "\n✓ Tree database saved to 'data/family_database.txt'\n" << Colors::RESET;
                } else {
                    if (engine.loadFromFile("data/family_database.txt"))
                        std::cout << Colors::GREEN << "\n✓ Tree database loaded from 'data/family_database.txt'\n" << Colors::RESET;
                }
                break;
            }
            case 8: std::cout << "\nExiting Rooted Kin Legacy Engine. Goodbye!\n"; break;
            default: std::cout << Colors::RED << "Invalid option. Try again.\n" << Colors::RESET;
        }
    }
}