#include "../include/MedCenterOS.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

MedCenterOS::MedCenterOS() {
    loadAllDatabases();
}

MedCenterOS::~MedCenterOS() {
    saveAllDatabases();
}

void MedCenterOS::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void MedCenterOS::pauseScreen() const {
    std::cout << "\n\033[1;36mPress Enter to return to Command Control Centre...\033[0m";
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void MedCenterOS::printHeader() const {
    std::cout << "\033[1;36m"
              << "================================================================================\n"
              << "          🏥  MEDCARE ENTERPRISE OS - ADVANCED CLINICAL CONTROL  🏥        \n"
              << "================================================================================\033[0m\n";
}

void MedCenterOS::printDeveloperBanner() const {
    std::cout << "\033[1;90m"
              << "--------------------------------------------------------------------------------\n"
              << "  Lead Software Architect: Syed Saad Bin Irfan | BSSE'28 Student @ DCS-UBIT\n"
              << "  University of Karachi | Professional High-Fidelity Healthcare Engine\n"
              << "--------------------------------------------------------------------------------\033[0m\n";
}

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

double MedCenterOS::getValidatedDouble(const std::string& prompt, double minVal, double maxVal) {
    double input;
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
        std::cout << "\033[1;31m[!] Out of scope. Range limits: [" << minVal << " - " << maxVal << "].\033[0m\n";
    }
}

std::string MedCenterOS::getValidatedString(const std::string& prompt, bool allowSpaces) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (allowSpaces) {
            std::getline(std::cin, input);
        } else {
            std::cin >> input;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        if (!input.empty() && input.find('|') == std::string::npos) {
            return input;
        }
        std::cout << "\033[1;31m[!] Error: String input cannot be null or contain reserved pipe (|) characters.\033[0m\n";
    }
}

void MedCenterOS::loadAllDatabases() {
    // 1. Patient Loading
    patients.clear();
    std::ifstream pFile(patientFile);
    std::string line;
    if (pFile.is_open()) {
        while (std::getline(pFile, line)) {
            if (!line.empty()) patients.push_back(Patient::deserialize(line));
        }
        pFile.close();
    }

    // 2. Doctor Loading
    doctors.clear();
    std::ifstream dFile(doctorFile);
    if (dFile.is_open()) {
        while (std::getline(dFile, line)) {
            if (!line.empty()) doctors.push_back(Doctor::deserialize(line));
        }
        dFile.close();
    } else {
        // Feed mock doctors if empty
        doctors.push_back(Doctor(2001, "Dr. Imran Ahmed", "Cardiology", "Morning", 2000.0, true));
        doctors.push_back(Doctor(2002, "Dr. Aisha Khan", "Neurology", "Evening", 2500.0, true));
        doctors.push_back(Doctor(2003, "Dr. Faisal Shah", "Pediatrics", "Night", 1500.0, true));
        doctors.push_back(Doctor(2004, "Dr. Maria Alvi", "General Medicine", "Morning", 1000.0, true));
    }

    // 3. Inventory Loading
    inventory.clear();
    std::ifstream iFile(inventoryFile);
    if (iFile.is_open()) {
        while (std::getline(iFile, line)) {
            if (!line.empty()) inventory.push_back(InventoryItem::deserialize(line));
        }
        iFile.close();
    } else {
        // Feed mock pharmacy items
        inventory.push_back(InventoryItem(3001, "Panadol 500mg", 500, 15.0));
        inventory.push_back(InventoryItem(3002, "Augmentin 625mg", 100, 350.0));
        inventory.push_back(InventoryItem(3003, "Surbex-Z", 250, 45.0));
        inventory.push_back(InventoryItem(3004, "Loprin 75mg", 400, 12.0));
    }

    // 4. Lab Test Loading
    labTests.clear();
    std::ifstream ltFile(labTestFile);
    if (ltFile.is_open()) {
        while (std::getline(ltFile, line)) {
            if (!line.empty()) labTests.push_back(LabTest::deserialize(line));
        }
        ltFile.close();
    }
}

