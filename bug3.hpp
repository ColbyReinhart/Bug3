#ifndef BUG_HPP
#define BUG_HPP

const int MAX_MALE_AGE = 30;
const int MAX_FEMALE_AGE = 37;
const int BREED_COOLDOWN = 3;
const int MATURE_AGE = 6;
const float DEATH_COEFFICIENT = 0.5;
const float BREED_COEFFICIENT = 0.001;
const float M_PERCENT = 0.5;

class Population {
public:
    Population();
    Population(unsigned long int start_pop, double sterile_percent, int sterile_interval, int sterile_period, int sterile_age);
    Population(unsigned long int start_pop, unsigned long int sterile_amount, int sterile_interval, int sterile_period, int sterile_age);
    void die();
    void age();
    void breed();
    void introduce_sterile_males();
    void update();
    void iterate(int days);
    void printInfo();
    unsigned long int male_population(int start_age);
    unsigned long int female_population(int start_age);
    unsigned long int sterile_male_population(int start_age);
    unsigned long int total_population(int start_age);
    unsigned long int cooldown_female_population();
private:
    unsigned long int males_[MAX_MALE_AGE];
    unsigned long int females_[MAX_FEMALE_AGE];
    unsigned long int sterile_males_[MAX_MALE_AGE];
    unsigned long int breeds_[BREED_COOLDOWN];
    double death_rate_;
    double mate_rate_;
    unsigned long int stable_pop_;
    double sterile_percent_;
    unsigned long int sterile_amount_;
    int sterile_interval_;
    int sterile_period_;
    int sterile_age_;
    int day_;
};

#endif