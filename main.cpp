// Mosquito Simulator - Probability Based
// COF Spring 2020 Project
// Colby Reinhart, JT Raber, Vanessa Sanders, Jeremy Faircloth
// Date Started - 2-20-2020

#include "bug3.hpp"
#include <iostream>
#include <fstream>

int main(){

    // Open export file and format header
    std::ofstream csv("export.csv");
    csv << "MALEPOP,FEMALEPOP,STERILEMALEPOP,TOTALPOP,DEATHRATE,MATERATE,STABLEPOP,STERILEPERCENT,STERILEAMOUNT,STERILEINTERVAL,STERILEPERIOD,STERILEAGE,DAY" << std::endl;

    // Take in user specifications
    std::cout << "Input number of days to iterate: ";
    int maxDays;
    std::cin >> maxDays;
    std::cout << "Input day to begin writing data: ";
    int startExp;
    std::cin >> startExp;
    std::cout << "Input interval for which days will be recorded: ";
    int exportInt;
    std::cin >> exportInt;

    // Simulation
    Population testPop(1000000000, 0.25, 1, -1, 6);
    testPop.iterate(maxDays, startExp, exportInt, csv);

    // Close export file
    csv.close();

}