void MedCenterOS::saveAllDatabases() {
    // 1. Save Patients
    std::ofstream pFile(patientFile, std::ios::trunc);
    for (const auto& p : patients) pFile << p.serialize() << "\n";
    pFile.close();

    // 2. Save Doctors
    std::ofstream dFile(doctorFile, std::ios::trunc);
    for (const auto& d : doctors) dFile << d.serialize() << "\n";
    dFile.close();

    // 3. Save Inventory
    std::ofstream iFile(inventoryFile, std::ios::trunc);
    for (const auto& i : inventory) iFile << i.serialize() << "\n";
    iFile.close();

    // 4. Save Lab Tests
    std::ofstream ltFile(labTestFile, std::ios::trunc);
    for (const auto& lt : labTests) ltFile << lt.serialize() << "\n";
    ltFile.close();
}

int MedCenterOS::generatePatientID() const {
    if (patients.empty()) return 1001;
    int maxID = 1000;
    for (const auto& p : patients) { if (p.getID() > maxID) maxID = p.getID(); }
    return maxID + 1;
}

int MedCenterOS::generateDoctorID() const {
    if (doctors.empty()) return 2001;
    int maxID = 2000;
    for (const auto& d : doctors) { if (d.getID() > maxID) maxID = d.getID(); }
    return maxID + 1;
}

int MedCenterOS::generateItemID() const {
    if (inventory.empty()) return 3001;
    int maxID = 3000;
    for (const auto& i : inventory) { if (i.getID() > maxID) maxID = i.getID(); }
    return maxID + 1;
}

int MedCenterOS::generateTestID() const {
    if (labTests.empty()) return 4001;
    int maxID = 4000;
    for (const auto& lt : labTests) { if (lt.getTestID() > maxID) maxID = lt.getTestID(); }
    return maxID + 1;
}

void MedCenterOS::listActiveDoctors() const {
    std::cout << "\n  Active Duty Physicians:\n";
    std::cout << "  " << std::left << std::setw(8) << "Doc ID" << std::setw(25) << "Physician Name" << std::setw(20) << "Specialty" << std::setw(12) << "Shift" << "Fee\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    for (const auto& d : doctors) {
        if (d.getIsAvailable()) {
            std::cout << "  " << std::left << std::setw(8) << d.getID()
                      << std::setw(25) << d.getName()
                      << std::setw(20) << d.getSpecialty()
                      << std::setw(12) << d.getShift()
                      << d.getConsultationFee() << " PKR\n";
        }
    }
}

void MedCenterOS::patientAdmissionDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- PATIENT ADMISSION & TRIAGE CONTROL DECK ---\033[0m\n\n";

    int pid = generatePatientID();
    std::cout << "\033[1;32m[+] Next Available Ledger ID: " << pid << "\033[0m\n";

    std::string name = getValidatedString("❯ Patient Full Legal Name: ");
    int age = getValidatedInteger("❯ Patient Chronological Age: ", 0, 125);
    std::string gender = getValidatedString("❯ Gender Marker (Male/Female/Other): ");
    std::string contact = getValidatedString("❯ Primary Contact Number: ");
    std::string emergency = getValidatedString("❯ Emergency Kin & Phone: ");

    int triageInput = getValidatedInteger("❯ Clinical Triage [1-Green (Routine), 2-Yellow (Urgent), 3-Red (Emergency)]: ", 1, 3);
    TriageLevel triage = static_cast<TriageLevel>(triageInput);

    std::string ward = "Outpatient Desk";
    int bedNum = 0;
    double roomFee = 0.0;

    if (triage == TriageLevel::RED || triage == TriageLevel::YELLOW) {
        std::cout << "\n[!] Critical/Urgent priority flag active. Bed allocation protocol initialized.\n";
        ward = getValidatedString("❯ Select Rooming Ward Assignment (ICU / Emergency / Isolation): ");
        bedNum = getValidatedInteger("❯ Assign Physical Bed Slot [1-100]: ", 1, 100);
        roomFee = getValidatedDouble("❯ Room / Emergency Support Base Fee per 24 Hours (PKR): ", 0.0);
    }

    listActiveDoctors();
    int docID = getValidatedInteger("\n❯ Enter attending Physician ID to assign: ", 2001, 2999);
    
    double docFee = 0.0;
    auto dIt = std::find_if(doctors.begin(), doctors.end(), [docID](const Doctor& d) { return d.getID() == docID; });
    if (dIt != doctors.end()) {
        docFee = dIt->getConsultationFee();
    }

    std::string diagnosis = getValidatedString("❯ Initial Clinical Diagnostic Impression: ");
    std::string prescribedMeds = "None";

    FinancialLedger led;
    led.roomCharges = roomFee;
    led.doctorFees = docFee;
    led.labCharges = 0.0;
    led.pharmacyCharges = 0.0;
    led.taxPercentage = 5.0; // Health services tax
    led.insuranceCoverage = getValidatedDouble("❯ Payer Policy Insurance Coverage Ratio (0.0 to 1.0): ", 0.0, 1.0);
    led.isSettled = false;

    patients.push_back(Patient(pid, name, age, gender, contact, emergency, triage, ward, bedNum, docID, diagnosis, prescribedMeds, led));
    saveAllDatabases();

    std::cout << "\n\033[1;32m[✓] Medical Record Admitted and Synchronized with Database.\033[0m\n";
    pauseScreen();
}

