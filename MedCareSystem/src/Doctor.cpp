#include "../include/Doctor.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

Doctor::Doctor() : id(0), consultationFee(0.0), isAvailable(true) {}

Doctor::Doctor(int id, std::string name, std::string specialty, std::string shift, double fee, bool isAvailable)
    : id(id), name(name), specialty(specialty), shift(shift), consultationFee(fee), isAvailable(isAvailable) {}

int Doctor::getID() const { return id; }
std::string Doctor::getName() const { return name; }
std::string Doctor::getSpecialty() const { return specialty; }
std::string Doctor::getShift() const { return shift; }
double Doctor::getConsultationFee() const { return consultationFee; }
bool Doctor::getIsAvailable() const { return isAvailable; }

void Doctor::setIsAvailable(bool status) { isAvailable = status; }
void Doctor::setShift(const std::string& s) { shift = s; }
void Doctor::setFee(double fee) { consultationFee = fee; }

std::string Doctor::serialize() const {
    std::stringstream ss;
    ss << id << "|"
       << name << "|"
       << specialty << "|"
       << shift << "|"
       << std::fixed << std::setprecision(2) << consultationFee << "|"
       << (isAvailable ? "1" : "0");
    return ss.str();
}

Doctor Doctor::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 6) return Doctor();

    return Doctor(
        std::stoi(tokens[0]),
        tokens[1],
        tokens[2],
        tokens[3],
        std::stod(tokens[4]),
        tokens[5] == "1"
    );
}

//Tracks clinical personnel profiles, active certifications, shift distributions, and professional consultation fee tariffs.