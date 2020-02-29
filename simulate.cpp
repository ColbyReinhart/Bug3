// Mosquito Simulator - Probability Based
// COF Spring 2020 Project
// Colby Reinhart, JT Raber, Vanessa Sanders, Jeremy Faircloth
// Date Started - 2-20-2020

#include "bug3.cpp"
#include <iostream>
#include <fstream>

int main(){

    // Open export file and format header
    std::ofstream csv("export.csv");
    csv << "INTROAMNT,INTROPRD,INTROINT,ENDPOP,DAYS,INTROTOT" << std::endl;

    // Simulation
    for(int i = 10000000; i <= 10000000000; i += 10000000) //Number of sterile males introduced. Ten million to ten billion in steps of ten million
        for(int j = 0; j <= 10000; j += 100) //Period of introduction. Zero to ten thousand in steps of one hundred
            for(int k = 1; k <= 20; ++k){ //Interval of introduction. One to twenty in steps of one.
                Population instance(1000000000, i, j, k, 6);
                // Make sure to adjust exportData function before running this
                //instance.iterate(1000, 1000, -1, csv);
            }
}