void MedCenterOS::doctorAdministrationDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- MEDICAL STAFF REGISTRY MANAGEMENT ---\033[0m\n\n";

    std::cout << "1. Register New Physician to MedCare Staff\n"
              << "2. View Operational Medical Staff & Specialties\n"
              << "3. Modify Duty Shift Schedules\n"
              << "4. Exit to Command Control\n";

    int choice = getValidatedInteger("❯ Select Operation Sector [1-4]: ", 1, 4);

    if (choice == 1) {
        int docId = generateDoctorID();
        std::cout << "\n[+] Assigning Doctor ID: " << docId << "\n";
        std::string name = getValidatedString("❯ Doctor Full Name (prefix Dr.): ");
        std::string specialty = getValidatedString("❯ Clinical Specialty: ");
        std::string shift = getValidatedString("❯ Shift Shift Schedule (Morning/Evening/Night): ");
        double fee = getValidatedDouble("❯ Consultation Fee Rate (PKR): ", 0.0);

        doctors.push_back(Doctor(docId, name, specialty, shift, fee, true));
        saveAllDatabases();
        std::cout << "\n\033[1;32m[✓] Staff ID registered on central roster ledger.\033[0m\n";
    } 
    else if (choice == 2) {
        listActiveDoctors();
    } 
    else if (choice == 3) {
        int targetId = getValidatedInteger("❯ Enter Doctor Staff ID to update schedule: ", 2001, 2999);
        auto dIt = std::find_if(doctors.begin(), doctors.end(), [targetId](const Doctor& d) { return d.getID() == targetId; });
        if (dIt != doctors.end()) {
            std::string shift = getValidatedString("❯ Enter New Shift Assignment (Morning/Evening/Night): ");
            dIt->setShift(shift);
            double fee = getValidatedDouble("❯ Update Consultant Fee Profile (PKR): ", 0.0);
            dIt->setFee(fee);
            saveAllDatabases();
            std::cout << "\n\033[1;32m[✓] Roster schedule amended in database.\033[0m\n";
        } else {
            std::cout << "\n\033[1;31m[!] Physician ID not mapped on system rosters.\033[0m\n";
        }
    }
    pauseScreen();
}

void MedCenterOS::appointmentSchedulingDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- CLINICAL APPOINTMENT & VISIT MATRIX ---\033[0m\n\n";

    int pID = getValidatedInteger("❯ Enter patient ID requesting appointment: ");
    auto pIt = std::find_if(patients.begin(), patients.end(), [pID](const Patient& p) { return p.getID() == pID; });

    if (pIt == patients.end()) {
        std::cout << "\033[1;31m[!] Patient profile missing. Admission file required first.\033[0m\n";
        pauseScreen();
        return;
    }

    listActiveDoctors();
    int docID = getValidatedInteger("\n❯ Select Consultant ID for appointment assignment: ", 2001, 2999);
    auto dIt = std::find_if(doctors.begin(), doctors.end(), [docID](const Doctor& d) { return d.getID() == docID; });

    if (dIt == doctors.end() || !dIt->getIsAvailable()) {
        std::cout << "\033[1;31m[!] Physician not available or missing in current rota.\033[0m\n";
        pauseScreen();
        return;
    }

    // Set new doctor to patient and append consultation fee
    pIt->setAttendingDoctorID(docID);
    FinancialLedger led = pIt->getLedger();
    led.doctorFees += dIt->getConsultationFee();
    pIt->setLedger(led);
    saveAllDatabases();

    std::cout << "\n\033[1;32m[✓] Appointment confirmed with " << dIt->getName() << " (" << dIt->getSpecialty() << "). Fee appended to ledger.\033[0m\n";
    pauseScreen();
}

