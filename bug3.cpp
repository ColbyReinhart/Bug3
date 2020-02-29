#include "bug3.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

//
// CONSTRUCTORS
//

Population::Population () {
    unsigned long int males_[MAX_MALE_AGE] = {0};
    unsigned long int females_[MAX_FEMALE_AGE] = {0};
    unsigned long int sterile_males_[MAX_MALE_AGE] = {0};
    unsigned long int breeds[BREED_COOLDOWN] = {0};
}

Population::Population (unsigned long int start_pop, unsigned long int sterile_amount, int sterile_interval, int sterile_period, int sterile_age) {
    unsigned long int male_pop = start_pop * M_PERCENT;
    unsigned long int female_pop = start_pop * (1 - M_PERCENT);
    for (int age = 0; age < MAX_MALE_AGE; ++age) {
        males_[age] = male_pop/MAX_MALE_AGE;
    }
    for (int age = 0; age < MAX_FEMALE_AGE; ++age) {
        females_[age] = female_pop/MAX_FEMALE_AGE;
    }
    for (int age = 0; age < MAX_MALE_AGE; ++age) {
        sterile_males_[age] = 0;
    }
    for (int age = 0; age < BREED_COOLDOWN; ++age) {
        breeds_[age] = 0;
    }
    sterile_amount_ = sterile_amount;
    sterile_interval_ = sterile_interval;
    sterile_period_ = sterile_period;
    sterile_age_ = sterile_age;
    stable_pop_ = start_pop;
    death_rate_ = 1;
    mate_rate_ = 0;
    day_ = 0;
}

//
// Accessors
//

unsigned long int Population::male_population(int start_age) const {
    unsigned long int sum = 0;
    for (int age = start_age; age < MAX_MALE_AGE; ++age) {
        sum+=males_[age];
    }
    return sum;
}

unsigned long int Population::female_population(int start_age) const {
    unsigned long int sum = 0;
    for (int age = start_age; age < MAX_FEMALE_AGE; ++age) {
        sum+=females_[age];
    }
    return sum;
}

unsigned long int Population::sterile_male_population(int start_age) const {
    unsigned long int sum = 0;
    for (int age = start_age; age < MAX_MALE_AGE; ++age) {
        sum+=sterile_males_[age];
    }
    return sum;
}

unsigned long int Population::total_population(int start_age) const {
    return (male_population(start_age) + female_population(start_age) + sterile_male_population(start_age));
}

unsigned long int Population::cooldown_female_population() const {
    unsigned long int sum = 0;
    for (int age = 0; age < BREED_COOLDOWN; ++age) {
        sum+=breeds_[age];
    }
    return sum;
}

//
// MUTATORS
//

void Population::die() {
    death_rate_ =  DEATH_COEFFICIENT * (total_population(0) / stable_pop_);
    for(int age = 0; age < MAX_MALE_AGE; ++age) {
        sterile_males_[age] = sterile_males_[age] * (1 - death_rate_);
        males_[age] = males_[age] * (1 - death_rate_);
    }
    for(int age = 0; age < MAX_FEMALE_AGE; ++age) {
        females_[age] = females_[age] * (1 - death_rate_);
    }
}

void Population::age () {
    die();
    for(int age = MAX_MALE_AGE-2; age >= 0; --age) {
        sterile_males_[age + 1] = sterile_males_[age];
        males_[age + 1] = males_[age];
    }
    sterile_males_[0] = 0;
    males_[0] = 0;
    for(int age = MAX_FEMALE_AGE-2; age >= 0; --age) {
        females_[age + 1] = females_[age];
    }
    females_[0] = 0;
    ++day_;
}

void Population::breed () {
    unsigned long int breeds = 0;
    unsigned long int breedable_females = female_population(MATURE_AGE) - cooldown_female_population();
    double mate_rate_ = double(male_population(MATURE_AGE)) / (double((male_population(MATURE_AGE)) + double(sterile_male_population(MATURE_AGE))));
    breeds = BREED_COEFFICIENT * mate_rate_ * breedable_females;
    unsigned long int new_males = breeds * M_PERCENT * (std::rand() % 40 + 80);
    unsigned long int new_females = breeds * (1 - M_PERCENT) * (std::rand() % 40 + 80);
    std::cout << new_males << "   " << new_females << "   " << breeds << "   " << mate_rate_ << "   " << male_population(MATURE_AGE) << "   " << sterile_male_population(MATURE_AGE);
    
    males_[0] = new_males;
    females_[0] = new_females;
}

void Population::introduce_sterile_males () {
    sterile_males_[sterile_age_] = sterile_amount_;
    total_sterile_introduced_+=sterile_amount_;
}


void Population::update () {
    printInfo();
    if ((day_ < sterile_period_ || sterile_period_ == -1) && day_ % sterile_interval_ == 0) {
        introduce_sterile_males();
    }
    age();
    breed();
}

void Population::iterate (int days, int expStart, int expInterval, std::ofstream& o) {
    while(day_ <= days && male_population(0) > 0 && female_population(0) > 0) {
        if(day_ >= expStart && (expInterval == -1 || (day_ - expStart) % expInterval == 0))
            exportData(o);
        update();
    }
}

//
// OUTPUT/EXPORT
//

void Population::printInfo() {
    std::cout << "[Day " << day_ << "]\nMales: " << male_population(0) << "\nFemales: " << female_population(0) << "\nSterile: " << sterile_male_population(0) << "\nCooldown: " << cooldown_female_population() << "\nDeath Rate: " << death_rate_ << "\n\n";
    /**std::cout << "Males: ";
    for(int i = 0;i < MAX_MALE_AGE;++i) {
        std::cout << "[" << males_[i] << "]";
    }
    std::cout << "\n";
    std::cout << "Females: ";
    for(int i = 0;i < MAX_FEMALE_AGE;++i) {
        std::cout << "[" << females_[i] << "]";
    }
    std::cout << "\n";
    std::cout << "Sterile: ";
    for(int i = 0;i < MAX_MALE_AGE;++i) {
        std::cout << "[" << sterile_males_[i] << "]";
    }
    std::cout << "\n";
    std::cout << "Cooldown: ";
    for(int i = 0;i < BREED_COOLDOWN;++i) {
        std::cout << "[" << breeds_[i] << "]";
    }**/
    std::cout << "\n";
}

// Writes data to a csv file
std::ofstream& Population::exportData(std::ofstream& out){
    out << male_population(0)
    << "," << female_population(0)
    << "," << sterile_male_population(0)
    << "," << total_population(0)
    << "," << death_rate_
    << "," << mate_rate_
    << "," << stable_pop_
    << "," << sterile_amount_
    << "," << sterile_interval_
    << "," << sterile_period_
    << "," << sterile_age_
    << "," << day_ 
    << "," << total_sterile_introduced_ << std::endl;
    return out;
}