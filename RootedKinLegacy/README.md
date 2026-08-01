# 🌳 Rooted Kin Legacy — Kinship Graph & Family Tree Engine
 
![C++17](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-0078D4?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active%20Production-success?style=for-the-badge)
![Repo](https://img.shields.io/badge/Repository-Cpp--Engineering--Hub-orange?style=for-the-badge&logo=github)
![License](https://img.shields.io/badge/License-MIT-1B4F57?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-1B4F57?style=for-the-badge&logo=cmake)
![Author](https://img.shields.io/badge/Author-Syed%20Saad-1B4F57?style=for-the-badge&logo=github)
 
**Rooted Kin Legacy** is a high-performance C++ engine designed to model, traverse, analyze, and visualize complex generational family trees regardless of density. Built with bidirectional kinship pointers, dual-directional input wizards, relationship pathfinding, and a vector-grade HTML/PDF printable exporter.
 
---
 
```text
  ██████╗  ██████╗  ██████╗ ████████╗███████╗██████╗     ██╗  ██╗██╗███╗   ██╗
  ██╔══██╗██╔═══██╗██╔═══██╗╚══██╔══╝██╔════╝██╔══██╗    ██║ ██╔╝██║████╗  ██║
  ██████╔╝██║   ██║██║   ██║   ██║   █████╗  ██║  ██║    █████╔╝ ██║██╔██╗ ██║
  ██╔══██╗██║   ██║██║   ██║   ██║   ██╔══╝  ██║  ██║    ██╔═██╗ ██║██║╚██╗██║
  ██║  ██║╚██████╔╝╚██████╔╝   ██║   ███████╗██████╔╝    ██║  ██╗██║██║ ╚████║
  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚═════╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
  ██╗     ███████╗ ██████╗  █████╗  ██████╗██╗   ██╗
  ██║     ██╔════╝██╔════╝ ██╔══██╗██╔════╝╚██╗ ██╔╝
  ██║     █████╗  ██║  ███╗███████║██║      ╚████╔╝
  ██║     ██╔══╝  ██║   ██║██╔══██║██║       ╚██╔╝
  ███████╗███████╗╚██████╔╝██║  ██║╚██████╗   ██║
  ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝   ╚═╝
```
 
## 📑 Table of Contents
 
- [✨ Key Features](#-key-features)
- [🎨 Visual Samples & Terminal Output](#-visual-samples--terminal-output)
- [📂 Repository Structure](#-repository-structure)
- [⚙️ Building & Running](#️-building--running-powershell)
- [🖨️ How to Export as PDF](#️-how-to-export-as-pdf)
- [👤 Author](#-author)
---
 
## ✨ Key Features
 
- **⬆️ Guided Bottom-Up Wizard** — Enter data starting from yourself, moving step-by-step upward through father, uncles, and grandparents, to the highest ancestor.
- **⬇️ Guided Top-Down Lineage Wizard** — Enter data starting from the Top Ancestor, recursively branching down into sons, spouses, and descendants.
- **📜 Context-Aware Dynamic Prompts** — Prompts dynamically fetch previously entered relative names (e.g., "Enter Father's Name for Hamza-Khan").
- **👑 Patrilineal Lineage Rule with Female Heirs Fallback** — Lineage prioritizes direct male lines while gracefully handling female-only branches to prevent tree fractures.
- **🌳 Clean Structured Console Visualizer** — Renders large trees using clean branch connectors (`├──`, `└──`), gender badges (`[M]`/`[F]`), and spouse markers (`<♥>`).
- **🔍 Kinship Pathfinding Calculator** — Calculates exact relationships between any two individuals in the family graph.
- **📊 Graph Analytics Engine** — Returns real-time statistics including member counts, gender ratios, and total generation depth.
- **🖨️ Vector HTML / PDF Export** — Generates print-optimized CSS reports (`@media print`) that export into clean, publication-ready PDF documents via browser Ctrl + P.
- **💾 Database Persistence** — Save and load family graphs dynamically (`data/family_database.txt`).
---
 
## 🎨 Visual Samples & Terminal Output
 
### 1. Main Terminal Interface
 
```text
  [1] ⬆️ Guided Input: Bottom-Up (You -> Father -> Ancestor)
  [2] ⬇️ Guided Input: Top-Down (Ancestor -> Children -> Descendants)
  [3] 🌳 View Structured Dense Family Tree
  [4] 🔍 Kinship & Relationship Path Calculator
  [5] 📊 Family Analytics & Generation Statistics
  [6] 🖨️ Export Vector HTML / Printable PDF Report
  [7] 💾 Save / Load Family Database File
  [8] ❌ Exit Application
```
 
### 2. Structured Top-Down Tree Visualizer Sample
 
```text
=====================================================================
         STRUCTURED DENSE FAMILY TREE VISUALIZER (TOP-DOWN)
=====================================================================
👑 TOP ANCESTOR ROOT: Tariq-Khan
 
└── Tariq-Khan [M] <♥> Spouse: Bilquis-Begum
    ├── Usman-Khan [M] <♥> Spouse: Samina-Begum
    │   ├── Hamza-Khan [M]
    │   └── Ayesha-Khan [F]
    └── Tariq-Jr-Khan [M]
```
 
### 3. Generated Printable PDF / HTML Card Layout Preview
 
```text
  ██████╗  ██████╗  ██████╗ ████████╗███████╗██████╗     ██╗  ██╗██╗███╗   ██╗
  ██╔══██╗██╔═══██╗██╔═══██╗╚══██╔══╝██╔════╝██╔══██╗    ██║ ██╔╝██║████╗  ██║
  ██████╔╝██║   ██║██║   ██║   ██║   █████╗  ██║  ██║    █████╔╝ ██║██╔██╗ ██║
  ██╔══██╗██║   ██║██║   ██║   ██║   ██╔══╝  ██║  ██║    ██╔═██╗ ██║██║╚██╗██║
  ██║  ██║╚██████╔╝╚██████╔╝   ██║   ███████╗██████╔╝    ██║  ██╗██║██║ ╚████║
  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚═════╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
  ██╗     ███████╗ ██████╗  █████╗  ██████╗██╗   ██╗
  ██║     ██╔════╝██╔════╝ ██╔══██╗██╔════╝╚██╗ ██╔╝
  ██║     █████╗  ██║  ███╗███████║██║      ╚████╔╝
  ██║     ██╔══╝  ██║   ██║██╔══██║██║       ╚██╔╝
  ███████╗███████╗╚██████╔╝██║  ██║╚██████╗   ██║
  ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝   ╚═╝
============================================================
      AUTHENTIC LINEAGE GRAPH & GENERATION TREE REPORT
============================================================
 
                     [ Tariq-Khan ]
                      GEN 1 - Male
                  Spouse: Bilquis-Begum
                          |
            --------------+--------------
            |                           |
      [ Usman-Khan ]           [ Tariq-Jr-Khan ]
       GEN 2 - Male                GEN 2 - Male
    Spouse: Samina-Begum
            |
      [ Hamza-Khan ]
       GEN 3 - Male
 
============================================================
```
 
---
 
## 📂 Repository Structure
 
```text
RootedKinLegacy/
├── include/
│   ├── Common.hpp            # Terminal ANSI color schemes & gender enumerations
│   ├── PersonNode.hpp        # Graph node definition & pointer declarations
│   ├── FamilyTreeEngine.hpp  # Tree algorithms, kinship search & data storage
│   ├── PDFExporter.hpp       # Vector HTML/PDF print engine interface
│   └── ConsoleUI.hpp         # Terminal interface & interactive wizards
├── src/
│   ├── PersonNode.cpp        # Node linking implementations
│   ├── FamilyTreeEngine.cpp  # Engine logic, persistence & search
│   ├── PDFExporter.cpp       # HTML visual template renderer
│   ├── ConsoleUI.cpp         # Wizard workflows & visual ASCII tree
│   └── main.cpp              # Application entry point
├── data/
│   └── family_database.txt   # Persistent storage file
└── README.md                 # Project documentation
```
 
---
 
## ⚙️ Building & Running (PowerShell)
 
### Compilation
 
```powershell
# Navigate to project root
Set-Location -Path ".\RootedKinLegacy"
 
# Compile executable using C++17
g++ -std=c++17 -Wall -O3 src/*.cpp main.cpp -I include -o RootedKinLegacy.exe
```
 
### Running the Application
 
```powershell
.\RootedKinLegacy.exe
```
 
---
 
## 🖨️ How to Export as PDF
 
Select Option 6 in the main menu to generate `FamilyTree_Report.html`.
 
Open `FamilyTree_Report.html` in Chrome, Edge, or Firefox.
 
Click **"Print Report / Save Vector PDF"** or press **Ctrl + P**.
 
Set destination to **"Save as PDF"** and select **Landscape** orientation.
 
---

## 👤 Author

***Syed Saad Bin Irfan***

BS Software Engineering (BSSE'28) — Department of Computer Science (UBIT), University of Karachi.
<br>
<a href="https://www.linkedin.com/in/syed-saad-bin-irfan-b27156300/"><img src="https://skillicons.dev/icons?i=linkedin" alt="LinkedIn" /></a> <a href="https://github.com/syedsaad314"><img src="https://skillicons.dev/icons?i=github" alt="GitHub" /></a>

<br>