void MedCenterOS::wardBedManagementDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- INPATIENT BED ALLOCATION & WARD METRICS ---\033[0m\n\n";

    int targetID = getValidatedInteger("❯ Enter patient ID for room/ward transfer: ");
    auto pIt = std::find_if(patients.begin(), patients.end(), [targetID](const Patient& p) { return p.getID() == targetID; });

    if (pIt == patients.end()) {
        std::cout << "\033[1;31m[!] Clinical record not registered.\033[0m\n";
        pauseScreen();
        return;
    }

    std::cout << "\nCurrent Status: Assigned Ward -> " << pIt->getAssignedWard() << " | Bed # " << pIt->getBedNumber() << "\n";
    std::string newWard = getValidatedString("❯ Enter Destination Ward Designation (General / ICU / Pediatric): ");
    int newBed = getValidatedInteger("❯ Assign Open Bed Unit: [1-100]: ", 1, 100);
    double perDayCharge = getValidatedDouble("❯ Set Room Charge Rate per day (PKR): ", 0.0);

    pIt->setAssignedWard(newWard, newBed);
    FinancialLedger led = pIt->getLedger();
    led.roomCharges += perDayCharge;
    pIt->setLedger(led);
    saveAllDatabases();

    std::cout << "\n\033[1;32m[✓] Ward allocation processed natively. Financial balances adjusted.\033[0m\n";
    pauseScreen();
}

void MedCenterOS::pharmacyInventoryDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- PHARMACY DRUG DECK & DISPENSARY ---\033[0m\n\n";

    std::cout << "1. View On-hand Pharmacological Stocks\n"
              << "2. Add/Restock Inventory Formulas\n"
              << "3. Dispense Prescription Medicines to Patient Bill\n"
              << "4. Exit to Command Deck\n";

    int choice = getValidatedInteger("❯ Select Operation Sector [1-4]: ", 1, 4);

    if (choice == 1) {
        std::cout << "\n  Current Pharmacopoeia Catalog:\n";
        std::cout << "  " << std::left << std::setw(8) << "Item ID" << std::setw(30) << "Formula/Name" << std::setw(15) << "Stock Level" << "Unit Price\n";
        std::cout << "  " << std::string(65, '-') << "\n";
        for (const auto& i : inventory) {
            std::cout << "  " << std::left << std::setw(8) << i.getID()
                      << std::setw(30) << i.getName()
                      << std::setw(15) << i.getStock()
                      << i.getUnitPrice() << " PKR\n";
        }
    } 
    else if (choice == 2) {
        int targetId = getValidatedInteger("❯ Enter Stock Item ID to replenish (or enter 0 to create new): ");
        if (targetId == 0) {
            int newId = generateItemID();
            std::cout << "[+] Provisioning stock ID: " << newId << "\n";
            std::string name = getValidatedString("❯ Drug Formula Name: ");
            int qty = getValidatedInteger("❯ Opening Balance Stock Quantity: ", 1, 10000);
            double price = getValidatedDouble("❯ Unit Wholesale/Retail Price (PKR): ", 0.0);
            inventory.push_back(InventoryItem(newId, name, qty, price));
        } else {
            auto iIt = std::find_if(inventory.begin(), inventory.end(), [targetId](const InventoryItem& i) { return i.getID() == targetId; });
            if (iIt != inventory.end()) {
                int replenishment = getValidatedInteger("❯ Enter incoming quantity to add to stock levels: ", 1, 5000);
                iIt->setStock(iIt->getStock() + replenishment);
            } else {
                std::cout << "\033[1;31m[!] Target Drug Item mapping error.\033[0m\n";
            }
        }
        saveAllDatabases();
        std::cout << "\n\033[1;32m[✓] Pharmacological registries updated natively.\033[0m\n";
    } 
    else if (choice == 3) {
        int patientId = getValidatedInteger("❯ Patient Account ID for dispensing billing: ");
        auto pIt = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& p) { return p.getID() == patientId; });

        if (pIt == patients.end()) {
            std::cout << "\033[1;31m[!] Patient record not found in system ledger.\033[0m\n";
            pauseScreen();
            return;
        }

        int itemId = getValidatedInteger("❯ Enter Drug Stock ID to dispense: ", 3001, 3999);
        auto iIt = std::find_if(inventory.begin(), inventory.end(), [itemId](const InventoryItem& i) { return i.getID() == itemId; });

        if (iIt == inventory.end() || iIt->getStock() <= 0) {
            std::cout << "\033[1;31m[!] Out of stock or formula unregistered.\033[0m\n";
            pauseScreen();
            return;
        }

        int qty = getValidatedInteger("❯ Number of dosing units to dispense: ", 1, iIt->getStock());
        iIt->setStock(iIt->getStock() - qty);

        double drugCost = qty * iIt->getUnitPrice();
        FinancialLedger led = pIt->getLedger();
        led.pharmacyCharges += drugCost;
        pIt->setLedger(led);

        // Update prescriptions history string in patient file
        std::string currentMeds = pIt->getPrescribedMeds();
        if (currentMeds == "None") {
            pIt->setPrescribedMeds(iIt->getName() + " (" + std::to_string(qty) + ")");
        } else {
            pIt->setPrescribedMeds(currentMeds + "; " + iIt->getName() + " (" + std::to_string(qty) + ")");
        }

        saveAllDatabases();
        std::cout << "\n\033[1;32m[✓] Formula dispensed. Cost: " << drugCost << " PKR appended to patient ledger.\033[0m\n";
    }
    pauseScreen();
}

