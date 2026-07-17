#include "../include/Patient.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

Patient::Patient() : pid(0), age(0), triage(TriageLevel::GREEN), bedNumber(0), attendingDoctorID(0) {
    ledger = {0.0, 0.0, 0.0, 0.0, 5.0, 0.0, false};
    diagnosis = "Undiagnosed";
    prescribedMeds = "None";
}

Patient::Patient(int id, std::string n, int a, std::string g, std::string c, std::string ec, TriageLevel t, std::string w, int bed, int docID, std::string diag, std::string meds, FinancialLedger led)
    : pid(id), name(n), age(a), gender(g), contact(c), emergencyContact(ec), triage(t), assignedWard(w), bedNumber(bed), attendingDoctorID(docID), diagnosis(diag), prescribedMeds(meds), ledger(led) {}

int Patient::getID() const { return pid; }
std::string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
std::string Patient::getGender() const { return gender; }
std::string Patient::getContact() const { return contact; }
std::string Patient::getEmergencyContact() const { return emergencyContact; }
TriageLevel Patient::getTriage() const { return triage; }
std::string Patient::getAssignedWard() const { return assignedWard; }
int Patient::getBedNumber() const { return bedNumber; }
int Patient::getAttendingDoctorID() const { return attendingDoctorID; }
std::string Patient::getDiagnosis() const { return diagnosis; }
std::string Patient::getPrescribedMeds() const { return prescribedMeds; }
FinancialLedger Patient::getLedger() const { return ledger; }

void Patient::setContact(const std::string& c) { contact = c; }
void Patient::setEmergencyContact(const std::string& ec) { emergencyContact = ec; }
void Patient::setTriage(TriageLevel t) { triage = t; }
void Patient::setAssignedWard(const std::string& w, int bed) { assignedWard = w; bedNumber = bed; }
void Patient::setAttendingDoctorID(int docID) { attendingDoctorID = docID; }
void Patient::setDiagnosis(const std::string& diag) { diagnosis = diag; }
void Patient::setPrescribedMeds(const std::string& meds) { prescribedMeds = meds; }
void Patient::setLedger(const FinancialLedger& led) { ledger = led; }

std::string Patient::getTriageString() const {
    switch (triage) {
        case TriageLevel::RED: return "EMERGENCY (RED)";
        case TriageLevel::YELLOW: return "URGENT (YELLOW)";
        case TriageLevel::GREEN: return "ROUTINE (GREEN)";
        default: return "UNKNOWN";
    }
}

std::string Patient::getTriageColor() const {
    switch (triage) {
        case TriageLevel::RED: return "\033[1;31m";    // Bold Red
        case TriageLevel::YELLOW: return "\033[1;33m"; // Bold Yellow
        case TriageLevel::GREEN: return "\033[1;32m";  // Bold Green
        default: return "\033[0m";
    }
}

double Patient::calculateGrossTotal() const {
    return ledger.roomCharges + ledger.doctorFees + ledger.labCharges + ledger.pharmacyCharges;
}

double Patient::calculateNetBill() const {
    double gross = calculateGrossTotal();
    double tax = gross * (ledger.taxPercentage / 100.0);
    double subtotal = gross + tax;
    double coverage = subtotal * ledger.insuranceCoverage;
    return subtotal - coverage;
}

std::string Patient::serialize() const {
    std::stringstream ss;
    ss << pid << "|"
       << name << "|"
       << age << "|"
       << gender << "|"
       << contact << "|"
       << emergencyContact << "|"
       << static_cast<int>(triage) << "|"
       << assignedWard << "|"
       << bedNumber << "|"
       << attendingDoctorID << "|"
       << diagnosis << "|"
       << prescribedMeds << "|"
       << std::fixed << std::setprecision(2) << ledger.roomCharges << "|"
       << ledger.doctorFees << "|"
       << ledger.labCharges << "|"
       << ledger.pharmacyCharges << "|"
       << ledger.taxPercentage << "|"
       << ledger.insuranceCoverage << "|"
       << (ledger.isSettled ? "1" : "0");
    return ss.str();
}

Patient Patient::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 19) return Patient();

    FinancialLedger led;
    led.roomCharges = std::stod(tokens[12]);
    led.doctorFees = std::stod(tokens[13]);
    led.labCharges = std::stod(tokens[14]);
    led.pharmacyCharges = std::stod(tokens[15]);
    led.taxPercentage = std::stod(tokens[16]);
    led.insuranceCoverage = std::stod(tokens[17]);
    led.isSettled = (tokens[18] == "1");

    return Patient(
        std::stoi(tokens[0]),
        tokens[1],
        std::stoi(tokens[2]),
        tokens[3],
        tokens[4],
        tokens[5],
        static_cast<TriageLevel>(std::stoi(tokens[6])),
        tokens[7],
        std::stoi(tokens[8]),
        std::stoi(tokens[9]),
        tokens[10],
        tokens[11],
        led
    );
}

//Maintains comprehensive patient medical files, physical bed designations, emergency triage metrics, and an integrated financial ledger.