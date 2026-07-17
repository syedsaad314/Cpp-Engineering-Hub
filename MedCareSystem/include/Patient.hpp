#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>

enum class TriageLevel {
    GREEN = 1,  // Routine Care
    YELLOW = 2, // Urgent Care
    RED = 3     // Critical / Emergency
};

struct FinancialLedger {
    double roomCharges;
    double doctorFees;
    double labCharges;
    double pharmacyCharges;
    double taxPercentage;     // GST/SST standard
    double insuranceCoverage; // 0.0 to 1.0 ratio
    bool isSettled;
};

class Patient {
private:
    int pid;
    std::string name;
    int age;
    std::string gender;
    std::string contact;
    std::string emergencyContact;
    TriageLevel triage;
    std::string assignedWard; // General, ICU, Pediatric, Isolation
    int bedNumber;
    int attendingDoctorID;    // ID of doctor assigned
    std::string diagnosis;
    std::string prescribedMeds; // Semicolon separated
    FinancialLedger ledger;

public:
    Patient();
    Patient(int id, std::string n, int a, std::string g, std::string c, std::string ec, TriageLevel t, std::string w, int bed, int docID, std::string diag, std::string meds, FinancialLedger led);

    int getID() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getContact() const;
    std::string getEmergencyContact() const;
    TriageLevel getTriage() const;
    std::string getAssignedWard() const;
    int getBedNumber() const;
    int getAttendingDoctorID() const;
    std::string getDiagnosis() const;
    std::string getPrescribedMeds() const;
    FinancialLedger getLedger() const;

    void setContact(const std::string& c);
    void setEmergencyContact(const std::string& ec);
    void setTriage(TriageLevel t);
    void setAssignedWard(const std::string& w, int bed);
    void setAttendingDoctorID(int docID);
    void setDiagnosis(const std::string& diag);
    void setPrescribedMeds(const std::string& meds);
    void setLedger(const FinancialLedger& led);

    std::string getTriageString() const;
    std::string getTriageColor() const;
    double calculateGrossTotal() const;
    double calculateNetBill() const;

    std::string serialize() const;
    static Patient deserialize(const std::string& line);
};

#endif

//Maintains comprehensive patient medical files, physical bed designations, emergency triage metrics, and an integrated financial ledger.