void MedCenterOS::clinicalLabDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- CLINICAL DIAGNOSTICS & LABORATORY INTERFACE ---\033[0m\n\n";

    std::cout << "1. Log Diagnostics / Laboratory Test Order\n"
              << "2. Access Active Lab Workorders Queue\n"
              << "3. Record Diagnostics Findings & Results\n"
              << "4. Exit to Command Center\n";

    int choice = getValidatedInteger("❯ Select Operation Sector [1-4]: ", 1, 4);

    if (choice == 1) {
        int patientId = getValidatedInteger("❯ Enter target Patient ID for test requisition: ");
        auto pIt = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& p) { return p.getID() == patientId; });

        if (pIt == patients.end()) {
            std::cout << "\033[1;31m[!] Patient ID not mapped.\033[0m\n";
            pauseScreen();
            return;
        }

        int testOpt = getValidatedInteger("❯ Diagnostic Category [1-Blood Panel, 2-MRI Scan, 3-X-Ray Imaging, 4-ECG cardiac analysis]: ", 1, 4);
        std::string type;
        double cost = 0.0;

        switch (testOpt) {
            case 1: type = "Blood Panel"; cost = 800.0; break;
            case 2: type = "MRI Scan"; cost = 8500.0; break;
            case 3: type = "X-Ray Imaging"; cost = 1200.0; break;
            case 4: type = "ECG Cardiac Analysis"; cost = 2500.0; break;
        }

        int testId = generateTestID();
        std::cout << "[+] Logged Test Order Ref: " << testId << "\n";

        labTests.push_back(LabTest(testId, patientId, type, "Pending", cost, false));

        // Append test fee directly to Patient ledger
        FinancialLedger led = pIt->getLedger();
        led.labCharges += cost;
        pIt->setLedger(led);

        saveAllDatabases();
        std::cout << "\n\033[1;32m[✓] Laboratory workorder initiated. Fee appended to billing balance.\033[0m\n";
    } 
    else if (choice == 2) {
        std::cout << "\n  Laboratory Worklist Matrix:\n";
        std::cout << "  " << std::left << std::setw(10) << "Work ID" << std::setw(12) << "Patient ID" << std::setw(25) << "Diagnostic Type" << std::setw(15) << "Status" << "Remarks/Findings\n";
        std::cout << "  " << std::string(75, '-') << "\n";
        for (const auto& lt : labTests) {
            std::cout << "  " << std::left << std::setw(10) << lt.getTestID()
                      << std::setw(12) << lt.getPatientID()
                      << std::setw(25) << lt.getTestType()
                      << std::setw(15) << (lt.getIsCompleted() ? "\033[1;32mCompleted\033[0m" : "\033[1;33mPending\033[0m")
                      << lt.getResult() << "\n";
        }
    } 
    else if (choice == 3) {
        int targetTest = getValidatedInteger("❯ Enter diagnostic Work ID to update findings: ");
        auto ltIt = std::find_if(labTests.begin(), labTests.end(), [targetTest](const LabTest& lt) { return lt.getTestID() == targetTest; });

        if (ltIt == labTests.end()) {
            std::cout << "\033[1;31m[!] Diagnostics Work ID mismatch.\033[0m\n";
            pauseScreen();
            return;
        }

        std::string findings = getValidatedString("❯ Enter Clinical Diagnostic Remarks / Medical Findings: ");
        ltIt->recordResult(findings);
        saveAllDatabases();
        std::cout << "\n\033[1;32m[✓] Laboratory results successfully submitted.\033[0m\n";
    }
    pauseScreen();
}

