#include "../include/MedCenterOS.hpp"
#include <iostream>

int main() {
    // Optimize Standard Streams for High-Performance C++ Terminal Operations
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Instantiate and Launch MedCare Systems Command Console Node
    MedCenterOS systemInstance;
    systemInstance.run();

    return 0;
}

//Initializes the memory manager, configures raw streams for real-time console speed, and releases the workspace thread into the runtime loop.