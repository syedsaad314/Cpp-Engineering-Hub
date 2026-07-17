#include "../include/LabTest.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

LabTest::LabTest() : testID(0), patientID(0), cost(0.0), isCompleted(false) {}

LabTest::LabTest(int tID, int pID, std::string type, std::string res, double cost, bool completed)
    : testID(tID), patientID(pID), testType(type), result(res), cost(cost), isCompleted(completed) {}

int LabTest::getTestID() const { return testID; }
int LabTest::getPatientID() const { return patientID; }
std::string LabTest::getTestType() const { return testType; }
std::string LabTest::getResult() const { return result; }
double LabTest::getCost() const { return cost; }
bool LabTest::getIsCompleted() const { return isCompleted; }

void LabTest::recordResult(const std::string& res) {
    result = res;
    isCompleted = true;
}

void LabTest::setCompleted(bool status) { isCompleted = status; }

std::string LabTest::serialize() const {
    std::stringstream ss;
    ss << testID << "|"
       << patientID << "|"
       << testType << "|"
       << result << "|"
       << std::fixed << std::setprecision(2) << cost << "|"
       << (isCompleted ? "1" : "0");
    return ss.str();
}

LabTest LabTest::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 6) return LabTest();

    return LabTest(
        std::stoi(tokens[0]),
        std::stoi(tokens[1]),
        tokens[2],
        tokens[3],
        std::stod(tokens[4]),
        tokens[5] == "1"
    );
}

//Tracks clinical laboratory workflows including MRI, CT Scans, blood pathology, and physical diagnostics.