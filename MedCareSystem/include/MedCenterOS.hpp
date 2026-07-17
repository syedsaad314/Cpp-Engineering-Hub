#ifndef MEDCENTEROS_HPP
#define MEDCENTEROS_HPP

#include "Patient.hpp"
#include "Doctor.hpp"
#include "Inventory.hpp"
#include "LabTest.hpp"
#include <vector>
#include <string>

class MedCenterOS {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<InventoryItem> inventory;
    std::vector<LabTest> labTests;

    const std::string patientFile = "db_patients.txt";
    const std::string doctorFile = "db_doctors.txt";
    const std::string inventoryFile = "db_inventory.txt";
    const std::string labTestFile = "db_labtests.txt";

    // System I/O Protocols
    void loadAllDatabases();
    void saveAllDatabases();

    // Data Auto-Generators
    int generatePatientID() const;
    int generateDoctorID() const;
    int generateItemID() const;
    int generateTestID() const;

    // Terminal Screen Formats
    void clearScreen() const;
    void pauseScreen() const;
    void printHeader() const;
    void printDeveloperBanner() const;

    // Secure Stream Sanitizers
    int getValidatedInteger(const std::string& prompt, int minVal = 0, int maxVal = 1000000);
    double getValidatedDouble(const std::string& prompt, double minVal = 0.0, double maxVal = 10000000.0);
    std::string getValidatedString(const std::string& prompt, bool allowSpaces = true);

public:
    MedCenterOS();
    ~MedCenterOS();

    // Main Control Deck Loop
    void run();

    // Sub-Command Control Centers
    void patientAdmissionDeck();
    void doctorAdministrationDeck();
    void appointmentSchedulingDeck();
    void wardBedManagementDeck();
    void pharmacyInventoryDeck();
    void clinicalLabDeck();
    void billingLedgerDeck();
    void executiveReportingDeck();

    // Secondary Helpers
    void listActiveDoctors() const;
};

#endif

//Maintains the master command line panel. Integrates the file persistence engine with terminal layouts and data stream validation.