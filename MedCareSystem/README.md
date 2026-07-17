<div align="center">

# 🏥 MedCare Systems OS: Hospital Management System (HMS)

[![C++ Version](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20-blueviolet?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/Platform-Cross--Platform-007ACC?style=for-the-badge)](https://en.wikipedia.org/wiki/Cross-platform_software)
[![Standard](https://img.shields.io/badge/Standard-ISO%20IEC%2014882-success?style=for-the-badge&logo=gitbook&logoColor=white)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge&logo=checkmarx)](#)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](#)

```text
 ███╗   ███╗███████╗██████╗  ██████╗ █████╗ ██████╗ ███████╗     ██████╗ ███████╗
 ████╗ ████║██╔════╝██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝    ██╔═══██╗██╔════╝
 ██╔████╔██║█████╗  ██║  ██║██║     ███████║██████╔╝█████╗      ██║   ██║███████╗
 ██║╚██╔╝██║██╔══╝  ██║  ██║██║     ██╔══██║██╔══██╗██╔══╝      ██║   ██║╚════██║
 ██║ ╚═╝ ██║███████╗██████╔╝╚██████╗██║  ██║██║  ██║███████╗    ╚██████╔╝███████║
 ╚═╝     ╚═╝╚══════╝╚═════╝  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚══════╝
```

Architectural Design • Visual Report Previews • Key Implementations • Project Directory • Installation & Compilation

</div>

---

<h3><code>📑Contents</code></h3>

- [👨‍💻 Lead Software Architect](#-lead-software-architect)
- [🧭 Architectural Design](#-architectural-design)
- [📊 Visual Report Previews](#-visual-report-previews)
- [✨ Key Implementations](#-key-implementations)
- [📋 Prerequisites](#-prerequisites)
- [🔨 Building the Project](#-building-the-project)
- [⚡ Running the Executable](#-running-the-executable)
- [💡 Code Implementations](#-code-implementations)

---

<h3><code>👨‍💻Lead Software Architect</code></h3>

**Architect:** Syed Saad Bin Irfan

**Institution:** Department of Computer Science, UBIT, University of Karachi

**Project Hub:** Part of the Cpp-Engineering-Hub

---

<h3><code>🧭Architectural Design</code></h3>

MedCare Systems OS is an enterprise-grade terminal solution built to completely replace outdated, unportable legacy console patterns (e.g., `<conio.h>`, raw structural file dumps). It implements a secure, modular Object-Oriented paradigm using structured database engines, bulletproof memory validation buffers, and clinical prioritization algorithms.

---

<h3><code>📊Visual Report Previews</code></h3>

The core system outputs structured, highly scannable, and clean tabular data reports formatted with dynamic console colors:

<h3>1. Active Duty Physician Roster</h3>

```text
================================================================================
          🏥  MEDCARE ENTERPRISE OS - ADVANCED CLINICAL CONTROL  🏥          
================================================================================
                Professional High-Fidelity Healthcare Engine
--------------------------------------------------------------------------------

  Active Duty Physicians:
  Doc ID   Physician Name           Specialty            Shift       Fee
  ----------------------------------------------------------------------
  2001     Dr. Imran Ahmed          Cardiology           Morning     2000 PKR
  2002     Dr. Aisha Khan           Neurology            Evening     2500 PKR
  2003     Dr. Faisal Shah          Pediatrics           Night       1500 PKR
  2004     Dr. Maria Alvi           General Medicine     Morning     1000 PKR
  ----------------------------------------------------------------------

  Lead Software Architect: Syed Saad Bin Irfan | BSSE Student @ KU-DCS-UBIT 
================================================================================  
```

<h3>2. Comprehensive Medical Clearance & Billing Invoice</h3>

```text
╔══════════════════════════════════════════════════════════════════════════════╗
║                MEDCARE OS — CLINICAL FINANCIAL CLEARANCE                     ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ PATIENT ID: #1024                    DIAGNOSIS: Acute Myocardial Infarction  ║
║ NAME: Ali Raza                       WARD: ICU (Bed Slot #12)                ║
║ ATTENDING: Dr. Imran Ahmed (Cardio)  INSURANCE RATE: 80% Policy Shield       ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ ITEMIZATION DETAILS                                         AMOUNT (PKR)     ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ [1] Physician Consultation Fees                               2,000.00       ║
║ [2] Emergency ICU Bed Support (Per 24 Hours)                  5,500.00       ║
║ [3] Diagnostic Lab Fees (ECG Cardiac Analysis + Blood Panel)  3,300.00       ║
║ [4] Pharmacy Dispensation (Augmentin 625mg + Surbex-Z)        3,950.00       ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ SUB-TOTAL                                                    14,750.00       ║
║ HEALTH SERVICES PROVINCIAL TAX (5.0%)                           737.50       ║
║ GROSS CALCULATED TOTAL                                       15,487.50       ║
║ PAYER POLICY INSURANCE SHIELD (80.0%)                      - 12,390.00       ║
╠══════════════════════════════════════════════════════════════════════════════╣
║ NET CLEARANCE BALANCE DUE                                     3,097.50 PKR   ║
╚══════════════════════════════════════════════════════════════════════════════╝
```


<h3>3. Diagnostic Laboratory Worklist Matrix</h3>

```text
  Laboratory Worklist Matrix:
  Work ID   Patient ID   Diagnostic Type          Status         Remarks/Findings
  ------------------------------------------------------------------------------
  4001      1001         ECG Cardiac Analysis     Completed      Sinus tachycardia.
  4002      1002         Blood Panel              Pending        Awaiting serum.
  4003      1003         MRI Scan                 Completed      No structural anomalies.
```

---

<h3><code>Key Implementations</code></h3>

🛡️ **Robust Serialization Engine:** Eradicated compiler structural padding risks by compiling and writing custom pipe-delimited data packets (`|`), guaranteeing complete data serialization safety across various platforms.

🚨 **Multi-Stage Triage Engine:** Prioritizes high-risk cardiac and emergency events by separating critical (Red), stable/urgent (Yellow), and routine (Green) cases into dynamic patient queues.

🧾 **Real-Time Audit & Billing Ledger:** Automatically tracks and calculates clinical bed/care costs, provincial healthcare service taxes, and out-of-pocket insurance offsets.

🔥 **Resilient Input Handlers:** Custom-engineered type-safe validation guards to isolate and drop corrupted standard stream inputs (`std::cin`), preventing infinity-loop memory locks.

```text
MedCareSystem/
├── include/
│   ├── Doctor.hpp         # Doctor registry and schedule models
│   ├── Patient.hpp        # Expanded patient profile, medical chart, and billing ledger
│   ├── Inventory.hpp      # Pharmacy stock management
│   ├── LabTest.hpp        # Diagnostics and laboratory records
│   └── MedCenterOS.hpp    # Advanced coordination dashboard and terminal loop
├── src/
│   ├── Doctor.cpp         # Medical staff registry handlers and models
│   ├── Patient.cpp        # Serializers, file streams parsing, and balance operations
│   ├── Inventory.cpp      # Pharmacy formulas stock mutations
│   ├── LabTest.cpp        # Lab test execution states and diagnostics notes
│   ├── MedCenterOS.cpp    # Unified controller loop and database persistence mechanisms
│   └── main.cpp           # Main menu controller and bootstrap launch-deck
└── README.md              # Premium system manual
```

---

<h3><code>📋Prerequisites</code></h3>

Ensure a modern standard-compliant C++ compiler with C++11 standard support or higher (GCC, MSVC, Clang) is installed in your environment.

---

<h3><code>🔨 Building the Project</code></h3>

Navigate to the root workspace directory and run the compilation sequence:

```bash
# Enter the workspace directory
cd MedCareSystem

# Compile source assets into a single binary executable
g++ -std=c++17 src/*.cpp -I include -Wall -O3 -o MedCareSystem
```

---

<h3><code>Running the Executable</code></h3>

```bash
# On Linux / macOS
./MedCareSystem

# On Windows (Command Prompt/PowerShell)
./MedCareSystem.exe
```

---

<h3><code>Code Implementations</code></h3>

<h2><code>Stream Security Handlers</code></h2>

```cpp
// Prevents standard buffer pollution from non-numeric entry bugs
int MedCenterOS::getValidatedInteger(const std::string& prompt, int minVal, int maxVal) {
    int input;
    while (true) {
        std::cout << prompt;
        if (std::cin >> input) {
            if (input >= minVal && input <= maxVal) {
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                return input;
            }
        }
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "\033[1;31m[!] Out of scope. Enter a number between " << minVal << " and " << maxVal << ".\033[0m\n";
    }
}
```

<h2><code>Strict Output Serialization Pattern</code></h2>

```cpp
// Compiles patient records with absolute safety inside a single flat line
std::string Patient::serialize() const {
    return std::to_string(patientID) + "|" + name + "|" + std::to_string(age) + "|" 
           + gender + "|" + contact + "|" + emergencyKin + "|" 
           + std::to_string(static_cast<int>(triage)) + "|" + assignedWard + "|" 
           + std::to_string(assignedBed) + "|" + std::to_string(attendingDoctorID) + "|" 
           + diagnosis + "|" + prescribedMeds + "|" + serializeLedger();
}
```

---

<div align="center">

**Built by** ***Syed Saad Bin Irfan*** — BSSE'28, DCS-UBIT, University of Karachi

</div>
