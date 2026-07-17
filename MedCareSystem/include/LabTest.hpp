#ifndef LABTEST_HPP
#define LABTEST_HPP

#include <string>

class LabTest {
private:
    int testID;
    int patientID;
    std::string testType; // Blood Test, MRI, X-Ray, ECG, Covid-19
    std::string result;   // Diagnostic remarks
    double cost;
    bool isCompleted;

public:
    LabTest();
    LabTest(int tID, int pID, std::string type, std::string res, double cost, bool completed);

    int getTestID() const;
    int getPatientID() const;
    std::string getTestType() const;
    std::string getResult() const;
    double getCost() const;
    bool getIsCompleted() const;

    void recordResult(const std::string& res);
    void setCompleted(bool status);

    std::string serialize() const;
    static LabTest deserialize(const std::string& line);
};

#endif

//Tracks clinical laboratory workflows including MRI, CT Scans, blood pathology, and physical diagnostics.