void MedCenterOS::billingLedgerDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- MEDICAL CLEARANCE & ACCOUNTING DECK ---\033[0m\n\n";

    int pID = getValidatedInteger("❯ Enter Patient ID to request billing clearance: ");
    auto pIt = std::find_if(patients.begin(), patients.end(), [pID](const Patient& p) { return p.getID() == pID; });

    if (pIt == patients.end()) {
        std::cout << "\033[1;31m[!] Patient Profile not mapped.\033[0m\n";
        pauseScreen();
        return;
    }

    FinancialLedger led = pIt->getLedger();
    double subtotal = pIt->calculateGrossTotal();
    double tax = subtotal * (led.taxPercentage / 100.0);
    double gross = subtotal + tax;
    double coverage = gross * led.insuranceCoverage;
    double netPayable = pIt->calculateNetBill();

    std::cout << "\n\033[1;32m╔══════════════════════════════════════════════════════════════════╗\n"
              << "║                ★  MEDCARE DETAILED DISCHARGE INVOICE ★           ║\n"
              << "╚══════════════════════════════════════════════════════════════════╝\033[0m\n"
              << "  Patient Account Record Ref:   " << pIt->getID() << "\n"
              << "  Patient Legal Name:           " << pIt->getName() << "\n"
              << "  Current Clinical Ward/Bed:    " << pIt->getAssignedWard() << " / Bed #" << pIt->getBedNumber() << "\n"
              << "  Clinical Diagnosis:           " << pIt->getDiagnosis() << "\n"
              << "  Pharmacy Dispensed:           " << pIt->getPrescribedMeds() << "\n"
              << "  ----------------------------------------------------------------\n"
              << "  Room Rent & Ward Service Fees:    " << std::fixed << std::setprecision(2) << led.roomCharges << " PKR\n"
              << "  Consultant / Physician Fees:      " << led.doctorFees << " PKR\n"
              << "  Lab Test / Diagnostics Fees:      " << led.labCharges << " PKR\n"
              << "  Pharmacy Formula Dispense Cost:   " << led.pharmacyCharges << " PKR\n"
              << "  ----------------------------------------------------------------\n"
              << "  Net Ledger Subtotal:              " << subtotal << " PKR\n"
              << "  SST Provincial Tax (" << led.taxPercentage << "%):         " << tax << " PKR\n"
              << "  Gross Liability:                  " << gross << " PKR\n"
              << "  Insurance Coverage Offset:       -" << coverage << " PKR\n"
              << "  ----------------------------------------------------------------\n"
              << "  \033[1;33mTOTAL NET RECEIVABLE AMOUNT:      " << netPayable << " PKR\033[0m\n"
              << "  ----------------------------------------------------------------\n";

    if (led.isSettled) {
        std::cout << "\033[1;32m  [✓] STATUS: PAID IN FULL. SYSTEM CLEARANCE GRANTED.\033[0m\n";
    } else {
        std::cout << "\033[1;31m  [!] STATUS: ACCOUNT OUTSTANDING. CLEARANCE DENIED.\033[0m\n";
        std::string choice = getValidatedString("❯ Process immediate financial settlement? (yes/no): ", false);
        if (choice == "yes" || choice == "YES") {
            led.isSettled = true;
            pIt->setLedger(led);
            saveAllDatabases();
            std::cout << "\n\033[1;32m[✓] Ledger balanced. Patient account zeroed. Authorized for discharge.\033[0m\n";
        }
    }
    pauseScreen();
}

