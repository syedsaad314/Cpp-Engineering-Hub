#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <string>

class Doctor {
private:
    int id;
    std::string name;
    std::string specialty;
    std::string shift; // Morning, Evening, Night
    double consultationFee;
    bool isAvailable;

public:
    Doctor();
    Doctor(int id, std::string name, std::string specialty, std::string shift, double fee, bool isAvailable);

    int getID() const;
    std::string getName() const;
    std::string getSpecialty() const;
    std::string getShift() const;
    double getConsultationFee() const;
    bool getIsAvailable() const;

    void setIsAvailable(bool status);
    void setShift(const std::string& s);
    void setFee(double fee);

    std::string serialize() const;
    static Doctor deserialize(const std::string& line);
};

#endif

//Tracks clinical personnel profiles, active certifications, shift distributions, and professional consultation fee tariffs.