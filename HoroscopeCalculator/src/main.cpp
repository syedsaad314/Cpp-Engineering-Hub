#include "../include/AstroCalc.hpp"
#include <iostream>

#define GOLD    "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"
#define GREY    "\033[90m"

void drawHeader() {
    std::cout << GOLD << R"(
       ___       _             _____      _      
      / _ \  ___| |_ _ __ ___  /  __ \__ _| | ___ 
     / /_\ \/ __| __| '__/ _ \ | /  \/ _` | |/ __|
    / /_\\ \__ \ |_| | | (_) | | \__\ (_| | | (__ 
    \_| |_/|___/\__|_|  \___/  \____/\__,_|_|\___|
            Astronomical Coordinate Finder
    )" << RESET << std::endl;
}

int main() {
    int choice = 1;
    while (choice != 0) {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

        drawHeader();
        
        AstroCalc calculator;
        calculator.gatherInput();
        calculator.runEngine();
        calculator.displayCard();

        std::cout << GREY << "  [ Enter '1' to analyze another date | '0' to exit ]\n" << RESET;
        std::cout << CYAN << "  ❯ Selection: " << RESET;
        while (!(std::cin >> choice)) {
            std::cout << "  Invalid input. Enter 1 or 0: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    std::cout << GOLD << "\n  Clear skies! Keep looking up at the stars.\n\n" << RESET;
    return 0;
}