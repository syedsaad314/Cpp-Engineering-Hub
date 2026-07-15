#include "../include/AstroCalc.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

// ANSI Terminal Formatting Constants
#define RESET   "\033[0m"
#define GOLD    "\033[1;33m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define WHITE   "\033[1;37m"
#define GREY    "\033[90m"
#define EMERALD "\033[1;32m"

AstroCalc::AstroCalc() : birth_month(1), birth_day(1) {
    profile = {"Unknown", "", "", "", ""};
}

void AstroCalc::gatherInput() {
    std::cout << MAGENTA << "\n   ✧✧✧  ENTER CELESTIAL DETAILS  ✧✧✧\n" << RESET;
    std::cout << CYAN << " ❯ " << WHITE << "Enter your Name: " << CYAN;
    std::cin >> user_name;

    std::cout << CYAN << " ❯ " << WHITE << "Birth Month (1-12): " << CYAN;
    while (!(std::cin >> birth_month) || birth_month < 1 || birth_month > 12) {
        std::cout << "   Invalid entry. Please use the scale of 1-12: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    std::cout << CYAN << " ❯ " << WHITE << "Birth Day (1-31): " << CYAN;
    while (!(std::cin >> birth_day) || birth_day < 1 || birth_day > 31) {
        std::cout << "   Invalid entry. Enter a valid day: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
}

void AstroCalc::calculateConstellation() {
    int m = birth_month;
    int d = birth_day;

    if ((m == 3 && d >= 21) || (m == 4 && d <= 19)) {
        profile = {"Aries", "♈", "Diamond", "March 21 - April 19", 
                   "Contains several stars with confirmed, orbiting exoplanets."};
    }
    else if ((m == 4 && d >= 20) || (m == 5 && d <= 20)) {
        profile = {"Taurus", "♉", "Emerald", "April 20 - May 20", 
                   "Home to the famous Pleiades and Hyades stellar open clusters."};
    }
    else if ((m == 5 && d >= 21) || (m == 6 && d <= 20)) {
        profile = {"Gemini", "♊", "Pearl", "May 21 - June 20", 
                   "Contains the famous bright binary star systems Castor and Pollux."};
    }
    else if ((m == 6 && d >= 21) || (m == 7 && d <= 22)) {
        profile = {"Cancer", "♋", "Ruby", "June 21 - July 22", 
                   "Houses the Beehive Cluster, one of the closest star groups to Earth."};
    }
    else if ((m == 7 && d >= 23) || (m == 8 && d <= 22)) {
        profile = {"Leo", "♌", "Peridot", "July 23 - August 22", 
                   "Home to many massive and bright structures, including the Leo Triplet galaxies."};
    }
    else if ((m == 8 && d >= 23) || (m == 9 && d <= 22)) {
        profile = {"Virgo", "♍", "Sapphire", "August 23 - September 22", 
                   "It is the second largest constellation cataloged in our night sky."};
    }
    else if ((m == 9 && d >= 23) || (m == 10 && d <= 22)) {
        profile = {"Libra", "♎", "Opal", "September 23 - October 22", 
                   "The only constellation representing an inanimate instrument (the scales)."};
    }
    else if ((m == 10 && d >= 23) || (m == 11 && d <= 21)) {
        profile = {"Scorpio", "♏", "Topaz", "October 23 - November 21", 
                   "Features the colossal red supergiant star Antares at its heart."};
    }
    else if ((m == 11 && d >= 22) || (m == 12 && d <= 21)) {
        profile = {"Sagittarius", "♐", "Turquoise", "November 22 - December 21", 
                   "Points directly to the supermassive black hole at the core of our Milky Way."};
    }
    else if ((m == 12 && d >= 22) || (m == 1 && d <= 19)) {
        profile = {"Capricorn", "♑", "Garnet", "December 22 - January 19", 
                   "One of the oldest scientifically recognized constellations in astronomy."};
    }
    else if ((m == 1 && d >= 20) || (m == 2 && d <= 18)) {
        profile = {"Aquarius", "♒", "Amethyst", "January 20 - February 18", 
                   "Contains the Helix Nebula, which looks like a giant celestial eye."};
    }
    else {
        profile = {"Pisces", "♓", "Aquamarine", "February 19 - March 20", 
                   "Features the grand design phantom spiral galaxy known as M74."};
    }
}

void AstroCalc::runEngine() {
    std::cout << std::endl;
    std::string stars[] = {"★", "☆", "✦", "✧"};
    for (int i = 0; i < 8; ++i) {
        std::cout << "\r" << MAGENTA << " [ " << stars[i % 4] << " ] Aligning celestial coordinates... Mapping orbital intersection..." << RESET << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(180));
    }
    std::cout << "\r" << EMERALD << " [ ✓ ] Astronomical Mapping Completed Successfully!                              \n" << RESET << std::endl;

    calculateConstellation();
}

void AstroCalc::displayCard() const {
    std::cout << GOLD << " ╔══════════════════════════════════════════════════════════════════╗\n" << RESET;
    std::cout << GOLD << " ║" << WHITE << "                  ★  CELESTIAL PROFILE CARD  ★                  " << GOLD << "║\n" << RESET;
    std::cout << GOLD << " ╠══════════════════════════════════════════════════════════════════╣\n" << RESET;
    
    std::cout << GOLD << " ║ " << CYAN << std::left << std::setw(18) << "Astronomer Name:" << WHITE << std::setw(46) << user_name << GOLD << "║\n";
    std::cout << GOLD << " ║ " << CYAN << std::left << std::setw(18) << "Date System:" << WHITE << std::setw(46) << (std::to_string(birth_day) + "/" + std::to_string(birth_month)) << GOLD << "║\n";
    
    std::cout << GOLD << " ╠══════════════════════════════════════════════════════════════════╣\n" << RESET;
    
    std::cout << GOLD << " ║ " << MAGENTA << std::left << std::setw(18) << "Constellation:" << GOLD << std::setw(46) << (profile.constellation + " " + profile.symbol) << GOLD << "║\n";
    std::cout << GOLD << " ║ " << MAGENTA << std::left << std::setw(18) << "Transit Window:" << WHITE << std::setw(46) << profile.date_range << GOLD << "║\n";
    std::cout << GOLD << " ║ " << EMERALD << std::left << std::setw(18) << "Birthstone:" << WHITE << std::setw(46) << profile.birthstone << GOLD << "║\n";
    
    std::cout << GOLD << " ╠══════════════════════════════════════════════════════════════════╣\n" << RESET;
    
    // Auto-wrap the scientific fact line neatly
    std::string fact = "Fact: " + profile.astronomical_fact;
    std::cout << GOLD << " ║ " << GREY << std::left << std::setw(64) << fact << GOLD << "║\n";
    
    std::cout << GOLD << " ╚══════════════════════════════════════════════════════════════════╝\n" << RESET << std::endl;
}