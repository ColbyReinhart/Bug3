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
    csv << "INTROAMNT,INTROPRD,INTROINT,ENDPOP,DAYS,INTROTOT" << std::endl;

    unsigned long int AMTMIN = 1000000;
    unsigned long int AMTMAX = 10000000;
    unsigned long int AMTSTP = 1000000;
    unsigned long int AMTTOTAL = (AMTMAX / AMTSTP) - (AMTMIN / AMTSTP) + 1;

    unsigned long int PRDMIN = 0;
    unsigned long int PRDMAX = 1000;
    unsigned long int PRDSTP = 100;
    unsigned long int PRDTOTAL = (PRDMAX / PRDSTP) - (PRDMIN / PRDSTP) + 1;

    unsigned long int INTMIN = 1;
    unsigned long int INTMAX = 20;
    unsigned long int INTSTP = 1;
    unsigned long int INTTOTAL = (INTMAX / INTSTP) - (INTMIN / INTSTP) + 1;

    std::cout << AMTTOTAL << " " << PRDTOTAL << " " << INTTOTAL << std::endl;

    unsigned long int TOTAL = AMTTOTAL * PRDTOTAL * INTTOTAL;
    unsigned long int TEST = 0;
    long double PROGRESS = 0;
    int PERCENT = 0;

    // Simulation
    for(int i = AMTMIN; i <= AMTMAX; i += AMTSTP) //Number of sterile males introduced. Ten million to ten billion in steps of ten million
        for(int j = PRDMIN; j <= PRDMAX; j += PRDSTP) //Period of introduction. Zero to ten thousand in steps of one hundred
            for(int k = INTMIN; k <= INTMAX; k += INTSTP){ //Interval of introduction. One to twenty in steps of one.
                TEST = (i-AMTMIN)/AMTSTP*INTTOTAL*PRDTOTAL + (j-PRDMIN)/PRDSTP*INTTOTAL + (k-INTMIN)/INTSTP + 1;
                PROGRESS = double(TEST) / double(TOTAL);
                PERCENT = int(100*PROGRESS);
                std::cout << TEST << "/" << TOTAL << "    " << PERCENT << "%    " << "AMT=" << i << " PRD=" << j << " INT=" << k << std::endl;
                Population instance(1000000000, i, k, j, 6);
                instance.iterate(1000, csv);
            }
}