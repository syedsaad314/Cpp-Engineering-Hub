#ifndef ASTRO_CALC_HPP
#define ASTRO_CALC_HPP

#include "AstroProfile.hpp"
#include <string>

class AstroCalc {
private:
    std::string user_name;
    int birth_month;
    int birth_day;
    ConstellationProfile profile;

    void calculateConstellation();

public:
    AstroCalc();
    void gatherInput();
    void runEngine();
    void displayCard() const;
};

#endif