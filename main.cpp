// Mosquito Simulator - Probability Based
// COF Spring 2020 Project
// Colby Reinhart, JT Raber, Vanessa Sanders, Jeremy Faircloth
// Date Started - 2-20-2020

#include "bug3.hpp"
#include <iostream>

int main(){
    Population testPop(1000000, 0.25, 1, -1, 6);
    testPop.iterate(1000);
}