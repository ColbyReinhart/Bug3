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
    csv << "MALEPOP,FEMALEPOP,STERILEMALEPOP,TOTALPOP,DEATHRATE,MATERATE,STABLEPOP,STERILEAMOUNT,STERILEINTERVAL,STERILEPERIOD,STERILEAGE,DAY,TOTALSTERILEINTRODUCED" << std::endl;

    // user defined loop
    std::cout << "Run a test? [y/n]: ";
    char loop;
    std::cin >> loop;
    while(loop == 'y'){
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
        std::cout << "Give population specifications? Defaults are:" << std::endl
        << "Starting pop = 1000000000" << std::endl
        << "Sterile introduction percentage (based off of current population) = 0.25" << std::endl
        << "Sterile introduction interval (days) = 1" << std::endl
        << "Sterile introduction period (days) = INDEFINITE" << std::endl
        << "Sterile introduction age (days) = 6" << std::endl
        << "[y/n]: ";
        char pick;
        std::cin >> pick;
        if(pick == 'y'){
            std::cout << "Input starting population: ";
            unsigned long int start;
            std::cin >> start;
            std::cout << "Input sterile introduction percentage (based off of current population): ";
            double introPercent;
            std::cin >> introPercent;
            std::cout << "Input sterile introduction interval (days): ";
            int interval;
            std::cin >> interval;
            std::cout << "Input sterile introducton period (days, -1 for indefinite): ";
            int period;
            std::cin >> period;
            std::cout << "Input age of introduced sterilized males (days): ";
            int age;
            std::cin >> age;
            
            std::cout << "Beginning simulation\n";
            Population testPop(start, introPercent, interval, period, age);
            testPop.iterate(maxDays, csv);
        }
        else{
            std::cout << "Beginning simulation with default parameters\n";
            Population testPop(1000000000, 100, 1, -1, 6);
            testPop.iterate(maxDays, csv);
        }

         std::cout << "Run a test? [y/n]: ";
         std::cin >> loop;
    }

    // Close export file
    csv.close();

}