void MedCenterOS::executiveReportingDeck() {
    clearScreen();
    printHeader();
    std::cout << "\033[1;35m--- EXECUTIVE BUSINESS REPORTING & ANALYTICS DASHBOARD ---\033[0m\n\n";

    double roomTotal = 0.0, doctorTotal = 0.0, labTotal = 0.0, pharmTotal = 0.0;
    double realizedCash = 0.0, unrealizedDebt = 0.0;
    int criticalEmergencyCount = 0, totalPatients = patients.size();

    for (const auto& p : patients) {
        FinancialLedger led = p.getLedger();
        roomTotal += led.roomCharges;
        doctorTotal += led.doctorFees;
        labTotal += led.labCharges;
        pharmTotal += led.pharmacyCharges;

        double netBill = p.calculateNetBill();
        if (led.isSettled) {
            realizedCash += netBill;
        } else {
            unrealizedDebt += netBill;
        }

        if (p.getTriage() == TriageLevel::RED) {
            criticalEmergencyCount++;
        }
    }

    double cumulativeGross = roomTotal + doctorTotal + labTotal + pharmTotal;

    std::cout << "  📊  Clinical Operations Census Metrics:\n"
              << "  " << std::string(60, '-') << "\n"
              << "  Total Patient Files Registered on Ledger:     " << totalPatients << "\n"
              << "  Active Critical Emergency Cases:              " << criticalEmergencyCount << "\n\n"
              << "     Hospital Financial Portfolios Ledger:\n"
              << "  " << std::string(60, '-') << "\n"
              << "  Ward Room Rent Revenue Realized:              " << roomTotal << " PKR\n"
              << "  Consulting Doctor Revenue Realized:           " << doctorTotal << " PKR\n"
              << "  Diagnostics & Laboratory Fee Billings:        " << labTotal << " PKR\n"
              << "  Pharmacy Dispensing Volume Revenue:           " << pharmTotal << " PKR\n"
              << "  " << std::string(60, '=') << "\n"
              << "  Cumulative Hospital Gross Ledger Assets:      " << cumulativeGross << " PKR\n"
              << "  Realized Hard Cash Flow Assets (Settled):     \033[1;32m" << realizedCash << " PKR\033[0m\n"
              << "  Outstanding Hospital Credit (Unpaid Balance): \033[1;31m" << unrealizedDebt << " PKR\033[0m\n";
    pauseScreen();
}

void MedCenterOS::run() {
    while (true) {
        clearScreen();
        printHeader();
        printDeveloperBanner();

        std::cout << "\n\033[1;36m       ★  CENTRALIZED STRATEGIC NAVIGATION CONSOLE  ★\033[0m\n"
                  << "  \033[1;32m1.\033[0m Patient Admissions Center (Registration & Triage Intake)\n"
                  << "  \033[1;32m2.\033[0m Medical Staff Administration (Doctor Roster & Schedules)\n"
                  << "  \033[1;32m3.\033[0m Scheduling Matrix Desk (Outpatient Appointments Queue)\n"
                  << "  \033[1;32m4.\033[0m Inpatient Bed & Ward Management (ICU / Room Transfers)\n"
                  << "  \033[1;32m5.\033[0m Integrated Dispensary Desk (Pharmacy Stock & Dispense)\n"
                  << "  \033[1;32m6.\033[0m Clinical Diagnostics & Laboratory (Test Orders & Records)\n"
                  << "  \033[1;32m7.\033[0m Central Accounting Gate (Detailed Invoicing & Settlements)\n"
                  << "  \033[1;32m8.\033[0m Executive Audit Office (Hospital Business Reporting Dashboard)\n"
                  << "  \033[1;31m9. Shutdown Clinical Node OS Safely\033[0m\n"
                  << std::string(80, '-') << "\n";

        int option = getValidatedInteger("\033[1;36m❯ Authorize Console Command Deck [1-9]: \033[0m", 1, 9);

        switch (option) {
            case 1: patientAdmissionDeck(); break;
            case 2: doctorAdministrationDeck(); break;
            case 3: appointmentSchedulingDeck(); break;
            case 4: wardBedManagementDeck(); break;
            case 5: pharmacyInventoryDeck(); break;
            case 6: clinicalLabDeck(); break;
            case 7: billingLedgerDeck(); break;
            case 8: executiveReportingDeck(); break;
            case 9: {
                clearScreen();
                std::cout << "\033[1;33m[!] Finalizing database safe state writes to disk...\033[0m\n";
                saveAllDatabases();
                std::cout << "\033[1;32m[✓] Operational datasets secured. Clinical Systems Offline. System Halted.\033[0m\n";
                return;
            }
        }
    }
}

//Maintains the master command line panel. Integrates the file persistence engine with terminal layouts and data stream validation.